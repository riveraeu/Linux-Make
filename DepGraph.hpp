
#ifndef _DepGraph_hpp
#define _DepGraph_hpp

#include<iostream>
#include<cstring>

#include "MakeTree.hpp"
#include "Token.hpp"
#include "Reader.hpp"
#include "systemInterface.hpp"

class DepGraph {
public:
    DepGraph( string name );
    void print();
    void parseDepGraph();
    void runMake()              {runMake(firstTarget);}
    bool isCyclic()             {return isCyclic(firstTarget);}

private:
    Token readAndProcessDependencyPair(Reader *);
    bool isCyclic(GraphNode *);
    void runMake( GraphNode *p );

private:
    bool local_make(long time, GraphNode *p);
    string _fileToMake, _targetToMake;
    GraphNode *firstTarget;
    MakeTree *_tree;
};

#endif
