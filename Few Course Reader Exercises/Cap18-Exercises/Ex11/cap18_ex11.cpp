#include <iostream>
#include "simpio.h"
#include "console.h"
#include "graph.h"
#include "vector.h"
#include "map.h"
#include "diogographnodearc.h"

using namespace std;

void readGraph(Graph<DiogoNode, DiogoArc> & g, istream & infile);
void populateHardcodedGraph(Graph<DiogoNode, DiogoArc> & g);
void addUndirectedArcWithCost(Graph<DiogoNode, DiogoArc> & g, string start, string end, int cost);
Vector<DiogoArc *> dijkstraFindShortestPath(DiogoNode *start, DiogoNode* finish);
int getPathCost(Vector<DiogoArc *> path);

int main()
{
    Graph<DiogoNode, DiogoArc> g;
    populateHardcodedGraph(g);

    while(true)
    {
        string start = getLine("Enter start:");
        string finish = getLine("Enter finish:");

        for (DiogoArc *arc: dijkstraFindShortestPath(g.getNode(start), g.getNode(finish)))
        {
            cout << arc->getStart()->getName().c_str() << "->" << arc->getFinish()->getName().c_str() << endl;
        }

        cout << "----------" << endl;
    }

    return 0;
}

void readGraph(Graph<DiogoNode, DiogoArc> & g, istream & infile)
{
    //TODO
}

void populateHardcodedGraph(Graph<DiogoNode, DiogoArc> & g)
{
    g.addNode("Atlanta");
    g.addNode("Boston");
    g.addNode("Chicago");
    g.addNode("Dallas");
    g.addNode("Denver");
    g.addNode("Los Angeles");
    g.addNode("New York");
    g.addNode("Portland");
    g.addNode("San Francisco");
    g.addNode("Seattle");

    addUndirectedArcWithCost(g, "Atlanta", "Chicago", 599);
    addUndirectedArcWithCost(g, "Atlanta", "Dallas", 725);
    addUndirectedArcWithCost(g, "Atlanta", "New York", 756);
    addUndirectedArcWithCost(g, "Boston", "New York", 191);
    addUndirectedArcWithCost(g, "Boston", "Seattle", 2489);
    addUndirectedArcWithCost(g, "Chicago", "Denver", 907);
    addUndirectedArcWithCost(g, "Dallas", "Denver", 650);
    addUndirectedArcWithCost(g, "Dallas", "Los Angeles", 1240);
    addUndirectedArcWithCost(g, "Dallas", "San Francisco", 1468);
    addUndirectedArcWithCost(g, "Denver", "San Francisco", 954);
    addUndirectedArcWithCost(g, "Portland", "San Francisco", 550);
    addUndirectedArcWithCost(g, "Portland", "Seattle", 130);
}

void addUndirectedArcWithCost(Graph<DiogoNode, DiogoArc> & g, string start, string end, int cost)
{
    g.addArc(start, end)->setCost(cost);
    g.addArc(end, start)->setCost(cost);
}

Vector<DiogoArc *> dijkstraFindShortestPath(DiogoNode *start, DiogoNode* finish)
{
    Vector<DiogoArc *> path;
    SimplePiorityQueue<Vector<DiogoArc *>> queue;
    Map<string, int> fixed;

    while (start != finish)
    {
        if (!fixed.containsKey(start->getName())) //If hasnt reached this node, meaning is the shortest/first path to this
        {
            fixed.add(start->getName(), getPathCost(path)); //Cached the visited node, with the current path cost because its the lowest (first one to arrive)

            for (DiogoArc *arc: *(start->getArcs())) //Queue up the next nodes to continue the checking, having the cost as the priority so the next path dequeued is the closest one
            {
                path.add(arc);
                queue.enqueue(path, getPathCost(path));
                path.remove(path.size() - 1);
            }
        }
        if(queue.isEmpty()) //went through all the arcs and paths and didnt reach the finish node
        {
            path.clear();
            return path; //return empty path;
        }

        path = queue.dequeue();
        start = path[path.size() - 1]->getFinish(); //change the start to the last node reached and continue the search for the finish node
    }
    return path;
}

int getPathCost(Vector<DiogoArc *> path)
{
    int cost = 0;

    for(DiogoArc * arc: path)
        cost += arc->getCost();

    return cost;
}