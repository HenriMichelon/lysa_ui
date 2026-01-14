/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.button;

import lysa.context;
import lysa.input_event;
import lysa.ui.box;

export namespace lysa::ui {

    /**
     * %A clickable Box
     */
    class Button : public Box {
    public:
        Button(Context& ctx);

    protected:
        bool eventMouseUp(MouseButton button, float x, float y) override;
    };

}
