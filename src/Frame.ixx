/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.frame;

import lysa.context;
import lysa.math;
import lysa.ui.panel;

export namespace lysa::ui {

    /**
     * A rectangular frame widget with an optional title.
     */
    class Frame: public Panel {
    public:
        /**
         * Constructor.
         * @param ctx The engine context.
         * @param title The title of the frame.
         */
        Frame(Context& ctx, const std::string& title);

        /**
         * Returns the current title of the widget.
         */
        auto& getTitle() const { return title; }

        /**
         * Changes the title of the widget.
         */
        void setTitle(const std::string& title);

        /**
         * Sets the title text color.
         */
        void setTitleColor(const float4& color) { textColor = color; }

        /**
         * Returns the title text color.
         */
        auto getTitleColor() const { return textColor; }

    private:
        std::string title{};
        float4 textColor{0.0f};
    };

}
