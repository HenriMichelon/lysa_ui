/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.widget;

import lysa.context;
import lysa.exception;
import lysa.rect;
import lysa.input_event;
import lysa.types;
import lysa.renderers.vector_2d;
import lysa.resources;
import lysa.resources.font;
import lysa.ui.alignment;
import lysa.ui.uiresource;

namespace lysa::ui {

    /**
     * Base class for all UI widgets.
     */
    export class Widget : public UniqueResource, public std::enable_shared_from_this<Widget>  {
    public:
        /**
         * Widget type enumeration.
         */
        enum Type {
            //! transparent widget
            WIDGET,
            //! rectangular widget with only a background
            PANEL,
            //! rectangular widget with a border and a background
            BOX,
            //! %A horizontal or vertical line
            LINE,
            //! %A box with a title
            FRAME,
            //! %A push button
            BUTTON,
            //! %A two states button
            TOGGLEBUTTON,
            //! %A single line of text
            TEXT,
            //! An editable single line of text
            TEXTEDIT,
            //! %A scroll bar. with min, max & pos
            SCROLLBAR,
            //! Tree of Widget
            TREEVIEW,
            //! 2D Image
            IMAGE,
        };

        /**
         * Creates a widget of a particular type.
         * @param ctx The engine context.
         * @param type The type of the widget.
         */
        Widget(Context& ctx, Type type = WIDGET);

        virtual ~Widget() = default;

        /**
         * Returns the type of the widget.
         */
        Type getType() const;

        /**
         * Returns true if the widget is visible.
         */
        bool isVisible() const;

        /**
         * Shows or hides the widget.
         */
        void show(bool show = true);

        /**
         * Returns true if the widget is reactive to user action (mouse & keyboard).
         */
        bool isEnabled() const;

        /**
         * Enables or disables widget reactions to input events.
         */
        void enable(bool isEnabled = true);

        /**
         * Moves the widget to a particular position.
         */
        void setPos(float x, float y);

        /**
         * Returns the width of the widget, in pixels.
         */
        float getWidth() const { return rect.width; }

        /**
         * Returns the height of the widget, in pixels.
         */
        float getHeight() const { return rect.height; }

        /**
         * Resizes the widget, in pixels.
         */
        virtual void setSize(float width, float height);

        /**
         * Returns the size & the position of the widget.
         */
        const Rect &getRect() const;

        /**
         * Changes the size & position of the widget.
         */
        void setRect(float x, float y, float width, float height);

        /**
         * Changes the size & position of the widget.
         */
        void setRect(const Rect &rect);

        /**
         * Returns the current widget placement.
         */
        Alignment getAlignment() const;

        /**
         * Sets the widget placement.
         *
         * Calling this method involves redrawing the parent widget &
         * resizing all the children widgets.
         */
        void setAlignment(Alignment alignment);

        /**
         * Returns the current font of the widget.
         */
        std::shared_ptr<Font> getFont() const;

        /**
         * Sets the current font of the widget.
         */
        void setFont(const std::shared_ptr<Font>& font);

        /**
         * Returns the font scale.
         */
        float getFontScale() const;

        /**
         * Sets the font scale.
         */
        virtual void setFontScale(float fontScale);

        /**
         * Returns true if the widget has keyboard focus.
         */
        bool isFocused() const;

        /**
         * Returns the parent widget, or nullptr.
         */
        Widget* getParent() const { return parent; }

