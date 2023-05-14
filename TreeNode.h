#ifndef PARSER_TREENODE_H
#define PARSER_TREENODE_H

#include <string>
#include <vector>

class TreeNode {
public:
    explicit TreeNode(std::string value);

    [[nodiscard]] const std::string &getValue() const;

    void addChild(TreeNode *child);

    [[nodiscard]] TreeNode *getParent() const;

    [[nodiscard]] const std::vector<TreeNode *> &getChildren() const;

private:
    std::string value;
    TreeNode *parent;
    std::vector<TreeNode *> children;
};


#endif
