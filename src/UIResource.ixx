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
     * @class UIResource
     * @brief Base class for style resources descriptions.
     */
    class UIResource {
    public:
        /**
         * @brief Constructor.
         * @param res The resource description string.
         */
        UIResource(const std::string& res): res{res} {}

        virtual ~UIResource() = default;

        /**
         * @brief Returns the resource description string.
         * @return Reference to the resource string.
         */
        const std::string& getResource() const { return res; }

    private:
        std::string res;
    };

}