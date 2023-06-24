#include "TreeNode.h"


TreeNode::TreeNode(std::string value, bool is_value) : value(std::move(value)), parent(nullptr), children({}),
                                                       is_value(is_value) {}

const std::string &TreeNode::getValue() const {
    return value;
}

TreeNode *TreeNode::getParent() const {
    return parent;
}

const std::vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}

void TreeNode::setValue(const std::string &new_value) {
    value = new_value;
}

void TreeNode::setParent(TreeNode *new_parent) {
    parent = new_parent;
}

void TreeNode::addChild(TreeNode *child) {
    if (child == nullptr) return;
    child->parent = this;
    children.push_back(child);
}
