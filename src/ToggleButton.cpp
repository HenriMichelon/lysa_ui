/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.toggle_button;

import lysa.ui.event;

namespace lysa::ui {

    ToggleButton::ToggleButton(Context& ctx): CheckWidget(ctx, TOGGLEBUTTON) {
        moveChildrenOnPush = true;
        redrawOnMouseEvent = true;
        allowFocus = true;
    }

    bool ToggleButton::eventMouseUp(const MouseButton button, const float x, const float y)  {
        CheckWidget::eventMouseUp(button, x, y);
        if (getRect().contains(x, y)) {
            ctx.events.push({UIEvent::OnClick, UIEventClick{}, id});
            return true;
        }
        return false;
    }

}
