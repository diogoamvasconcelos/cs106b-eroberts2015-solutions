/*
 * File: pqueue.cpp (linked-list version)
 * --------------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a linked list as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue()
{
    count = 0;
    head = NULL;
}

PriorityQueue::~PriorityQueue()
{
   clear();
}

int PriorityQueue::size()
{
   return count;
}

bool PriorityQueue::isEmpty()
{
   return count == 0;
}

void PriorityQueue::clear()
{
    Cell *cell = head;
    while(cell != NULL)
    {
        Cell *next_cell = cell->link;
        delete cell;
        cell = next_cell;
    }
    count = 0;
    head = NULL;
}

void PriorityQueue::enqueue(string value, double priority)
{
    // Find cell to insert
    Cell *cell_to_insert_after = NULL;
    for (Cell *cell = head; cell != NULL; cell = cell->link)
    {
         if(priority < cell->priority)
             break;

         cell_to_insert_after = cell;
    }

    // Insert new cell
    count++;
    Cell *new_cell = new Cell();
    new_cell->priority = priority;
    new_cell->value = value;

    if(cell_to_insert_after == NULL)
    {
        new_cell->link = head;
        head = new_cell;
    }
    else
    {
        new_cell->link = cell_to_insert_after->link;
        cell_to_insert_after->link = new_cell;
    }
}

std::string PriorityQueue::dequeue()
{
    if(isEmpty())
    {
        error("dequeue: Trying to dequeue from an empty queue");
    }

    Cell *cell = head;
    head = head->link;
    std::string result = cell->value;
    delete cell;
    count--;

    return result;
}

std::string PriorityQueue::peek()
{
    if(isEmpty())
    {
        error("dequeue: Trying to dequeue from an empty queue");
    }

    return head->value;
}

double PriorityQueue::peekPriority()
{
    if(isEmpty())
    {
        error("dequeue: Trying to dequeue from an empty queue");
    }

    return head->priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      clear();
      deepCopy(src);
   }
   return *this;
}
