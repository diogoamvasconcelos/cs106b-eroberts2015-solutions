#include "diogohashset.h"

using namespace std;

DiogoHashSet::DiogoHashSet()
{
    count = 0;
    num_buckets = INITIAL_NUMBER_OF_BUCKETS;
    buckets = new Cell*[num_buckets];

    for (int i = 0; i < num_buckets; ++i)
    {
        buckets[i] = NULL;
    }
}

DiogoHashSet::~DiogoHashSet()
{
    clear();
    delete[] buckets;
}

void DiogoHashSet::add(int value)
{
    int bucket = getHash(value) & num_buckets;
    Cell *cp = findCell(bucket, value);

    if(cp == NULL)
    {
        cp = new Cell();
        cp->link = buckets[bucket];
        buckets[bucket] = cp;
    }
    cp->value = value;
}

void DiogoHashSet::remove(int value)
{
    int bucket = getHash(value) & num_buckets;

    Cell *cp = buckets[bucket];
    Cell *prev_cp = NULL;

    while (cp != NULL)
    {
        if(cp->value == value)
            break;

        prev_cp = cp;
        cp = cp->link;
    }

    //remove if contains
    if(cp != NULL)
    {
        if(prev_cp == NULL)
        {
            buckets[bucket] = cp->link;
        }
        else
        {
            prev_cp->link = cp->link;
        }

        delete cp;
        count--;
    }
}

bool DiogoHashSet::contains(int value) const
{
    int bucket = getHash(value) & num_buckets;
    Cell *cp = buckets[bucket];

    return cp != NULL;
}

void DiogoHashSet::clear()
{
    for (int i = 0; i < num_buckets; ++i)
    {
        Cell *cp = buckets[i];
        while (cp != NULL)
        {
            Cell *old_cp = cp;
            cp = cp->link;
            delete old_cp;
        }
    }

    count = 0;
}

int DiogoHashSet::size() const
{
    return count;
}

bool DiogoHashSet::isEmpty() const
{
    return count > 0;
}

DiogoHashSet::DiogoHashSet(const DiogoHashSet & src)
{
    deepCopy(src);
}

DiogoHashSet DiogoHashSet::operator=(const DiogoHashSet & src)
{
    if (this != &src)
    {
        clear();
        delete[] buckets;
        deepCopy(src);
    }

    return *this;
}
