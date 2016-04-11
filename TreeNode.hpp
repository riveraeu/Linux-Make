
#ifndef _TreeNode_hpp
#define _TreeNode_hpp

#include<iostream>
#include<string>
#include "GraphNode.hpp"

class GraphNode;

class TreeNode {
public:
    TreeNode( GraphNode *nNode );

    TreeNode *left()                        {return leftSubtree;}
    void left( TreeNode *leftPtr )          {leftSubtree = leftPtr;}
    TreeNode *right()                       {return rightSubtree;}
    void right( TreeNode *rightPtr )        {rightSubtree = rightPtr;}
    void print()                            {cout << makeNode->getName() << endl;}
    GraphNode *graphNode()                  {return makeNode;}

private:
    GraphNode *makeNode;
    TreeNode *leftSubtree, *rightSubtree;
};

#endif
