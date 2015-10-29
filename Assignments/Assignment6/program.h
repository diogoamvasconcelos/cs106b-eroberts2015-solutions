/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include "statement.h"
using namespace std;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

   void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */

   void addSourceLine(int lineNumber, std::string line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

   void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */

   std::string getSourceLine(int lineNumber) const;

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 */

   void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */

   Statement *getParsedStatement(int lineNumber) const;

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

   int getFirstLineNumber() const;

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

   int getNextLineNumber(int lineNumber) const;

private:

//Because the getParsedStatement and getSourceLine methods need to be run at constant time, a hash table will be used.
//Each cell of the table buckets will also have a pointer to the next statement to be executed,
//creating a parallel linked list containing the cells of all buckets, to enable constant time
//in the getFirstLineNumber and getNextLineNumber because the order of the cells will be well defined by the linked list


    //Cell struct that contains the data of each line
   struct CellLine
   {
       int number;
       string source;
       Statement* statement;
       CellLine* link;
       CellLine* link_in_bucket;
   };

   /* Constants */
    static const int INITIAL_NUMBER_OF_BUCKETS = 13;
    const int HASH_MULTIPLIER = 2654435761;
    const int HASH_MOD = 2^32;
    const double MAX_LOAD_FACTOR = 0.7;

    /* Instance variables */
   CellLine **buckets;
   int num_buckets;
   int count;
   CellLine *head;    //Linked list first element - head

   //Calculate an hash from an integer
   //source https://gist.github.com/badboy/6267743, Knuth's Multiplicative Method
   int getHash(int value) const
   {
        return value * HASH_MULTIPLIER % HASH_MOD;
   }

   //Get line
   CellLine *getLine(int number) const
   {
       CellLine *cp = NULL;
       int bucket_number = getHash(number) & num_buckets;
       for (CellLine *bucket_cp = buckets[bucket_number]; bucket_cp != NULL; bucket_cp = bucket_cp->link_in_bucket)
       {
            if(bucket_cp->number == number)
            {
                cp = bucket_cp;
                break;
            }
       }

       return cp;
   }

   //Deep copy
   /*
   void deepCopy(const Program & src, int new_num_buckets)
    {
        num_buckets = new_num_buckets;
        count = src.count;
        buckets = new CellLine*[num_buckets];
        head = NULL;
        for (int i = 0; i < num_buckets; ++i)
        {
            buckets[i] = NULL;
        }

        CellLine* tail = NULL;
        for (CellLine *cp = src.head; cp != NULL; cp = cp->link)
        {
            //Create the new Line
            CellLine *new_cp = new CellLine();
            new_cp->number = cp->number;
            new_cp->source = cp->source;

            //Create a new copied statement
            Statement *new_statement = new Statement();
            *new_statement = *(cp->statement);
            new_cp->statement = new_statement;

            //Insert line in correct bucket
            int bucket_number = getHash(cp->number) & num_buckets;
            CellLine * & bucket = buckets[bucket_number];
            new_cp->link_in_bucket = bucket;
            bucket = new_cp;

            //Insert line in linked list
            new_cp->link = NULL;
            tail->link = new_cp;
            tail = new_cp;
            if(head == NULL)
                head = new_cp;
        }
    }
    */

   //Capacity check. If load factor higher than MAX_LOAD_FACTOR, increase num_buckets and copy/recreate the table again
   void CheckCapacity()
   {
       if (count / (double)num_buckets > MAX_LOAD_FACTOR)
       {
            int new_num_buckets = num_buckets;
            while(count / new_num_buckets > MAX_LOAD_FACTOR)
            {
                new_num_buckets *= 2;
            }

            /*
            Program copy(*this);
            deepCopy(copy, new_num_buckets);
            */
       }
   }
};

#endif
