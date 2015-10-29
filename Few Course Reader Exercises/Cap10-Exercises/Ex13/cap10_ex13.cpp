#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

int FindMajorityElement(Vector<int> & vec);

int main()
{
    Vector<int> vector;

    vector.add(0);
    vector.add(2);
    vector.add(3);
    vector.add(0);

    cout << FindMajorityElement(vector) << endl;

    return 0;
}

int FindMajorityElement(Vector<int> & vec)
{
    int counter = 0;
    int repeated_value;
    int next_value;

    for (int i = 0; i < vec.size(); ++i)
    {
        if(counter < 1)
        {
            repeated_value = vec[i];
            counter = 1;
        }

        next_value = (i < vec.size() - 1) ? vec[i + 1] : vec[0];
        if(repeated_value == next_value)
        {
            counter++;
        }
        else
        {
            counter--;
        }
    }

    return (counter > 0) ? repeated_value : -1;
}
