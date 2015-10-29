#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int RaiseToPower(int n, int k);

int main()
{
    while(true)
    {
        int n = getInteger("Enter n:");
        int k = getInteger("Enter k:");

        if( k < 0)
            continue;

        cout << RaiseToPower(n, k) << endl;
    }

   return 0;
}


int RaiseToPower(int n, int k)
{
    if(k == 0)
    {
        return 1;
    }

    return n * RaiseToPower(n, k-1);
}
