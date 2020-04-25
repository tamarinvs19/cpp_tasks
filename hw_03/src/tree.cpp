#include <iostream>
#include "tree.h"

namespace huffman_tree {
TreeNode::TreeNode(char value, size_t weight, TreeNode* left_children, TreeNode* right_children) :
    weight_(weight),
    value_(value),
    left_children_(left_children),
    right_children_(right_children) {}

TreeNode::~TreeNode() {
    delete left_children_; delete right_children_;
}

bool TreeNode::Compar::operator()(const TreeNode* a, const TreeNode* b) {
    return a->weight_ > b->weight_;
}


HuffTree::~HuffTree() {
    delete root;
}

void HuffTree::build(std::vector<int> stat_table) {
    std::priority_queue<TreeNode*, std::vector<TreeNode*>, TreeNode::Compar> nodes;
    for (size_t i = 0; i < stat_table.size(); ++i) {
	TreeNode* node = new TreeNode((char)i, stat_table[i], nullptr, nullptr);
	nodes.push(node);
    }

    TreeNode *a, *b;
    while (nodes.size() > 1) {
	a = nodes.top(); nodes.pop();
	b = nodes.top(); nodes.pop();
	TreeNode* join_node =  new TreeNode(' ', a->weight_ + b->weight_, a, b);
	nodes.push(join_node);
    }
    root = nodes.top();
}

TreeNode* HuffTree::get_root() const {
    return root;
}

void HuffTree::gen_relative_code(const TreeNode* head, const std::string code) {
    if (head->left_children_ == nullptr || head->right_children_ == nullptr) 
	code_table_[head->value_] = code;
    else {
	gen_relative_code(head->left_children_, code + "0");
	gen_relative_code(head->right_children_, code + "1");
    }
}

std::unordered_map< char, std::string >* HuffTree::get_code_table() {
    return &code_table_;
}
}
