#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

bool IsMeasurable (Vector<int>& weights, int target);

int main()
{
    Vector<int> sample_weights;
    sample_weights += 1, 3;

    while(true)
    {
       int target = getInteger("Enter target:");

       cout << IsMeasurable(sample_weights, target) << endl;
    }

   return 0;
}

bool IsMeasurable (Vector<int>& weights, int target)
{
    if (weights[0] == target)
    {
        return true;
    }
    else if (weights.size() > 1)
    {
        Vector<int> weights_subset = weights;
        int first_weight = weights_subset[0];
        weights_subset.remove(0);

        if(IsMeasurable(weights_subset, target))
            return true;

        if(IsMeasurable(weights_subset, target - first_weight))
            return true;

        if(IsMeasurable(weights_subset, target + first_weight))
            return true;
    }

    return false;
}
