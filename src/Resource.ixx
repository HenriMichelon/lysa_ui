/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.resource;

import std;

export namespace lysa::ui {

    /**
     * Super class for style resources descriptions
     */
    class Resource {
    public:
        Resource(const std::string& res): res{res} {}

        virtual ~Resource() = default;

        const std::string& getResource() const { return res; }

    private:
        std::string res;
    };

}