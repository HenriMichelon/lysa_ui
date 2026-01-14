/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.alignment;

export namespace lysa::ui {

    //! Widget placement (relative to the parent widget)
    enum class Alignment {
        NONE,
        //! The child widget is centered and resized to the parent content size
        FILL,
        //! The child widget is centered (and take all the parent content size)
        CENTER,
        //! The child widget is horizontally centered
        HCENTER,
        //! The child widget is vertically centered
        VCENTER,
        //! The children are stacked on the top
        TOP,
        //! The children are stacked on the bottom
        BOTTOM,
        //! The children are stacked on the left
        LEFT,
        //! The children are stacked on the right
        RIGHT,
        //! The children are stacked on the top and horizontally centered
        TOPCENTER,
        //! The children are stacked on the bottom and horizontally centered
        BOTTOMCENTER,
        //! The children are stacked on the left and vertically centered
        LEFTCENTER,
        //! The children are stacked on the right and vertically centered
        RIGHTCENTER,
        //! The children are stacked on the top and left aligned
        TOPLEFT,
        //! The children are stacked on the bottom and left aligned
        BOTTOMLEFT,
        //! The children are stacked on the bottom and right aligned
        BOTTOMRIGHT,
        //! The children are stacked on the top and right aligned
        TOPRIGHT,
        //! The children are stacked on the left then on the top
        LEFTTOP,
        //! The children are stacked on the left then on the bottom
        LEFTBOTTOM,
        //! The children are stacked on the right then on the bottom
        RIGHTBOTTOM,
        //! The children are stacked on the right then on the top
        RIGHTTOP,
        //!
        CORNERTOPLEFT,
        //!
        CORNERTOPRIGHT,
        //!
        CORNERBOTTOMLEFT,
        //!
        CORNERBOTTOMRIGHT
    };

}