#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray
{
public:
    IntArray();
    IntArray(int n);
    ~IntArray();

    int Size() const;
    int Get(int k) const;
    void Put(int k, int value);

    int & operator[](int k); //Ex 5
    IntArray & operator=(const IntArray & src); //Ex6

private:
    //static const int INITIAL_CAPACITY = 16;

    int *array;
    //int capacity;
    int count;

    IntArray(const IntArray & src);
};

#endif // INTARRAY_H
