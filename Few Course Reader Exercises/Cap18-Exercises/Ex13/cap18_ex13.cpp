#include <iostream>
#include "simpio.h"
#include "console.h"
#include "graph.h"
#include "vector.h"
#include "map.h"
#include "diogographnodearc.h"

using namespace std;

void populateHardcodedGraph(Graph<DiogoNode, DiogoArc> & g);
void addUndirectedArcWithCost(Graph<DiogoNode, DiogoArc> & g, string start, string end, int cost);
Graph<DiogoNode, DiogoArc> kruskalFindMinimumSpanningTree(Graph<DiogoNode, DiogoArc> & g);
int getPathCost(Vector<DiogoArc *> path);
bool areConnected(DiogoNode *nodeA, DiogoNode *nodeB, Set<DiogoNode *> visited);

int main()
{
    Graph<DiogoNode, DiogoArc> g;
    populateHardcodedGraph(g);

    Graph<DiogoNode, DiogoArc> minSpanningTree = kruskalFindMinimumSpanningTree(g);

    cout << "Node:" << endl;
    for (DiogoNode *node: minSpanningTree.getNodeSet())
    {
        cout << node->getName().c_str() << endl;
    }

    cout << "------" << endl;

    cout << "Arcs:" << endl;
    for (DiogoArc *arc: minSpanningTree.getArcSet())
    {
        cout << arc->getStart()->getName().c_str() << "-" << arc->getFinish()->getName().c_str() << endl;
    }

    return 0;
}

void populateHardcodedGraph(Graph<DiogoNode, DiogoArc> & g)
{
    g.addNode("San Rafael");
    g.addNode("Vallejo");
    g.addNode("Berkeley");
    g.addNode("San Francisco");
    g.addNode("Oakland");
    g.addNode("Hayward");
    g.addNode("Palo Alto");
    g.addNode("Fremont");
    g.addNode("Sunnyvale");
    g.addNode("San Jose");

    addUndirectedArcWithCost(g, "San Rafael", "Vallejo", 28);
    addUndirectedArcWithCost(g, "San Rafael", "Berkeley", 30);
    addUndirectedArcWithCost(g, "Vallejo", "Berkeley", 22);
    addUndirectedArcWithCost(g, "San Rafael", "San Francisco", 19);
    addUndirectedArcWithCost(g, "Berkeley", "Oakland", 10);
    addUndirectedArcWithCost(g, "San Francisco", "Oakland", 19);
    addUndirectedArcWithCost(g, "Oakland", "Hayward", 10);
    addUndirectedArcWithCost(g, "San Francisco", "Palo Alto", 19);
    addUndirectedArcWithCost(g, "Hayward", "Fremont", 10);
    addUndirectedArcWithCost(g, "Palo Alto", "Fremont", 21);
    addUndirectedArcWithCost(g, "Palo Alto", "Sunnyvale", 15);
    addUndirectedArcWithCost(g, "Sunnyvale", "Fremont", 13);
    addUndirectedArcWithCost(g, "Sunnyvale", "San Jose", 11);
    addUndirectedArcWithCost(g, "Fremont", "San Jose", 11);
}

void addUndirectedArcWithCost(Graph<DiogoNode, DiogoArc> & g, string start, string end, int cost)
{
    g.addArc(start, end)->setCost(cost);
    g.addArc(end, start)->setCost(cost);
}

Graph<DiogoNode, DiogoArc> kruskalFindMinimumSpanningTree(Graph<DiogoNode, DiogoArc> & g)
{
    Graph<DiogoNode, DiogoArc> minSpanningTree;

    //Get a list of arcs of increasing cost
    SimplePiorityQueue<DiogoArc *> queue;
    for (DiogoArc *arc: g.getArcSet())
    {
        queue.enqueue(arc, arc->getCost());
    }

    //Set to keep track of already added nodes
    Set<string> addedNodes;

    while(!queue.isEmpty())
    {
        DiogoArc *arc = queue.dequeue();

        //Add node if not added already
        if(!addedNodes.contains(arc->getStart()->getName()))
        {
            addedNodes.add(minSpanningTree.addNode(arc->getStart()->getName())->getName());
        }

        //Add node if not added already
        if(!addedNodes.contains(arc->getFinish()->getName()))
        {
            addedNodes.add(minSpanningTree.addNode(arc->getFinish()->getName())->getName());
        }

        //Add arc if not connected already
        Set<DiogoNode *> visited;
        if(!areConnected(minSpanningTree.getNode(arc->getStart()->getName()), minSpanningTree.getNode(arc->getFinish()->getName()), visited))
        {
            addUndirectedArcWithCost(minSpanningTree, arc->getStart()->getName(), arc->getFinish()->getName(), arc->getCost());
        }
    }

    return minSpanningTree;
}

//Deep first search algorithm
bool areConnected(DiogoNode *nodeA, DiogoNode *nodeB, Set<DiogoNode *> visited)
{
    if(visited.contains(nodeA))
        return false;

    visited.add(nodeA);

    for (DiogoArc *arc: nodeA->getArcs())
    {
        if(arc->getFinish() == nodeB)
            return true;

        if(areConnected(arc->getFinish(), nodeB, visited))
            return true;
    }

    return false;
}