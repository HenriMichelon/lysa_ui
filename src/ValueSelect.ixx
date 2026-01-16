/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.value_select;

import lysa.context;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Base class for widgets that allow selecting a numeric value within a range.
     */
    class ValueSelect : public Widget {
    public:
        /**
         * Constructor.
         * @param ctx The engine context.
         * @param type The widget type.
         * @param min Minimum value.
         * @param max Maximum value.
         * @param value Initial value.
         * @param step Step increment.
         */
        ValueSelect(
            Context& ctx,
            Type type,
            float min,
            float max,
            float value,
            float step);

        /**
         * Returns the minimum value.
         */
        auto getMin() const { return min; }

        /**
         * Returns the maximum value.
         */
        auto getMax() const { return max; }

        /**
         * Returns the current value.
         */
        auto getValue() const { return value; }

        /**
         * Returns the step increment.
         */
        auto getStep() const { return step; }

        /**
         * Sets the minimum value.
         */
        virtual void setMin(float min);

        /**
         * Sets the maximum value.
         */
        virtual void setMax(float max);

        /**
         * Sets the current value.
         */
        virtual void setValue(float value);

        /**
         * Sets the step increment.
         */
        virtual void setStep(float step);

    protected:
        float min;
        float max;
        float value;
        float step;

        void eventResize() override;

        virtual void eventRangeChange();

        virtual void eventValueChange(float prev);
    };
}
