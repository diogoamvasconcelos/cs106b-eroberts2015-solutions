#ifndef DIOGOGRAPHNODEARC_H
#define DIOGOGRAPHNODEARC_H

#include "set.h"

class DiogoNode;
class DiogoArc;
template<typename Typename>
class SimplePiorityQueue;

class DiogoNode
{

public:
    std::string getName()
    {
        return name;
    }

    Set<DiogoArc *> *getArcs()
    {
        return &arcs;
    }

private:
    std::string name;
    Set<DiogoArc *> arcs;
    friend class Graph<DiogoNode, DiogoArc>;
};

class DiogoArc
{

public:
    int getCost()
    {
        return cost;
    }

    void setCost(int new_cost)
    {
        cost = new_cost;
    }

    DiogoNode * getStart()
    {
        return start;
    }

    DiogoNode * getFinish()
    {
        return finish;
    }

private:
    int cost;
    DiogoNode *start;
    DiogoNode *finish;
    friend class Graph<DiogoNode, DiogoArc>;
};

template<typename Typename>
class SimplePiorityQueue
{
public:
    void enqueue(Typename value, double priority)
    {
        value_vector.add(value);
        priority_vector.add(priority);
    }

    Typename dequeue()
    {
        int most_urgent_index = 0;
        int prev_priority = INT_MAX;
        for (int i = 0; i < priority_vector.size(); ++i)
        {
            if(priority_vector[i] < prev_priority)
            {
                most_urgent_index = i;
                prev_priority = priority_vector[i];
            }
        }

        Typename result = value_vector[most_urgent_index];

        value_vector.remove(most_urgent_index);
        priority_vector.remove(most_urgent_index);

        return result;
    }

    bool isEmpty() const
    {
        return value_vector.isEmpty();
    }

private:
    Vector<Typename> value_vector;
    Vector<double> priority_vector;
};

#endif // DIOGOGRAPHNODEARC_H
