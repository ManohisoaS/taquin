#ifndef GRAPHE_H
#define GRAPHE_H
#include <map>
#include <string>
#include "Node.h"
using namespace std;

class Graphe
{
private:
    map<string, Node> graphe;

public:
    void addNode(Node);
    list<string> getSolveStory();
    Node get(string);
};

#endif
