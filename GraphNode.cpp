//  Created by Eugene Rivera on 11/18/15.

#include "GraphNode.hpp"

GraphNode::GraphNode(string name){
    _name = name;
    _command = "";
    _timeStamp = 0;
    _listOfDependentNodes = new vector<GraphNode *> ();
    _onPath = _isATarget = _wasMade = 0;
}

void GraphNode::runCommand(){
    executeCommand(_command.c_str());
}

void GraphNode::print(){
    cout << getName() << " Timestamp: " << getTimeStamp() << " List of dependent nodes: " << endl;
    for (int i = 0; i < numDependentNodes(); i++)
        cout << _listOfDependentNodes->at(i)->getName() << " Timestamp: " << _listOfDependentNodes->at(i)->getTimeStamp() << endl;
}