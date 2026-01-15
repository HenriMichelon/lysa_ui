/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.text_edit;

import lysa.context;
import lysa.exception;
import lysa.input_event;
import lysa.types;
import lysa.ui.box;
import lysa.ui.event;
import lysa.ui.text;
import lysa.ui.widget;

export namespace lysa::ui {

    class TextEdit : public Widget {
    public:
        TextEdit(Context& ctx, const std::string& text = "");

        auto isReadOnly() const { return readonly; }

        void setReadOnly(const bool state) { readonly = state; }

        void setText(const std::string& text);

        void setSelStart(uint32 start);

        auto getText() const { return text; }

        auto getSelStart() const { return selStart; }

        auto getFirstDisplayedChar() const { return startPos; }

        auto getDisplayedText() const { return textBox->getText(); }

        auto getTextBox() const { return textBox; }

        void setResources(const std::string& resource);

    protected:
        std::string text;
        bool readonly{false};
        uint32 selStart{0};
        uint32 selLen{0};
        uint32 startPos{0};
        uint32 nDispChar{0};
        std::shared_ptr<Box> box;
        std::shared_ptr<Text> textBox;

        bool eventKeyDown(Key key) override;

        // Compute the number of displayed characters
        void computeNDispChar();
    };
}
