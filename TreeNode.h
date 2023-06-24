#ifndef PARSER_TREENODE_H
#define PARSER_TREENODE_H

#include <string>
#include <vector>

class TreeNode {
public:
    explicit TreeNode(std::string value, bool is_value);

    [[nodiscard]] const std::string &getValue() const;
    [[nodiscard]] TreeNode *getParent() const;
    [[nodiscard]] const std::vector<TreeNode *> &getChildren() const;

    void setValue(const std::string& new_value);
    void setParent(TreeNode* new_parent);
    void addChild(TreeNode *child);

private:
    std::string value;
    TreeNode *parent;
    std::vector<TreeNode *> children;
    bool is_value;
};


#endif
