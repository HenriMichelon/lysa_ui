/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
export module lysa.ui.tree_view;

import lysa.context;
import lysa.exception;
import lysa.ui.box;
import lysa.ui.panel;
import lysa.ui.scroll_bar;
import lysa.ui.text;
import lysa.ui.widget;

export namespace lysa::ui {

    /**
     * A widget that displays a hierarchical list of items.
     */
    class TreeView : public Widget {
    public:
        /**
         * An item within a TreeView.
         */
        class Item : public Panel {
        public:
            std::shared_ptr<Widget> item;           //! The widget displayed for this item
            std::shared_ptr<Text> handle;           //! The expansion handle (+/-)
            std::list<std::shared_ptr<Item>> children; //! Child items
            int level{0};                           //! Depth level in the tree
            bool selected{false};                   //! Whether the item is selected
            bool expanded{false};                   //! Whether the item is expanded

            /**
             * Constructor.
             * @param ctx The engine context.
             * @param item The widget to display for this item.
             */
            Item(Context& ctx, std::shared_ptr<Widget> item) : Panel(ctx), item{item} {}
        };

        /**
         * Constructor.
         * @param ctx The engine context.
         */
        TreeView(Context& ctx);

        /**
         * Sets the UI resources for the tree view.
         * @param resBox Resource for the background box.
         * @param resScroll Resource for the scroll bar.
         */
        void setResources(const std::string& resBox, const std::string& resScroll, const std::string&);

        /**
         * Removes all items from the tree view.
         */
        void removeAllItems();

        /**
         * Adds a root item to the tree view.
         * @param item The widget to add as an item.
         * @return Shared pointer to the created tree item.
         */
        std::shared_ptr<Item>& addItem(std::shared_ptr<Widget> item);

        /**
         * Adds a child item to a parent item.
         * @param parent The parent item.
         * @param item The widget to add as a child item.
         * @return Shared pointer to the created tree item.
         */
        std::shared_ptr<Item>& addItem(const std::shared_ptr<Item>& parent, std::shared_ptr<Widget> item) const;

        /**
         * Expands a specific item.
         * @param item The widget associated with the item to expand.
         */
        void expand(const std::shared_ptr<Widget>& item) const;

    private:
        const std::string treeTabsSize{"5,5"};
        float innerHeight;
        float itemsHeight;
        std::list<std::shared_ptr<Item>> items;
        std::shared_ptr<Box> box;
        std::shared_ptr<VScrollBar> vScroll;
    };
}
