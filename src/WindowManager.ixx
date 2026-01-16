/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.window_manager;

import lysa.context;
import lysa.input_event;
import lysa.math;
import lysa.rect;
import lysa.renderers.vector_2d;
import lysa.resources.font;
import lysa.resources.rendering_window;
import lysa.ui.window;

export namespace lysa::ui {

    /**
     * Manages all the UI windows for a rendering window.
     */
    class WindowManager {
    public:
        /**
         * Constructor.
         * @param renderingWindow The rendering window to manage UI for.
         * @param defaultFontURI URI of the default font.
         * @param defaultFontScale Default scale for the font.
         * @param defaultTextColor Default color for text.
         */
        WindowManager(
            RenderingWindow& renderingWindow,
            const std::string& defaultFontURI,
            float defaultFontScale = 1.0f,
            const float4& defaultTextColor = float4(1.0f, 1.0f, 1.0f, 1.0f));

        virtual ~WindowManager();

        /**
         * Creates and adds a UI Window to the list of managed windows.
         * @param rect The rectangle (position and size) of the new window.
         * @return Shared pointer to the created window.
         */
        std::shared_ptr<Window> create(const Rect& rect) {
            return add(std::make_shared<Window>(ctx, rect));
        }

        /**
         * Adds a UI Window to the list of managed windows.
         * @param window The window to add.
         * @return Shared pointer to the added window.
         */
        std::shared_ptr<Window> add(const std::shared_ptr<Window>& window);

        /**
         * Removes a UI Window from the list of managed windows.
         *
         * The Window will be removed at the start of the next frame.
         */
        void remove(const std::shared_ptr<Window>& window);

        /**
         * Returns the default font loaded at creation.
         */
        std::shared_ptr<Font> getDefaultFont() const { return defaultFont; }

        /**
         * Returns the default font scale.
         */
        auto getDefaultFontScale() const { return fontScale; }

        /**
         * Returns the default text color.
         */
        auto getDefaultTextColor() const { return textColor; }

        /**
         * Returns the aspect ratio of the managed rendering window.
         */
        float getAspectRatio() const { return renderingWindow.getRenderTarget().getAspectRatio(); }

        /**
         * Forces a redrawing of all the UI at the start of the next frame.
         */
        void refresh() { needRedraw = true; }

        /**
         * Returns the 2D renderer used by the manager.
         */
        Vector2DRenderer& getRenderer() { return renderer; }

        /**
         * Returns the resize delta for window resizing.
         */
        float getResizeDelta() const { return resizeDelta; }

        /**
         * Enables or disables UI window resizing by the user.
         */
        void setEnableWindowResizing(const bool enable) { enableWindowResizing = enable; }

        /**
         * Draws one frame of the UI.
         */
        void drawFrame();

        /**
         * Handles an input event.
         * @param inputEvent The input event to process.
         * @return True if the event was handled by the UI, false otherwise.
         */
        bool onInput(const InputEvent& inputEvent);

    private:
        const float resizeDelta{5.0f};
        Context& ctx;
        RenderingWindow& renderingWindow;
        Vector2DRenderer renderer;
        std::shared_ptr<Font> defaultFont;
        std::list<std::shared_ptr<Window>> windows;
        std::mutex windowsMutex;
        std::vector<std::shared_ptr<Window>> removedWindows{};
        std::shared_ptr<Window> focusedWindow{nullptr};
        std::shared_ptr<Window> resizedWindow{nullptr};
        bool needRedraw{false};
        bool enableWindowResizing{true};
        bool resizingWindow{false};
        bool resizingWindowOriginBorder{false};
        MouseCursor currentCursor{MouseCursor::ARROW};
        float fontScale;
        float4 textColor{1.0f};
    };
}
