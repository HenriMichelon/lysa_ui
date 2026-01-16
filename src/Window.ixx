/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.window;

import lysa.context;
import lysa.input_event;
import lysa.math;
import lysa.rect;
import lysa.renderers.vector_2d;
import lysa.resources;
import lysa.resources.font;
import lysa.ui.alignment;
import lysa.ui.style;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A virtual UI Window displayed inside a rendering Window.
     *
     * All UI widgets must belong to a UI window.
     */
    class Window : public UniqueResource {
    public:
        /**
         * Which Window borders can be used to resize the Window.
         */
        enum ResizeableBorder {
            RESIZEABLE_NONE   = 0b0000, //! No resizing
            RESIZEABLE_LEFT   = 0b0001, //! Left border resizable
            RESIZEABLE_RIGHT  = 0b0010, //! Right border resizable
            RESIZEABLE_TOP    = 0b0100, //! Top border resizable
            RESIZEABLE_BOTTOM = 0b1000, //! Bottom border resizable
        };

        /**
         * Creates a virtual UI window with a given position & size.
         * @param ctx The engine context.
         * @param rect The initial rectangle (position and size).
         */
        Window(Context& ctx, const Rect& rect);

        /**
         * Sets the borders that can be used to resize the Window.
         * @param borders Bitmask of ResizeableBorder.
         */
        void setResizeableBorders(const uint32 borders) { resizeableBorders = borders; }

        /**
         * Returns the borders that can be used to resize the Window.
         * @return Bitmask of ResizeableBorder.
         */
        auto getResizeableBorders() const { return resizeableBorders; }

        /**
         * Returns the current style layout.
         * @return The style pointer, or null if none.
         */
        std::shared_ptr<Style> getStyle() const;

        /**
         * Sets the current style layout.
         *
         * If `null`, installs a default layout.
         */
        void setStyle(const std::shared_ptr<Style>& style);

        /**
         * Returns the root widget.
         *
         * This is the widget that covers the entire Window and is the parent
         * of all the widgets in the Window.
         */
        Widget &getWidget() const;

        /**
         * Sets the root widget with optional resource string.
         *
         * Call setStyle(nullptr) if no layout have been set previously.
         * @param child Child widget to set as root.
         * @param resources Resource string for the root widget.
         * @param padding Padding for the root widget
         */
        void setWidget(std::shared_ptr<Widget> child = nullptr, const std::string& resources = "", float padding = 0);

        /**
         * Creates & adds a child widget using a resource string.
         * @tparam T The type of the widget to create.
         * @tparam Args The types of the arguments to pass to the widget constructor.
         * @param resource Resource string.
         * @param alignment Placement alignment.
         * @param args Arguments to pass to the widget constructor.
         * @return Shared pointer to the created widget.
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> create(
            const std::string & resource ,
            const Alignment alignment,
            Args&&... args) {
            return add(
                std::make_shared<T>(ctx, std::forward<Args>(args)...),
                alignment,
                resource);
        }

        /**
         * Creates & adds a child widget.
         * @tparam T The type of the widget to create.
         * @tparam Args The types of the arguments to pass to the widget constructor.
         * @param alignment Placement alignment.
         * @param args Arguments to pass to the widget constructor.
         * @return Shared pointer to the created widget.
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> create(
            const Alignment alignment,
            Args&&... args) {
            return add(
                std::make_shared<T>(ctx, std::forward<Args>(args)...),
                alignment);
        }

        /**
         * Adds a child widget.
         *
         * Children widgets will be destroyed on parent destruction.
         * @tparam T The type of the widget to add.
         * @param child Child widget to add.
         * @param alignment Placement alignment.
         * @param resource Resource string.
         * @param overlap Overlap widget on top of other widgets.
         * @return Shared pointer to the added widget.
         */
        template<typename T>
        std::shared_ptr<T> add(
            const std::shared_ptr<T> &child,
            const Alignment alignment,
            const std::string & resource = "",
            const bool overlap = false) const {
            return getWidget().add(child, alignment, resource, overlap);
        }

        /**
         * Removes a child widget.
         */
        void remove(const std::shared_ptr<Widget>& child) const {
            getWidget().remove(child);
        }

        /**
         * Changes the focus to a specific widget.
         */
        void setFocusedWidget(const std::shared_ptr<Widget>& widget);

        /**
         * Returns the width of the client area.
         */
        auto getWidth() const { return rect.width; }

        /**
         * Returns the height of the client area.
         */
        auto getHeight() const { return rect.height; }

        /**
         * Sets the client area position & size.
         */
        void setRect(const Rect& newRect);

        /**
         * Sets the width of the client area.
         */
        void setWidth(float width);

        /**
         * Sets the height of the client area.
         */
        void setHeight(float height);

        /**
         * Sets the position of the Window, bottom-left.
         */
        void setPos(float x, float y);

        /**
         * Sets the position of the Window, bottom-left.
         */
        void setPos(const float2& pos);

        /**
         * Sets the X position of the Window, bottom-left.
         */
        void setX(float x);

        /**
         * Sets the Y position of the Window, bottom-left.
         */
        void setY(float y);

        /**
         * Returns the size & position of the widget.
         */
        const auto& getRect() const { return rect; }

        /**
         * Returns true if Window is currently visible.
         */
        auto isVisible() const { return visible; }

        /**
         * Sets the Window visibility.
         *
         * The change will be effective at the start of the next frame.
         */
        void setVisible(bool isVisible);

        /**
         * Hides the Window.
         *
         * The change will be effective at the start of the next frame.
         * It needs to be called before adding the Window to the manager if you want the Window to be hidden at startup.
         */
        void hide();

        /**
         * Shows the Window.
         *
         * The change will be effective at the start of the next frame.
         */
        void show();

        /**
         * Sets the alpha value for transparency.
         */
        void setTransparency(float alpha);

        /**
         * Event called after Window creation (by the Window manager).
         */
        virtual void onCreate() { }

        /**
         * Event called after Window destruction (by the Window manager).
         */
        virtual void onDestroy() {  }

        /**
         * Event called when (before) the Window manager need to show the Window.
         */
        virtual void onShow() { }

        /**
         * Event called when (after) the Window manager need to hide the Window.
         */
        virtual void onHide() { }

        /**
         * Event called after a size change.
         */
        virtual void onResize() { }

        /**
         * Event called after a position change.
         */
        virtual void onMove() { }

        /**
         * Event called when a key was pressed.
         * @param key The key pressed.
         * @return True if event was handled.
         */
        virtual bool onKeyDown(Key key) { return false; }

        /**
         * Event called when a key was released.
         * @param key The key released.
         * @return True if event was handled.
         */
        virtual bool onKeyUp(Key key) { return false; }

        /**
         * Event called when a mouse button was pressed inside the Window.
         * @param button The mouse button.
         * @param x Mouse X coordinate.
         * @param y Mouse Y coordinate.
         * @return True if event was handled.
         */
        virtual bool onMouseDown(MouseButton button, float x, float y) { return false; }

        /**
         * Event called when a mouse button was released inside the Window.
         * @param button The mouse button.
         * @param x Mouse X coordinate.
         * @param y Mouse Y coordinate.
         * @return True if event was handled.
         */
        virtual bool onMouseUp(MouseButton button, float x, float y) { return false; }

        /**
         * Event called when the mouse is moved above the Window client area.
         * @param buttonsState State of mouse buttons.
         * @param x Mouse X coordinate.
         * @param y Mouse Y coordinate.
         * @return True if event was handled.
         */
        virtual bool onMouseMove(uint32 buttonsState, float x, float y) { return false; }

        /**
         * Event called when the Window got the keyboard focus.
         */
        virtual void onGotFocus() { }

        /**
         * Event called when the Window lost the keyboard focus.
         */
        virtual void onLostFocus() { }

        /**
         * Sets the minimum size of the Window (default to {2.0f, 2.0f}).
         */
        void setMinimumSize(float width, float height);

        /**
         * Sets the maximum size of the Window (default to VECTOR_SCALE).
         */
        void setMaximumSize(float width, float height);

        /**
         * Returns the minimum width of the Window.
         */
        auto getMinimumWidth() const { return minWidth; }

        /**
         * Returns the minimum height of the Window.
         */
        auto getMinimumHeight() const { return minHeight; }

        /**
         * Returns the maximum width of the Window.
         */
        auto getMaximumWidth() const { return maxWidth; }

        /**
         * Returns the maximum height of the Window.
         */
        auto getMaximumHeight() const { return maxHeight; }

        /**
         * Returns the default font loaded at startup.
         */
        std::shared_ptr<Font> getFont() const;

        /**
         * Sets the default font.
         */
        void setFont(const std::shared_ptr<Font>& font);

        /**
         * Returns the default font scale.
         */
        float getFontScale() const;

        /**
         * Sets the default font scale.
         */
        void setFontScale(float fontScale);

        /**
         * Returns the default text color.
         */
        auto& getTextColor() const { return textColor; }

        void setTextColor(const float4& color) { textColor = color; }

        void refresh() const;

        void eventCreate();

        void eventDestroy();

        void eventShow();

        void eventResize();

        void eventMove();

        void eventHide();

        bool eventKeyDown(Key);

        bool eventKeyUp(Key);

        bool eventMouseDown(MouseButton, float, float);

        bool eventMouseUp(MouseButton, float, float);

        bool eventMouseMove(uint32, float, float);

        void eventGotFocus();

        void eventLostFocus();

        void draw() const;

        friend class WindowManager;

        void attach(WindowManager* windowManager);

        void detach();

        WindowManager& getWindowManager() const { return *windowManager; }

    private:
        Context& ctx;
        Rect rect;
        float minWidth{2.0f};
        float minHeight{2.0f};
        float maxWidth{VECTOR_2D_SCREEN_SIZE};
        float maxHeight{VECTOR_2D_SCREEN_SIZE};
        std::shared_ptr<Style> layout{nullptr};
        std::shared_ptr<Widget> widget{nullptr};
        std::shared_ptr<Widget> focusedWidget{nullptr};
        float transparency{1.0};
        float4 textColor{0.0f, 0.0f, 0.0f, 1.0f};
        uint32 resizeableBorders{RESIZEABLE_NONE};
        WindowManager* windowManager{nullptr};
        bool visibilityChanged{false};
        bool visible{true};
        bool visibilityChange{false};
        std::shared_ptr<Font> font{nullptr};
        float fontScale{1.0f};

        void unFreeze(const std::shared_ptr<Widget> &);
    };
}