        /**
         * Creates & adds a child widget using a resource string.
         * @tparam T The type of the widget to create.
         * @tparam Args The types of the arguments to pass to the widget constructor.
         * @param resource The resource string defining the widget style or properties.
         * @param alignment The alignment of the child widget.
         * @param args The arguments to pass to the widget constructor.
         * @return A shared pointer to the created widget.
         */
        template<typename T, typename... Args>
        std::shared_ptr<T> create(
            const std::string & resource,
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
         * @param alignment The alignment of the child widget.
         * @param args The arguments to pass to the widget constructor.
         * @return A shared pointer to the created widget.
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
         * @return A shared pointer to the added widget.
         */
        template<typename T>
        std::shared_ptr<T> add(
            std::shared_ptr<T> child,
            const Alignment alignment,
            const std::string &resource = "",
            const bool overlap = false) {
            assert([&]{return window != nullptr;}, "Widget must be added to a Window before adding child");
            if (!allowChildren) { return child; }
            children.push_back(child);
            _init(*child, alignment, resource, overlap);
            return child;
        }

        /**
         * Removes a child widget.
         */
        virtual void remove(const std::shared_ptr<Widget> &child);

        /**
         * Removes all children widgets recursively.
         */
        virtual void removeAll();

        /**
         * Changes children padding (space between children).
         */
        void setPadding(float padding);

        /**
         * Returns current children padding.
         */
        float getPadding() const;

        /**
         * Returns vertical border size.
         */
        float getVBorder() const;

        /**
         * Returns horizontal border size.
         */
        float getHBorder() const;

        /**
         * Sets vertical border size.
         */
        void setVBorder(float size);

        /**
         * Sets horizontal border size.
         */
        void setHBorder(float size);

        /**
         * Returns false if the background is transparent.
         */
        bool isDrawBackground() const;

        /**
         * Sets whether to draw the widget background.
         */
        void setDrawBackground(bool drawBackground);

        /**
         * Returns true if the widget is currently pushed (e.g. mouse button down).
         */
        bool isPushed() const;

        /**
         * Returns true if the widget is currently pointed by the mouse.
         */
        bool isPointed() const;

        /**
         * Returns true if the widget is freezed (not responding to events).
         */
        bool isFreezed() const;

        /**
         * Returns true if the widget should redraw on mouse events.
         */
        bool isRedrawOnMouseEvent() const;

        /**
         * Returns true if the widget is overlapping other widgets.
         */
        bool isOverlapping() const { return overlap; }

        /**
         * Returns the rectangle enclosing all children.
         */
        Rect getChildrenRect() const;

        /**
         * Sets whether the widget is freezed.
         */
        void setFreezed(const bool f) { freeze = f; }

        /**
         * Sets whether the widget is pushed.
         */
        void setPushed(const bool p) { pushed = p; }

        /**
         * Force a refresh of the entire widget.
         */
        void refresh() const;

        /**
         * Changes widget resources.
         */
        void setResource(std::shared_ptr<UIResource> resource);

        /**
         * Returns the user defined group index.
         */
        uint32 getGroupIndex() const;

        /**
         * Sets the user defined group index.
         */
        void setGroupIndex(int32 index);

        /**
         * Returns the user data.
         */
        void* getUserData() const;

        /**
         * Sets user data.
         */
        void setUserData(void *data);

        /**
         * Returns the transparency alpha value.
         */
        float getTransparency() const { return transparency; }

        /**
         * Changes the transparency alpha value.
         */
        void setTransparency(float alpha);

        /**
         * Resizes children widgets.
         */
        void resizeChildren();

        void _setRedrawOnMouseEvent(const bool r) { redrawOnMouseEvent = r; }

        void _setMoveChildrenOnPush(const bool r) { moveChildrenOnPush = r; }

        virtual std::list<std::shared_ptr<Widget>>& _getChildren() { return children; }

        void _draw(Vector2DRenderer &) const;

        std::shared_ptr<Widget> setFocus(bool = true);

        virtual void eventCreate();

        virtual void eventDestroy();

        virtual void eventShow();

        virtual void eventHide();

        virtual void eventEnable();

        virtual void eventDisable();

        virtual void eventMove(float x, float y);

        virtual void eventResize();

        virtual bool eventKeyDown(Key key);

        virtual bool eventKeyUp(Key key);

        virtual bool eventMouseDown(MouseButton button, float x, float y);

        virtual bool eventMouseUp(MouseButton button, float x, float y);

        virtual bool eventMouseMove(uint32, float x, float y);

        virtual void eventGotFocus();

        virtual void eventLostFocus();

        virtual void _setSize(float width, float height);

        void _allowFocus(bool allow = true);

    protected:
        friend class Window;
        Context& ctx;
        const Type type;
        Rect rect;
        Rect defaultRect;
        float hborder{0};
        float vborder{0};
        float padding{0};
        bool overlap{false};
        bool focused{false};
        bool allowFocus{false};
        bool allowChildren{true};
        bool drawBackground{true};
        bool moveChildrenOnPush{false};
        bool redrawOnMouseEvent{false};
        bool redrawOnMouseMove{false};
        float transparency{1.0f};
        Widget* parent{nullptr};
        Alignment alignment{Alignment::NONE};
        std::shared_ptr<UIResource> resource;
        std::list<std::shared_ptr<Widget>> children;
        Window* window{nullptr};
        void* style{nullptr};
        bool mouseMoveOnFocus{false};
        float fontScale{0.0f};

        virtual Rect _getDefaultRect() { return defaultRect; }

        virtual void _init(Widget &child, Alignment alignment, const std::string &res, bool overlap);

    private:
        bool pushed{false};
        bool pointed{false};
        bool freeze{true};
        bool enabled{true};
        bool visible{true};
        void *userData{nullptr};
        int32 groupIndex{0};
        Rect childrenRect;
        std::shared_ptr<Font> font{nullptr};

        std::shared_ptr<Widget> setNextFocus();
    };
}