/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.box;

import lysa.context;
import lysa.ui.panel;

export namespace lysa::ui {

    /**
     * A rectangular box widget.
     */
    class Box : public Panel {
    public:
        /**
         * Constructor.
         * @param ctx The engine context.
         */
        Box(Context& ctx): Panel{ctx, BOX} {}

    protected:
        Box(Context& ctx, const Type type): Panel{ctx, type} {}
    };

}