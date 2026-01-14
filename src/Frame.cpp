/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.frame;

import lysa.ui.window;

namespace lysa::ui {

    Frame::Frame(Context& ctx, const std::string& title):
          Panel{ctx, FRAME}, title{title} {
    }

    void Frame::setTitle(const std::string& title) {
        this->title = title;
        resizeChildren();
        refresh();
    }

}
