/*
 * Copyright (c) 2024-present Henri Michelon
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
*/
module lysa.ui.tree_view;

import lysa.ui.alignment;

namespace lysa::ui {

    TreeView::TreeView(Context& ctx): Widget(ctx, TREEVIEW) {}

    void TreeView::setResources(const std::string& resBox, const std::string& resScroll, const std::string&) {
        if (box == nullptr) {
            box = std::make_shared<Box>(ctx);
            vScroll = std::make_shared<VScrollBar>(ctx, 0.0f, 0.0f);
            add(vScroll, Alignment::RIGHT, resScroll);
            add(box, Alignment::FILL, resBox);
            box->setDrawBackground(false);
            box->setPadding(1);
            vScroll->setStep(2);
        }
    }

    void TreeView::removeAllItems() {
        box->removeAll();
        items.clear();
    }

    std::shared_ptr<TreeView::Item>& TreeView::addItem(std::shared_ptr<Widget> item) {
        items.push_back(std::make_shared<Item>(ctx, item));
        auto& newWidget = items.back();
        box->add(newWidget, Alignment::TOPLEFT);
        newWidget->handle = std::make_shared<Text>(ctx, " ");
        newWidget->add(newWidget->handle,Alignment:: LEFT, treeTabsSize);
        newWidget->add(item, Alignment::LEFT);
        newWidget->_setSize(1000.0f, item->getHeight());
        newWidget->setDrawBackground(false);
        return newWidget;
    }

    std::shared_ptr<TreeView::Item>& TreeView::addItem(const std::shared_ptr<Item>& parent, std::shared_ptr<Widget> item) const {
        parent->children.push_back(std::make_shared<Item>(ctx, item));
        auto& newWidget = parent->children.back();
        newWidget->level = parent->level + 1;
        box->add(newWidget, Alignment::TOPLEFT);
        for (int i = 0; i <= newWidget->level; i++) {
            if (i == (newWidget->level)) {
                newWidget->handle = std::make_shared<Text>(ctx, " ");
                newWidget->add(newWidget->handle, Alignment::LEFT, treeTabsSize);
            }
            else {
                newWidget->add(std::make_shared<Panel>(ctx), Alignment::LEFT, treeTabsSize);
            }
        }
        parent->handle->setText("-");
        newWidget->add(item, Alignment::LEFT);
        newWidget->_setSize(1000.0f, item->getHeight());
        newWidget->setDrawBackground(false);
        //expand(parent->item);
        return newWidget;
    }

    void TreeView::expand(const std::shared_ptr<Widget>& item) const {
        for (const auto& widget : box->_getChildren()) {
            if (const auto itemWidget = dynamic_cast<Item*>(item.get())) {
                if (itemWidget->item == item) {
                    throw Exception("not implemented");
                    // log("found");
                }
            }
        }
    }

}
