/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program()
{
    num_buckets = INITIAL_NUMBER_OF_BUCKETS;
    buckets = new CellLine*[num_buckets];
    head = NULL;
    for (int i = 0; i < num_buckets; ++i)
    {
        buckets[i] = NULL;
    }
    count = 0;
}

Program::~Program()
{
    clear();
    delete[] buckets;
}

void Program::clear()
{
    CellLine *cp = head;
    while (cp != NULL)
    {
        CellLine *old_cp = cp;
        cp = cp->link;

        delete old_cp->statement;
        delete old_cp;
    }

    head = NULL;
    for (int i = 0; i < num_buckets; ++i)
    {
        buckets[i] = NULL;
    }
    count = 0;
}

void Program::addSourceLine(int lineNumber, string line)
{
    CellLine *cp = getLine(lineNumber);

    if(cp != NULL) //replace text and delete statement
    {
        cp->source = line;
        if (cp->statement != NULL)
        {
            delete cp->statement;
            cp->statement = NULL;
        }
    }
    else //Add line to program
    {
        //Create line
        cp = new CellLine();
        cp->number = lineNumber;
        cp->source = line;
        cp->statement = NULL;
        count++;

        CheckCapacity();

        //Insert in bucket
        int bucket_number = getHash(cp->number) & num_buckets;
        CellLine * & bucket = buckets[bucket_number];
        cp->link_in_bucket = bucket;
        bucket = cp;

        //Insert in sorted linked list
        CellLine *prev_cp = NULL;
        for (CellLine *next_cp = head; next_cp != NULL; next_cp = next_cp->link)
        {
            if(cp->number < next_cp->number)
                break;

            prev_cp = next_cp;
        }

        if(prev_cp == NULL)
        {
            cp->link = head;
            head = cp;
        }
        else
        {
           cp->link = prev_cp->link;
           prev_cp->link = cp;
        }
    }
}

void Program::removeSourceLine(int lineNumber)
{
    CellLine *cp = NULL;
    CellLine *prev_cp = NULL;
    CellLine *next_cp = NULL;

    //remove from bucket
    int bucket_number = getHash(cp->number) & num_buckets;
    CellLine * & bucket = buckets[bucket_number];
    for (next_cp = bucket; next_cp != NULL; next_cp = next_cp->link_in_bucket)
    {
        if(lineNumber < next_cp->number)
        {
            cp = next_cp;
            break;
        }

        prev_cp = next_cp;
    }

    if(cp == NULL) //return if line doest not exists
        return;

    if(prev_cp == NULL)
    {
        bucket = cp->link;
    }
    else
    {
        prev_cp->link = cp->link;
    }

    //remove from linked list
    prev_cp = NULL;
    for (next_cp = head; next_cp != NULL; next_cp = next_cp->link)
    {
        if(cp == next_cp)
        {
            break;
        }

        prev_cp = next_cp;
    }

    if(prev_cp == NULL)
    {
        head = cp->link;
    }
    else
    {
        prev_cp->link = cp->link;
    }

    delete cp->statement;
    delete cp;

    count--;
}

string Program::getSourceLine(int lineNumber) const
{
    CellLine *cp = getLine(lineNumber);

    if(cp != NULL)
    {
        return cp->source;
    }
    else
    {
        return "";
    }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt)
{
    CellLine *cp = getLine(lineNumber);

    if(cp != NULL)
    {
        if(cp->statement != NULL)
        {
            delete cp->statement;
        }

        cp->statement = stmt;
    }
    else
    {
        error("setParsedStatement: Line does not exist");
    }
}

Statement *Program::getParsedStatement(int lineNumber) const
{
    CellLine *cp = getLine(lineNumber);

    if(cp != NULL)
    {
        return cp->statement;
    }
    else
    {
        return NULL;
    }
}

int Program::getFirstLineNumber() const
{
   return (head != NULL) ? head->number : -1;
}

int Program::getNextLineNumber(int lineNumber) const
{
    CellLine *cp = getLine(lineNumber);

    if(cp != NULL)
    {
        return (cp->link != NULL) ? cp->link->number : -1;
    }
    else
    {
        //TODO, this runs on O(N) linear time. Improvement should transform the linked list in a binary search tree
        cp = head;
        while (cp != NULL)
        {
            if (cp->number > lineNumber)
               break;

            cp = cp->link;
        }

        return (cp != NULL) ? cp->number : -1;
    }
}
