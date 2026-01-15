/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.uiresource;

import std;

export namespace lysa::ui {

    /**
     * Super class for style resources descriptions
     */
    class UIResource {
    public:
        UIResource(const std::string& res): res{res} {}

        virtual ~UIResource() = default;

        const std::string& getResource() const { return res; }

    private:
        std::string res;
    };

}