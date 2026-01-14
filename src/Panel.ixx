/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.panel;

import lysa.context;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * %A rectangular widget with only a background
     */
    class Panel: public Widget {
    public:
        Panel(Context& ctx): Widget(ctx, PANEL) {}

    protected:
        Panel(Context& ctx, const Type type): Widget(ctx, type) {}
    };

}