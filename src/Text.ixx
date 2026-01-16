/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.text;

import lysa.context;
import lysa.math;
import lysa.rect;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A widget to display a line of text.
     */
    class Text : public Widget {
    public:
        /**
         * Constructor.
         * @param ctx The engine context.
         * @param text Initial text to display.
         */
        Text(Context& ctx, const std::string& text = "");

        /**
         * Returns the displayed text.
         */
        const auto& getText() const { return text; }

        /**
         * Sets the text to display.
         */
        void setText(const std::string& text);

        /**
         * @param c The new color.
         */
        void setTextColor(const float4 &c);

        /**
         * Returns the text color.
         */
        auto getTextColor() const { return textColor; }

        /**
         * Sets the font scale.
         */
        void setFontScale(float scale) override;

        /**
         * Returns the size for the text.
         * @param width Output width.
         * @param height Output height.
         */
        void getSize(float &width, float &height) const;

        void _setSize(float width, float height) override;

    protected:
        Rect _getDefaultRect() override;

    private:
        std::string text;
        float4 textColor{0.0f};

        void eventCreate() override;
    };
}
