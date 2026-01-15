/*
 * Copyright (c) 2024-resent Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.style_classic;

import lysa.math;
import lysa.rect;
import lysa.renderers.vector_2d;
import lysa.ui.button;
import lysa.ui.check_widget;
import lysa.ui.frame;
import lysa.ui.line;
import lysa.ui.panel;
import lysa.ui.uiresource;
import lysa.ui.scroll_bar;
import lysa.ui.style;
import lysa.ui.style_classic_resource;
import lysa.ui.text;
import lysa.ui.toggle_button;
import lysa.ui.tree_view;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * Classic vector style UI with 3D look
     */
    class StyleClassic : public Style {
    public:
        ~StyleClassic() override = default;

        void draw(const Widget &widget, UIResource &resources, Vector2DRenderer &renderer, bool before) const override;

        void addResource(Widget &widget, const std::string &resources) override;

        void resize(Widget &widget, Rect &rect, UIResource &resources) override;

    private:
        float4 focus{};
        float4 shadowDark{};
        float4 shadowBright{};
        float4 fgUp{};
        float4 fgDown{};
        // GTexture	*texture;

        void updateOptions() override;

        float4 extractColor(const std::string &OPT, float R, float G, float B, float A = 1.0f) const;

        void drawPanel(const Panel &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawBox(const Widget &, const StyleClassicResource &, Vector2DRenderer &, bool pushable) const;

        void drawLine(const Line &, const StyleClassicResource &, Vector2DRenderer &) const;

        void drawButton(const Button &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawToggleButton(ToggleButton &, StyleClassicResource &, Vector2DRenderer &) const;

        void drawText(const Text &, const StyleClassicResource &, Vector2DRenderer &) const;

        void drawFrame(Frame &, StyleClassicResource &, Vector2DRenderer &) const;

        /*void drawArrow(GArrow&, GLayoutVectorResource&, VectorRenderer&);
        void drawCheckmark(GCheckmark&, GLayoutVectorResource&, VectorRenderer&);
        void drawTextEdit(GTextEdit&, GLayoutVectorResource&, VectorRenderer&);
        void drawProgressBar(GProgressBar&, GLayoutVectorResource&, VectorRenderer&);
        void drawSelection(GSelection&, GLayoutVectorResource&, VectorRenderer&);
        void drawTrackBar(GTrackBar&, GLayoutVectorResource&, VectorRenderer&);
        void drawRoundButton(GRoundButton&, GLayoutVectorResource&, VectorRenderer&);
        void drawTabButton(GTabButton&, GLayoutVectorResource&, VectorRenderer&);
        void drawTabs(GTabs&, GLayoutVectorResource&, VectorRenderer&);
        void drawGridCell(GGridCell&, GLayoutVectorResource&, VectorRenderer&);*/
    };

} // namespace lysa::ui
