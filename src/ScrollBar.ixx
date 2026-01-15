/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.scroll_bar;

import lysa.context;
import lysa.input_event;
import lysa.rect;
import lysa.types;
import lysa.ui.box;
import lysa.ui.event;
import lysa.ui.value_select;

export namespace lysa::ui {

    class ScrollBar : public ValueSelect {
    public:
        static constexpr auto LIFT_MINWIDTH{10};
        static constexpr auto LONGSTEP_MUX{5};

        enum Type {
            HORIZONTAL,
            VERTICAL
        };

        ScrollBar(
            Context& ctx,
            Type type = HORIZONTAL,
            float min = 0,
            float max = 100,
            float value = 0,
            float step = 1);

        Type getScrollBarType() const { return type; }

        void setResources(const std::string& area, const std::string& cage);

    private:
        Type type;
        bool onScroll{false};
        float scrollStart{0};
        std::shared_ptr<Box> liftArea;
        std::shared_ptr<Box> liftCage;

        bool eventMouseUp(MouseButton button, float x, float y) override;

        void eventMouseMove(uint32 button, float x, float y) override;

        void eventRangeChange() override;

        void eventValueChange(float prev) override;

        void onLiftAreaDown(const UIEventMouseButton* event) ;

        void onLiftCageDown(const UIEventMouseButton* event);

        void liftRefresh(const Rect& rect) const;
    };

    class VScrollBar : public ScrollBar {
    public:
        VScrollBar(Context& ctx, const float min = 0, const float max = 100, const float value = 0, const float step = 1):
            ScrollBar(ctx, VERTICAL, min, max, value, step) {
        }
    };

    class HScrollBar : public ScrollBar {
    public:
        HScrollBar(Context& ctx, const float min = 0, const float max = 100, const float value = 0, const float step = 1):
            ScrollBar(ctx, HORIZONTAL, min, max, value, step) {
        }
    };

}
