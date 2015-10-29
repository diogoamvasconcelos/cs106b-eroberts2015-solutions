#include <iostream>
#include <cassert>
#include "simpio.h"
#include "console.h"
#include "intarray.h"

using namespace std;

int main()
{
    IntArray array(10);
    assert(array.Size() == 10);
    assert(array.Get(0) == 0);
    assert(array.Get(9) == 0);

    array.Put(9, 10);
    assert(array.Get(9) == 10);
    assert(array[9] == 10);

    array[9] = 99;
    assert(array[9] == 99);

    IntArray other_array(0);
    assert(other_array.Size() == 0);
    other_array = array;
    assert(other_array.Size() == 10);
    assert(other_array[9] == 99);

    cout << "IntArray unit testing succeeded" << endl;
    return 0;
}
