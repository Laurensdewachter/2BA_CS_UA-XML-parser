#include "TreeNode.h"


TreeNode::TreeNode(std::string value) : value(std::move(value)), parent(nullptr), children({}) {}

const std::string &TreeNode::getValue() const {
    return value;
}

void TreeNode::addChild(TreeNode *child) {
    child->parent = this;
    children.push_back(child);
}

TreeNode *TreeNode::getParent() const {
    return parent;
}

const std::vector<TreeNode *> &TreeNode::getChildren() const {
    return children;
}
