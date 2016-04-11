#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include "systemInterface.hpp"

using namespace std;

class GraphNode {
public:
    GraphNode( string name );
    string getName()                        {return _name;}
    void setName(string name)               { _name = name;}
    void setTimeStamp(long ts)              { _timeStamp = ts;}
    long getTimeStamp()                     {return _timeStamp;}
    vector<GraphNode *> *dependentNodes()   {return _listOfDependentNodes;}
    void setCommand(string cmnd)            {_command = cmnd;}
    string getCommand()                     {return _command;}
    void runCommand();  // execute the command associated with this node.
    void addDependentNode(GraphNode *child) {_listOfDependentNodes->push_back(child);}
    bool onPath()                           {return _onPath;}
    void onPath(bool v)                     {_onPath = v;}
    bool wasMade()                          {return _wasMade;}
    void wasMade(bool v)                    {_wasMade = v;}
    bool isATarget()                        {return _isATarget;}
    void isATarget(bool v)                  {_isATarget = v;}
    int numDependentNodes()                 {return _listOfDependentNodes->size();}
    void print();

private:
    string _name, _command;
    long _timeStamp;
    vector<GraphNode *> *_listOfDependentNodes;

    bool _onPath, _isATarget, _wasMade;
};
