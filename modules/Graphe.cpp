#include "Graphe.h"

void Graphe::addNode(Node node)
{
    this->graphe.insert({node.label, node});
}
Node Graphe::get(string label)
{
    return this->graphe[label];
}

