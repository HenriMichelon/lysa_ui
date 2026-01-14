/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.event;

import lysa.event;
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

        Widget* source;
    };

    /**
     * Parameter for Event::OnClick
     */
    struct EventClick : UIEvent {
        //! set this to true if the event have been consumed and will not be passed to widgets below
        bool consumed{false};
    };

    /**
     * Parameters for Event::OnKeyDown and Event::OnKeyUp
     */
    struct EventKeyb : UIEvent {
        //! Key code
        Key key;
        //! set this to true if the event have been consumed and will not be passed to widgets & nodes below
        bool consumed{false};
    };

    /**
     * Parameters for Event::OnMouseDown and Event::OnMouseUp
     */
    struct EventMouseButton : UIEvent {
        //! Mouse button
        MouseButton button;
        //! X coord
        float x;
        //! Y coord
        float y;
        //! set this to true if the event have been consumed and will not be passed to widgets & nodes below
        bool consumed{false};
    };

    /**
     * Parameters for Event::OnMouseMove
     */
    struct EventMouseMove : UIEvent {
        //! Mouse button states
        uint32 buttonsState;
        //! X coord
        float x;
        //! Y coord
        float y;
        //! set this to true if the event have been consumed and will not be passed to widgets & nodes below
        bool consumed{false};
    };

    /**
     * Parameters for Event::OnStateChange
     */
    struct EventState : UIEvent {
        //! CheckWidget::State
        int32 state;
    };

    /**
     * Parameters for Event::EventValue
     */
    struct EventValue : UIEvent {
        float value;
        float previous;
    };

    /**
     * Parameters for Event::EventRange
     */
    struct EventRange : UIEvent {
        float min;
        float max;
        float value;
    };

    struct EventTextChange : UIEvent {
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
    //const event_type Event::OnValueUserChange{"on_value_use_change"};
    const event_type UIEvent::OnRangeChange{"on_range_change"};
    /*     const event_type Event::OnInsertItem{"on_insert_item"};
        const event_type Event::OnRemoveItem{"on_remove_item"};
        const event_type Event::OnSelectItem{"on_select_item"};
     */
}
