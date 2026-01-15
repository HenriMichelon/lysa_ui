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
     * List of widgets events signals
     */
    struct UIEvent {
        //! called after widget creation (all widgets)
        static const std::string OnCreate;
        //! called before widget destruction (all widgets)
        static const std::string OnDestroy;
        //! called when the user press a key & the widget have the keyboard focus (all widgets)
        static const std::string OnKeyDown;
        //! called when the user press a key & the widget have the keyboard focus (all widgets)
        static const std::string OnKeyUp;
        //! the mouse button have been pressed above the widget or a child (all widgets)
        static const std::string OnMouseDown;
        //! the mouse button have been pressed above the widget or a child (all widgets)
        static const std::string OnMouseUp;
        //! the mouse have been moved above the widget (all widgets)
        static const std::string OnMouseMove;
        //! widget acquire keyboard focus (all widgets)
        static const std::string OnGotFocus;
        //! widget lost keyboard focus (all widgets)
        static const std::string OnLostFocus;
        //! called after visibility change (all widgets)
        static const std::string OnShow;
        //! called before visibility change (all widgets)
        static const std::string OnHide;
        //! called after state change (all widgets)
        static const std::string OnEnable;
        //! called after state change (all widgets)
        static const std::string OnDisable;
        //! text content of the widget have changed
        static const std::string OnTextChange;
        //! called when the user click on the widget (buttons)
        static const std::string OnClick;
        //! a CheckWidget state changed
        static const std::string OnStateChange;
        //! value of a ValueSelect widget changed
        static const std::string OnValueChange;
        //! value of a ValueSelect widget changed by the user
        //static const std::string OnValueUserChange;
        //! range of a ValueSelect widget changed
        static const std::string OnRangeChange;
        //! item list of a GList widget have changed
        //static const std::string OnInsertItem;
        //! item list of a GList widget have changed
        //static const std::string OnRemoveItem;
        //! a Window size changed
        static const std::string OnResize;
        //! a Window position changed
        static const std::string OnMove;
    };

    /**
     * Parameter for UIEvent::OnClick
     */
    struct UIEventClick : UIEvent {
    };

    /**
     * Parameters for UIEvent::OnKeyDown and UIEvent::OnKeyUp
     */
    struct UIEventKeyb : UIEvent {
        //! Key code
        Key key;
    };

    /**
     * Parameters for UIEvent::OnMouseDown and UIEvent::OnMouseUp
     */
    struct UIEventMouseButton : UIEvent {
        //! Mouse button
        MouseButton button;
        //! X coord
        float x;
        //! Y coord
        float y;
    };

    /**
     * Parameters for UIEvent::OnMouseMove
     */
    struct UIEventMouseMove : UIEvent {
        //! Mouse button states
        uint32 buttonsState;
        //! X coord
        float x;
        //! Y coord
        float y;
    };

    /**
     * Parameters for UIEvent::OnStateChange
     */
    struct UIEventState : UIEvent {
        //! CheckWidget::State
        int32 state;
    };

    /**
     * Parameters for UIEvent::EventValue
     */
    struct UIEventValue : UIEvent {
        float value;
        float previous;
    };

    /**
     * Parameters for UIEvent::EventRange
     */
    struct UIEventRange : UIEvent {
        float min;
        float max;
        float value;
    };

    struct UIEventTextChange : UIEvent {
        const std::string text;
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
