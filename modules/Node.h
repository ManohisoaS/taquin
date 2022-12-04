#ifndef NODE_H
#define NODE_H
#include <list>
using namespace std;

class Node
{
public:
    string label;
    string parent;
    list<string> neighbords;
};

#endif

