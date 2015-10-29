#include <iostream>
#include "console.h"
#include "simpio.h"
#include "set.h"
using namespace std;

int CountSubsetSumWays(Set<int>& set, int target);

int main()
{
    Set<int> sample_set;
    sample_set += 1, 3, 4, 5, 22;

    while(true)
    {
       int target = getInteger("Enter target:");

       cout << CountSubsetSumWays(sample_set, target) << endl;
    }

   return 0;
}

int CountSubsetSumWays(Set<int>& set, int target)
{
    int num_solution = 0;

    if (set.first() == target)
    {
        num_solution += 1;
    }

    if (set.size() > 1)
    {
        Set<int> subset = set;
        int first = subset.first();
        subset -= first;

        num_solution += CountSubsetSumWays(subset, target);
        num_solution += CountSubsetSumWays(subset, target - first);
    }

    return num_solution;
}
