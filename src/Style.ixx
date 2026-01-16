/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.style;

import std;
import lysa.context;
import lysa.rect;
import lysa.resources.font;
import lysa.renderers.vector_2d;
import lysa.ui.uiresource;
import lysa.ui.widget;

namespace lysa::ui {

    /**
     * UI Widget drawing style base class.
     */
    export class Style  {
    public:
        /**
         * Constructor.
         */
        Style();

        virtual ~Style() = default;

        /**
         * Creates a new UI drawing style renderer.
         * @param name Style name (e.g., "vector").
         * @return Shared pointer to the created style.
         */
        static std::shared_ptr<Style> create(const std::string & name= "vector");

        /**
         * Create a resource from a resources description string.
         * @param widget Widget to associate resources with.
         * @param resources String describing the resources.
         */
        virtual void addResource(Widget &widget, const std::string &resources) = 0;

        /**
         * Sets a style-specific option.
         * @param name Option name.
         * @param value Option value.
         */
        virtual void setOption(const std::string &name, const std::string &value);

        /**
         * Returns a style-specific option value.
         * @param name Option name.
         * @return The option value as a string.
         */
        std::string getOption(const std::string &name) const;

        /**
         * Draws a widget.
         * @param widget Widget to draw.
         * @param resources Resources used for drawing this widget.
         * @param render The 2D renderer.
         * @param when True = before drawing children, False = after.
         */
        virtual void draw(const Widget &widget, UIResource &resources, Vector2DRenderer &render, bool when) const = 0;

        /**
         * Adjusts a widget size to style specific constraints.
         * @param widget The widget being resized.
         * @param rect The rectangle to adjust.
         * @param resources The widget's UI resources.
         */
        virtual void resize(Widget &widget, Rect &rect, UIResource &resources) = 0;

        /**
         * Returns the default font for the style.
         */
        std::shared_ptr<Font> getFont() const { return font; }

    protected:
        std::shared_ptr<Font> font;

        virtual void init() {}

        virtual void updateOptions() = 0;

    private:
        class StyleOption {
        public:
            std::string name;
            std::string value;
            explicit StyleOption(const std::string &name):
                name{std::move(name)} {
            }
        };

        std::list<std::shared_ptr<StyleOption>> options;
    };
}
