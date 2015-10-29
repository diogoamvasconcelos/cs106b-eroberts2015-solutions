#include <iostream>
#include <math.h>
#include "simpio.h"
#include "console.h"
#include "set.h"

using namespace std;

Set<int> createPrimeSet(int max);

int main()
{
    Set<int> primeSet;

    while(true)
    {
        int max = getInteger("Enter the max:");
        primeSet = createPrimeSet(max);

        cout << "Set:";
        for (Set<int>::iterator iter = primeSet.begin(); iter != primeSet.end(); ++iter)
        {
             cout << " " << *iter;
        }

        cout << endl;
    }

    return 0;
}

Set<int> createPrimeSet(int max)
{
    Set<int> result;

    for (int i = 2; i < max; ++i)
    {
        bool isPrime = true;
        int isqrt = sqrt(i);

        for (int prime : result)
        {
            if(prime > isqrt)
                break;

            if(i % prime == 0)
            {
                isPrime = false;
                break;
            }
        }

        if(isPrime)
            result.add(i);
    }

    return result;
}
