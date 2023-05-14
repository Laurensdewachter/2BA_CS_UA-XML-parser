#include "TreeNode.h"


TreeNode::TreeNode(std::string value, bool is_brackets) : value(std::move(value)), parent(nullptr), children({}),
                                                          is_brackets(is_brackets) {}

const std::string &TreeNode::getValue() const {
    return value;
}

void TreeNode::addChild(TreeNode *child) {
    if (child == nullptr) return;
    child->parent = this;
    children.push_back(child);
}

TreeNode *TreeNode::getParent() const {
    return parent;
}

const std::vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}
