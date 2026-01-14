/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.line;

import lysa.context;
import lysa.ui.widget;

export namespace lysa::ui {
    /**
     * %A horizontal or vertical line
     */
    class Line : public Widget {
    public:
        enum LineStyle { HORIZ, VERT };

        Line(Context& ctx, LineStyle style = HORIZ);

        auto getStyle() const { return style; }

        void setStyle(LineStyle style);

    private:
        LineStyle style;
    };

    class HLine : public Line {
    public:
        HLine(Context& ctx) : Line(ctx, HORIZ) {}
    };

    class VLine : public Line {
    public:
        VLine(Context& ctx) : Line(ctx, VERT) {}
    };
}
