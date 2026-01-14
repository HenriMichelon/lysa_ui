/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.line;

namespace lysa::ui {

    Line::Line(Context& ctx, const LineStyle style) : Widget{ctx, LINE}, style{style} {
        allowChildren = false;
    }

    void Line::setStyle(const LineStyle style) {
        if (this->style != style) {
            this->style = style;
            resizeChildren();
            refresh();
        }
    }

}
