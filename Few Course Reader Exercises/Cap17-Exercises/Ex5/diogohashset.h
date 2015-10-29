#ifndef DIOGOHASHSET_H
#define DIOGOHASHSET_H
#include "error.h"

class DiogoHashSet
{
public:
    DiogoHashSet();
    ~DiogoHashSet();

     int size() const;
     bool isEmpty() const;

     void add(int value);
     void remove(int value);
     bool contains(int value) const;
     void clear();

     DiogoHashSet(const DiogoHashSet & src);
     DiogoHashSet operator=(const DiogoHashSet & src);

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

     /* Type used for each heap entry - Cell */
        struct Cell
        {
           int value;
           Cell *link;
        };

     /* Constants */
     static const int INITIAL_NUMBER_OF_BUCKETS = 13;
     const int HASH_MULTIPLIER = 2654435761;
     const int HASH_MOD = 2^32;

     /* Instance variables */
     int count;
     int num_buckets;
     Cell **buckets;

     /* Private methods */
     Cell *findCell(int bucket, int value) const
     {
         Cell *cp = buckets[bucket];

         while (cp != NULL)
         {
             if(cp->value == value)
                 break;

             cp = cp->link;
         }

         return cp;
     }

     //source https://gist.github.com/badboy/6267743, Knuth's Multiplicative Method
     int getHash(int value) const
     {
       return value*HASH_MULTIPLIER % HASH_MOD;
     }

     void deepCopy(const DiogoHashSet & src)
     {
         count = src.count;
         num_buckets = src.num_buckets;
         buckets = new Cell*[num_buckets];

         for (int i = 0; i < num_buckets; ++i)
         {
             buckets[i] = NULL;

             for (Cell *cp = src.buckets[i]; cp != NULL; cp = cp->link)
             {
                Cell *new_cp = new Cell();
                new_cp->value = cp->value;
                new_cp->link = NULL;
                buckets[i] = new_cp;
             }
         }
     }
};

#endif // DIOGOHASHSET_H
