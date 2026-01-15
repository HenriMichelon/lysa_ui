/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.button;

import lysa.ui.event;

namespace lysa::ui {

    Button::Button(Context& ctx): Box{ctx, BUTTON} {
        moveChildrenOnPush = true;
        redrawOnMouseEvent = true;
        allowFocus = true;
    }

    bool Button::eventMouseUp(const MouseButton button, const float x, const float y) {
        if (isPushed()) {
            if (!getRect().contains(x, y)) {
                setPushed(false);
                resizeChildren();
            } else {
                Box::eventMouseUp(button, x, y);
                ctx.events.push(Event{ UIEvent::OnClick, UIEventClick{}, id});
                return true;
            }
        }
        Box::eventMouseUp(button, x, y);
        return false;
    }
}
