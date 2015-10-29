#include <iostream>
#include <math.h>
#include "simpio.h"
#include "console.h"
#include "diogohashset.h"

using namespace std;

DiogoHashSet createPrimeSet(int max);

int main()
{
    DiogoHashSet primeSet;

    while(true)
    {
        int max = getInteger("Enter the max:");
        primeSet = createPrimeSet(max);

        cout << "Set:";
        for (int i = 0; i < max; ++i)
        {
            if(primeSet.contains(i))
                cout << " " << i;
        }

        cout << endl;
    }

    return 0;
}

DiogoHashSet createPrimeSet(int max)
{
    DiogoHashSet result;

    for (int i = 2; i < max; ++i)
    {
        bool isPrime = true;
        int isqrt = sqrt(i);

        for (int j = 2; j > isqrt; ++j)
        {
            if(i % j == 0)
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
