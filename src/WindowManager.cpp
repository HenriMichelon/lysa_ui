/*
 * Copyright (c) 2024-2025 Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.window_manager;

import lysa;

namespace lysa::ui {

    WindowManager::WindowManager(
        RenderingWindow& renderingWindow,
        const std::string& defaultFontURI,
        const float defaultFontScale,
        const float4& defaultTextColor):
        ctx{renderingWindow.getRenderTarget().getContext()},
        renderingWindow{renderingWindow},
        renderer{ctx,renderingWindow.getRenderTarget().getRendererConfiguration()},
        fontScale{defaultFontScale},
        textColor{defaultTextColor} {
        defaultFont = std::make_shared<Font>(ctx, defaultFontURI);
        renderingWindow.getRenderTarget().addRenderer(renderer);
        ctx.events.subscribe(MainLoopEvent::PROCESS, [this](const Event&) {
            drawFrame();
        });
        ctx.events.subscribe(RenderingWindowEvent::INPUT, renderingWindow.id, [this](Event& evt) {
            evt.consumed = onInput(std::any_cast<InputEvent>(evt.payload));
        });
    }

    WindowManager::~WindowManager() {
        for (const auto& window: windows) {
            window->eventDestroy();
        }
        windows.clear();
    }

    void WindowManager::drawFrame() {
        auto lock = std::lock_guard(windowsMutex);
        for(const auto&window : removedWindows) {
            window->detach();
            if (window->isVisible()) { window->eventHide(); }
            window->eventDestroy();
            windows.remove(window);
            needRedraw = true;
        }
        removedWindows.clear();
        for (auto& window: windows) {
            if (window->visibilityChanged) {
                window->visibilityChanged = false;
                window->visible = window->visibilityChange;
                needRedraw = true;
                if (window->visible) {
                    if (focusedWindow) { focusedWindow->eventLostFocus(); }
                    focusedWindow = window;
                    window->eventGotFocus();
                    window->eventShow();
                } else {
                    if (focusedWindow == window) {
                        window->eventLostFocus();
                        if (windows.empty()) {
                            focusedWindow = nullptr;
                        } else {
                            focusedWindow = windows.back();
                            focusedWindow->eventGotFocus();
                        }
                    }
                    window->eventHide();
                }
            }
        }
        if (!needRedraw) { return; }
        needRedraw = false;
        renderer.restart();
        for (const auto& window: windows) {
            window->draw();
        }
    }

    std::shared_ptr<Window> WindowManager::add(const std::shared_ptr<Window> &window) {
        {
            auto lock = std::lock_guard(windowsMutex);
            windows.push_back(window);
            window->attach(this);
        }
        window->eventCreate();
        if (window->isVisible()) { window->eventShow(); }
        needRedraw = true;
        return window;
    }

    void WindowManager::remove(const std::shared_ptr<Window>&window) {
        removedWindows.push_back(window);
    }

    bool WindowManager::onInput(const InputEvent &inputEvent) {
        if (inputEvent.type == InputEventType::KEY) {
            const auto &keyInputEvent = std::get<InputEventKey>(inputEvent.data);
            if ((focusedWindow != nullptr) && (focusedWindow->isVisible())) {
                if (keyInputEvent.pressed) {
                    return focusedWindow->eventKeyDown(keyInputEvent.key);
                } else {
                    return focusedWindow->eventKeyUp(keyInputEvent.key);
                }
            }
        } else if ((inputEvent.type == InputEventType::MOUSE_BUTTON)
                || (inputEvent.type == InputEventType::MOUSE_MOTION)) {
            if (renderingWindow.isMouseHidden()) {
                return false;
            }
            const auto scaleX = VECTOR_2D_SCREEN_SIZE / renderingWindow.getRenderTarget().getWidth();
            const auto scaleY = VECTOR_2D_SCREEN_SIZE / renderingWindow.getRenderTarget().getHeight();

            if (inputEvent.type == InputEventType::MOUSE_MOTION) {
                auto mouseEvent = std::get<InputEventMouseMotion>(inputEvent.data);
                const auto x = mouseEvent.position.x * scaleX;
                const auto y = mouseEvent.position.y * scaleY;
                const auto resizeDeltaY = scaleY * resizeDelta;
                if (resizedWindow != nullptr) {
                    if (resizingWindow) {
                        Rect rect = resizedWindow->getRect();
                        if (currentCursor == MouseCursor::RESIZE_H) {
                            const auto lx = x - rect.x;
                            if (resizingWindowOriginBorder) {
                                rect.width = rect.width - lx;
                                rect.x = x;
                            } else {
                                rect.width = lx;
                            }
                        } else {
                            const auto ly = y - rect.y;
                            if (resizingWindowOriginBorder) {
                                rect.height = rect.height - ly;
                                rect.y = y;
                            } else {
                                rect.height = ly;
                            }
                        }
                        resizedWindow->setRect(rect);
                        renderingWindow.setMouseCursor(currentCursor);
                        return true;
                    }
                    currentCursor = MouseCursor::ARROW;
                    resizedWindow = nullptr;
                    renderingWindow.setMouseCursor(currentCursor);
                }
                for (const auto& window: windows) {
                    auto consumed = false;
                    const float lx = std::ceil(x - window->getRect().x);
                    const float ly = std::ceil(y - window->getRect().y);
                    if (window->getRect().contains(x, y)) {
                        if (enableWindowResizing && window->getWidget().isDrawBackground()) {
                            if ((window->getResizeableBorders() & Window::RESIZEABLE_RIGHT) &&
                                (lx >= (window->getRect().width - resizeDelta))) {
                                currentCursor = MouseCursor::RESIZE_H;
                                resizedWindow = window;
                                resizingWindowOriginBorder = false;
                                } else if ((window->getResizeableBorders() & Window::RESIZEABLE_LEFT) &&
                                           (lx < resizeDelta)) {
                                    currentCursor = MouseCursor::RESIZE_H;
                                    resizedWindow = window;
                                    resizingWindowOriginBorder = true;
                                           } else if ((window->getResizeableBorders() & Window::RESIZEABLE_TOP) &&
                                                      (ly >= static_cast<float>(window->getRect().height - resizeDeltaY))) {
                                               currentCursor = MouseCursor::RESIZE_V;
                                               resizedWindow = window;
                                               resizingWindowOriginBorder = false;
                                                      } else if ((window->getResizeableBorders() & Window::RESIZEABLE_BOTTOM) &&
                                                                 (ly < static_cast<float>(resizeDeltaY))) {
                                                          currentCursor = MouseCursor::RESIZE_V;
                                                          resizedWindow = window;
                                                          resizingWindowOriginBorder = true;
                                                                 }
                        }
                        if (resizedWindow != nullptr) {
                            renderingWindow.setMouseCursor(currentCursor);
                            return true;
                        }
                        consumed |= window->eventMouseMove(mouseEvent.buttonsState, lx, ly);
                    }
                    if (consumed) { return true; }
                }
            } else {
                auto mouseInputEvent = std::get<InputEventMouseButton>(inputEvent.data);
                const auto x = mouseInputEvent.position.x * scaleX;
                const auto y = mouseInputEvent.position.y * scaleY;
                if (resizedWindow != nullptr) {
                    if ((!resizingWindow) &&
                        (mouseInputEvent.button== MouseButton::LEFT) &&
                        (mouseInputEvent.pressed)) {
                            resizingWindow = true;
                        } else if ((mouseInputEvent.button == MouseButton::LEFT) &&
                                   (!mouseInputEvent.pressed)) {
                            currentCursor = MouseCursor::ARROW;
                            resizedWindow = nullptr;
                            resizingWindow = false;
                        }
                    renderingWindow.setMouseCursor(currentCursor);
                    return true;
                }
                for (const auto& window: windows) {
                    auto consumed = false;
                    const auto lx = std::ceil(x - window->getRect().x);
                    const auto ly = std::ceil(y - window->getRect().y);
                    if (mouseInputEvent.pressed) {
                        if (window->getRect().contains(x, y)) {
                            focusedWindow = window;
                            consumed |= window->eventMouseDown(mouseInputEvent.button, lx, ly);
                        }
                    } else {
                        consumed |= window->eventMouseUp(mouseInputEvent.button, lx, ly);
                    }
                    if (consumed) { return true; }
                }
            }
        }
        return false;
    }

}