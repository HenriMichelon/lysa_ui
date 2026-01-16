/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.text_edit;

import std;
import lysa.input;
import lysa.log;
import lysa.ui.alignment;

namespace lysa::ui {

    TextEdit::TextEdit(Context& ctx, const std::string& text):
        Widget{ctx, TEXTEDIT},
        text(text)  {
        allowFocus = true;
    }

    void TextEdit::computeNDispChar() {
        auto s = box->getWidth() - box->getHBorder() * 2 - box->getPadding() * 2;
        const auto scale = textBox->getFontScale();
        uint32 i;
        for (i = startPos; (i < text.size()) && (s > 0); i++) {
            const auto width = getFont()->getWidth(text[i], scale);
            if (s < width) { break; }
            s -= width;
        }
        nDispChar = i - startPos;
    }

    void TextEdit::setText(const std::string& TEXT) {
        if (text == TEXT) return;
        if (text.empty()) {
            selStart = 0;
            startPos = 0;
        }
        text = TEXT;
        computeNDispChar();
        if (parent) { parent->refresh(); }
        if ((startPos + nDispChar) >= text.size()) {
            startPos = 0;
        }
        // Log::info(text, " : " , text.size(), " - " , startPos, " - ", nDispChar);
        textBox->setText(text.substr(startPos, nDispChar));
        box->refresh();
        refresh();
        ctx.events.push({UIEvent::OnTextChange, UIEventTextChange{.text = text}, id});
    }

    void TextEdit::setSelStart(const uint32 start) {
        selStart = start;
        if (startPos > selStart) {
            startPos = selStart;
        }
    }

    void TextEdit::setResources(const std::string& resource) {
        if (box == nullptr) {
            box = create<Box>(resource + ",LOWERED", Alignment::FILL);
            textBox = box->create<Text>(Alignment::HCENTER, text);
        }
        selStart = 0;
        startPos = 0;
        computeNDispChar();
        textBox->setText(text.substr(0, nDispChar));
    }

    bool TextEdit::eventKeyDown(const Key key) {
        const auto consumed = Widget::eventKeyDown(key);
        if (isReadOnly()) { return key; }

        setFreezed(true);
        if (key == KEY_LEFT) {
            if (selStart > 0) { selStart--; }
        }
        else if (key == KEY_RIGHT) {
            if (selStart < text.length()) { selStart++; }
        }
        else if (key == KEY_END) {
            selStart = text.length();
        }
        else if (key == KEY_HOME) {
            selStart = 0;
        }
        else if (key == KEY_BACKSPACE) {
            if (selStart > 0) {
                selStart--;
                setText(text.substr(0, selStart) + text.substr(selStart + 1,
                                                               text.length() - selStart - 1));
            }
        }
        else if (key == KEY_DELETE) {
            if (selStart < text.length()) {
                setText(text.substr(0, selStart) + text.substr(selStart + 1,
                                                               text.length() - selStart - 1));
            }
        } else if ((key != KEY_RIGHT_SHIFT) &&
                (key != KEY_LEFT_SHIFT) &&
                (key != KEY_RIGHT_CONTROL) &&
                (key != KEY_LEFT_CONTROL) &&
                (key != KEY_RIGHT_ALT) &&
                (key != KEY_LEFT_ALT)) {
            const auto c = Input::keyToChar(key);
            if (!c.empty()) {
                setText(text.substr(0, selStart) + c +
                        text.substr(selStart, text.size() - selStart));
                ctx.events.push({UIEvent::OnTextChange, UIEventTextChange{.text = text}, id});
                selStart++;
            }
            else {
                setFreezed(false);
                return true;
            }
        } else {
            setFreezed(false);
            return consumed;
        }
        computeNDispChar();
        if (selStart < startPos) {
            startPos = selStart;
        }
        else if (((selStart + selLen) > (startPos + nDispChar)) &&
            (nDispChar != text.length())) {
            startPos = selStart - nDispChar;
        }
        computeNDispChar();
        setFreezed(false);
        textBox->setText(text.substr(startPos, nDispChar));
        box->refresh();
        refresh();
        return true;
    }
}
