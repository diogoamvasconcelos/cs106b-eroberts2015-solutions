#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

double GetTitiusBodeDistance(int k);

int main()
{
    while(true)
    {
        int k = getInteger("Enter k:");

        cout << GetTitiusBodeDistance(k) << endl;
    }

   return 0;
}

double GetTitiusBodeDistance(int k)
{
    int b;

    if(k == 1)
    {
        b = 1;
    }
    else if(k == 2)
    {
        b = 3;
    }
    else
    {
        b = ((GetTitiusBodeDistance(k - 1) * 10) - 4) * 2;
    }

    return (b + 4) / 10.0;
}
