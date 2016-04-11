//  Created by Eugene Rivera on 11/20/15.

#include "MakeTree.hpp"

TreeNode * MakeTree::insert(TreeNode *tNode, GraphNode *nNode){
    if (tNode == nullptr)
        return new TreeNode(nNode);
    if (tNode->graphNode()->getName() > nNode->getName())
        tNode->left(insert(tNode->left(), nNode));
    else
        tNode->right(insert(tNode->right(), nNode));
    return tNode;
}

GraphNode * MakeTree::local_find(TreeNode *root, string name){
    if (root == nullptr)
        return nullptr;
    if (root->graphNode()->getName() == name)
        return root->graphNode();
    if (root->graphNode()->getName() > name)
        return local_find(root->left(), name);
    return local_find(root->right(), name);
}

void MakeTree::print(TreeNode *root){
    if (root == nullptr)
        return;
    print(root->left());
    root->graphNode()->print();
    print(root->right());
}

