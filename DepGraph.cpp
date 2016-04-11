//  Created by Eugene Rivera on 11/20/15.


#include "DepGraph.hpp"

DepGraph::DepGraph(string name){
    _fileToMake = name;
    _targetToMake = "";
    firstTarget = nullptr;
    _tree = new MakeTree();
}

void DepGraph::print(){
    _tree->print();
}

void DepGraph::parseDepGraph(){
    Reader *reader = new Reader(_fileToMake);
    while(true){
        Token token = readAndProcessDependencyPair(reader);
        if (token.isEOF())
            return;
    }
}

void DepGraph::runMake(GraphNode *p){
    //Sets time stamps and compares the timestamps of the target and its dependent nodes.
    long time = 0;
    timestamp(p->getName().c_str(), &time);
    p->setTimeStamp(time);
    for (int i = 0; i < p->numDependentNodes(); i++)
        runMake(p->dependentNodes()->at(i));
    if (p->numDependentNodes() != 0){
        if (local_make(time, p)){
            p->runCommand();
            timestamp(p->getName().c_str(), &time);
            p->setTimeStamp(time);
        }
    }
}

bool DepGraph::local_make(long time, GraphNode *p){
    //Run make helper function, takes a target graphNode and its timestamp as arguments.
    //If graphNode has no dependent nodes and does not exist, outputs an error messege.
    for (int i = 0; i < p->numDependentNodes(); i++){
        if (p->dependentNodes()->at(i)->numDependentNodes() == 0 && p->dependentNodes()->at(i)->getTimeStamp() == -1){
            cout << "error " << p->dependentNodes()->at(i)->getName() << "dose not exist" << endl;
            exit(1);
        }
        if (time == -1 || time < p->dependentNodes()->at(i)->getTimeStamp())
            return true;
    }
    return false;
}

bool DepGraph::isCyclic(GraphNode *g){
    // Checks if makefile is cyclic
    if (g->onPath())
        return true;
    g->onPath(true);
    for (int i = 0; i < g->numDependentNodes(); i++)
        if(isCyclic(g->dependentNodes()->at(i)))
            return true;
    g->onPath(false);
    return false;
}

Token DepGraph::readAndProcessDependencyPair(Reader *reader){
    Token target = reader->getToken();
    if (target.isEOF())
        return target;
    if(!target.isName()) {
        cout << "The first token of a dependency line should be a name-token.\n";
        exit(1);
    }
    //cout << "Target is: " << target.getName() << endl;
    Token colon = reader->getToken();
    if( ! colon.isColon() ) {
        cout << "Missing colon character on the dependency line.\n";
        exit(1);
    }
    // add target to tree
    GraphNode *tar = nullptr;
    if (firstTarget == nullptr){
        firstTarget = new GraphNode(target.getName());
        _tree->insert(firstTarget);
    }
    if (_tree->find(target.getName()) == nullptr){
        tar = new GraphNode(target.getName());
        _tree->insert(tar);
    }
    else
        tar =  _tree->find(target.getName());
    
    //cout << "The following file-names depend on the above target.\n";
    Token token;
    token = reader->getToken();
    while (token.isName()){
        // add dependent nodes to tree
        GraphNode *dep;
        if (_tree->find(token.getName()) == nullptr){
            dep = new GraphNode(token.getName());
            _tree->insert(dep);
        } else
            dep = _tree->find(token.getName());
        //add dependent nodes to target graphnode vector
        tar->addDependentNode(dep);
        if (token.isName())
            //cout << token.getName() << endl;
        token = reader->getToken();
    }
    
    if( ! token.isEOL() ) {
        cout << "Dependency line contains a non-name token.\n";
        exit(1);
    }
    token = reader->getToken();
    if (!token.isCommand()) {
        cout << "No command found after dependency line.\n";
        exit(1);
    }
    //cout << "The command is: " << token.getCommand() << endl;
    tar->setCommand(token.getCommand());
    return token;
}