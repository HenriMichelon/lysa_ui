/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.check_widget;

import lysa.context;
import lysa.input_event;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Base class for all two-states widgets.
     */
    class CheckWidget : public Widget {
    public:
        /**
         * State of the widget.
         */
        enum State {
            UNCHECK = 0, //! Unchecked (aka OFF)
            CHECK = 1,   //! Checked (aka ON)
        };

        /**
         * Returns the current state of the widget.
         */
        auto getState() const { return state; }

        /**
         * Changes the state of the widget.
         */
        virtual void setState(State newState);

    protected:
        explicit CheckWidget(Context& ctx, const Type type): Widget{ctx, type} { }

        bool eventMouseDown(MouseButton button, float x, float y) override;

    private:
        State state{UNCHECK};
    };
}
