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

    /**
     * An editable single line of text widget.
     */
    class TextEdit : public Widget {
    public:
        /**
         * Constructor.
         * @param ctx The engine context.
         * @param text Initial text.
         */
        TextEdit(Context& ctx, const std::string& text = "");

        /**
         * Returns true if the widget is read-only.
         */
        auto isReadOnly() const { return readonly; }

        /**
         * Sets whether the widget is read-only.
         */
        void setReadOnly(const bool state) { readonly = state; }

        /**
         * Sets the text.
         */
        void setText(const std::string& text);

        /**
         * Sets the selection start position.
         */
        void setSelStart(uint32 start);

        /**
         * Returns the text.
         */
        auto getText() const { return text; }

        /**
         * Returns the selection start position.
         */
        auto getSelStart() const { return selStart; }

        /**
         * Returns the index of the first displayed character.
         */
        auto getFirstDisplayedChar() const { return startPos; }

        /**
         * Returns the text currently being displayed in the text box.
         */
        auto getDisplayedText() const { return textBox->getText(); }

        /**
         * Returns the internal text widget.
         */
        auto getTextBox() const { return textBox; }

        /**
         * Sets the UI resources for the text edit.
         */
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
