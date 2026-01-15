/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.check_widget;

import lysa.input_event;
import lysa.ui.event;

namespace lysa::ui {

    void CheckWidget::setState(const State newState) {
        if (state == newState) { return; }
        state = newState;
        resizeChildren();
        refresh();
        ctx.events.push({UIEvent::OnStateChange, UIEventState{.state = newState}, id});
    }

    bool CheckWidget::eventMouseDown(const MouseButton button, const float x, const float y) {
        if (getRect().contains(x, y)) {
            setState(state == CHECK ? UNCHECK : CHECK);
            Widget::eventMouseDown(button, x, y);
            return true;
        }
        return Widget::eventMouseDown(button, x, y);
    }

}
