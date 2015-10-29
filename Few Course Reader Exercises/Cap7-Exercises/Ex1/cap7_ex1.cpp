#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int NumberOfSpheres(int n);

int main()
{
    while(true)
    {
        int n = getInteger("n?");

        if (n < 0)
            break;

        cout << "c = " << NumberOfSpheres(n) << endl;
    }

   return 0;
}

int NumberOfSpheres(int n)
{
    if(n == 0)
        return 1;

    return NumberOfSpheres(n - 1) + (n + 1) * (n + 1);
}
