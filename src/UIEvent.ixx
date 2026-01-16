/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.event;

export import lysa.event;
import lysa.input_event;
import lysa.types;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * List of widget event signals.
     */
    struct UIEvent {
        static const std::string OnCreate;      //!< Called after widget creation (all widgets)
        static const std::string OnDestroy;     //!< Called before widget destruction (all widgets)
        static const std::string OnKeyDown;     //!< Called when the user presses a key & the widget has the keyboard focus (all widgets)
        static const std::string OnKeyUp;       //!< Called when the user releases a key & the widget has the keyboard focus (all widgets)
        static const std::string OnMouseDown;   //!< The mouse button has been pressed above the widget or a child (all widgets)
        static const std::string OnMouseUp;     //!< The mouse button has been released above the widget or a child (all widgets)
        static const std::string OnMouseMove;   //!< The mouse has been moved above the widget (all widgets)
        static const std::string OnGotFocus;    //!< Widget acquires keyboard focus (all widgets)
        static const std::string OnLostFocus;   //!< Widget lost keyboard focus (all widgets)
        static const std::string OnShow;        //!< Called after visibility change to visible (all widgets)
        static const std::string OnHide;        //!< Called after visibility change to hidden (all widgets)
        static const std::string OnEnable;      //!< Called after state change to enabled (all widgets)
        static const std::string OnDisable;     //!< Called after state change to disabled (all widgets)
        static const std::string OnTextChange;  //!< Text content of the widget has changed
        static const std::string OnClick;       //!< Called when the user clicks on the widget (buttons)
        static const std::string OnStateChange; //!< A CheckWidget state changed
        static const std::string OnValueChange; //!< Value of a ValueSelect widget changed
        static const std::string OnRangeChange; //!< Range of a ValueSelect widget changed
        static const std::string OnResize;      //!< A Window size changed
        static const std::string OnMove;        //!< A Window position changed
    };

    /**
     * Parameter for UIEvent::OnClick.
     */
    struct UIEventClick : UIEvent {
    };

    /**
     * Parameters for UIEvent::OnKeyDown and UIEvent::OnKeyUp.
     */
    struct UIEventKeyb : UIEvent {
        Key key; //!< Key code
    };

    /**
     * Parameters for UIEvent::OnMouseDown and UIEvent::OnMouseUp.
     */
    struct UIEventMouseButton : UIEvent {
        MouseButton button; //!< Mouse button
        float x;            //!< X coordinate
        float y;            //!< Y coordinate
    };

    /**
     * Parameters for UIEvent::OnMouseMove.
     */
    struct UIEventMouseMove : UIEvent {
        uint32 buttonsState; //!< Mouse button states bitmask
        float x;             //!< X coordinate
        float y;             //!< Y coordinate
    };

    /**
     * Parameters for UIEvent::OnStateChange.
     */
    struct UIEventState : UIEvent {
        int32 state; //!< New CheckWidget::State
    };

    /**
     * Parameters for UIEvent::OnValueChange.
     */
    struct UIEventValue : UIEvent {
        float value;    //!< New value
        float previous; //!< Previous value
    };

    /**
     * Parameters for UIEvent::OnRangeChange.
     */
    struct UIEventRange : UIEvent {
        float min;   //!< New minimum value
        float max;   //!< New maximum value
        float value; //!< Current value
    };

    /**
     * Parameters for UIEvent::OnTextChange.
     */
    struct UIEventTextChange : UIEvent {
        const std::string text; //!< New text content
    };

    const event_type UIEvent::OnCreate{"on_create"};
    const event_type UIEvent::OnDestroy{"on_destroy"};
    const event_type UIEvent::OnKeyDown{"on_key_down"};
    const event_type UIEvent::OnKeyUp{"on_key_up"};
    const event_type UIEvent::OnMouseDown{"on_mouse_down"};
    const event_type UIEvent::OnMouseUp{"on_mouse_up"};
    const event_type UIEvent::OnMouseMove{"on_mouse_move"};
    const event_type UIEvent::OnGotFocus{"on_got_focus"};
    const event_type UIEvent::OnLostFocus{"on_lost_focus"};
    const event_type UIEvent::OnShow{"on_show"};
    const event_type UIEvent::OnHide{"on_hide"};
    const event_type UIEvent::OnEnable{"on_enable"};
    const event_type UIEvent::OnDisable{"on_disable"};
    const event_type UIEvent::OnTextChange{"on_text_change"};
    const event_type UIEvent::OnClick{"on_click"};
    const event_type UIEvent::OnStateChange{"on_state_change"};
    const event_type UIEvent::OnResize{"on_resize"};
    const event_type UIEvent::OnMove{"on_move"};
    const event_type UIEvent::OnValueChange{"on_value_change"};
    //const event_type UIEvent::OnValueUserChange{"on_value_use_change"};
    const event_type UIEvent::OnRangeChange{"on_range_change"};
    /*     const event_type UIEvent::OnInsertItem{"on_insert_item"};
        const event_type UIEvent::OnRemoveItem{"on_remove_item"};
        const event_type UIEvent::OnSelectItem{"on_select_item"};
     */
}
