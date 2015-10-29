#include <iostream>
#include "simpio.h"
#include "console.h"

using namespace std;

int* CreateIndexArray(const int n);

int main()
{
    int n  = 20;
    int *array = CreateIndexArray(n);

    for (int i = 0; i < n; ++i)
    {
        cout << *(array + i) << endl;
    }

    return 0;
}

int* CreateIndexArray(const int n)
{
    int *array = new int[n];

    for (int *curr = array; curr - array < n; curr++)
    {
        *curr = curr - array;
    }

    return array;
}
