/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.alignment;

export namespace lysa::ui {

    /**
     * Widget placement enumeration (relative to the parent widget).
     */
    enum class Alignment {
        NONE,               //! No alignment
        FILL,               //! The child widget is centered and resized to the parent content size
        CENTER,             //! The child widget is centered (and take all the parent content size)
        HCENTER,            //! The child widget is horizontally centered
        VCENTER,            //! The child widget is vertically centered
        TOP,                //! The children are stacked on the top
        BOTTOM,             //! The children are stacked on the bottom
        LEFT,               //! The children are stacked on the left
        RIGHT,              //! The children are stacked on the right
        TOPCENTER,          //! The children are stacked on the top and horizontally centered
        BOTTOMCENTER,       //! The children are stacked on the bottom and horizontally centered
        LEFTCENTER,         //! The children are stacked on the left and vertically centered
        RIGHTCENTER,        //! The children are stacked on the right and vertically centered
        TOPLEFT,            //! The children are stacked on the top and left aligned
        BOTTOMLEFT,         //! The children are stacked on the bottom and left aligned
        BOTTOMRIGHT,        //! The children are stacked on the bottom and right aligned
        TOPRIGHT,           //! The children are stacked on the top and right aligned
        LEFTTOP,            //! The children are stacked on the left then on the top
        LEFTBOTTOM,         //! The children are stacked on the left then on the bottom
        RIGHTBOTTOM,        //! The children are stacked on the right then on the bottom
        RIGHTTOP,           //! The children are stacked on the right then on the top
        CORNERTOPLEFT,      //! Stacked at top-left corner
        CORNERTOPRIGHT,     //! Stacked at top-right corner
        CORNERBOTTOMLEFT,   //! Stacked at bottom-left corner
        CORNERBOTTOMRIGHT   //! Stacked at bottom-right corner
    };

}