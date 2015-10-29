#include "intarray.h"
#include "error.h"

IntArray::IntArray()
{
    //capacity = INITIAL_CAPACITY;
    count = 0;
    array = new int[count];
}

IntArray::IntArray(int n)
{
    //capacity = INITIAL_CAPACITY;
    count = n;
    array = new int[count];

    for (int *curr = array; curr - array < count; curr++)
    {
        *curr = 0;
    }
}

IntArray::~IntArray()
{
    delete[] array;
}

int IntArray::Size() const
{
    return count;
}

int IntArray::Get(int k) const
{
    if (k < 0 || k >= count)
        error("Get: Index is out of bounds.");

    return *(array + k);
}

void IntArray::Put(int k, int value)
{
    if (k < 0 || k >= count)
        error("Get: Index is out of bounds.");

    *(array + k) = value;
}

int & IntArray::operator[](int k)
{
    if (k < 0 || k >= count)
        error("Get: Index is out of bounds.");

    return *(array + k);
}
IntArray & IntArray::operator =(const IntArray & src)
{
    delete[] array;
    count = src.count;
    array = new int[count];

    for (int i = 0; i < count; i++)
    {
        *(array + i) = src.array[i];
    }

    return *this;
}
