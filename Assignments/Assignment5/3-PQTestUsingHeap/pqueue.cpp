/*
 * File: pqueue.cpp (heap version)
 * -------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a heap as the
 * underlying representation.  Only the copy constructor and assignment
 * operator are included.  Your job is to include definitions for the
 * other exported methods and to make a change to the definition of the
 * assignment operator so that it deletes any old storage.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;



/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow a standard paradigm,
 * as described in the textbook.
 */

PriorityQueue::PriorityQueue()
{
    capacity = INITIAL_CAPACITY;
    count = 0;
    array = new HeapNode[capacity];
}

PriorityQueue::~PriorityQueue()
{
    delete[] array;
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
    count = 0;
}

void PriorityQueue::enqueue(string value, double priority)
{
    //Inser new Node into bottom most space (left to right)
    HeapNode newNode;
    newNode.priority = priority;
    newNode.value = value;

    array[count++] = newNode;

    //Fix the inbalance, corrtly positioning the inserted node
    fixEnqueueSubTreeInbalance(count - 1);
}

string PriorityQueue::dequeue()
{
   if(isEmpty())
   {
        error("dequeue: Attempting to dequeue an empty queue");
   }

   string result = array[0].value;
   swapNodes(array[0], array[--count]); //swap root with bottom rightmost value, decreasing count so the old root is "removed" from array

   fixDequeueSubTreeInbalance(0); //fix inbalance starting in the root node

   return result;
}

string PriorityQueue::peek()
{
    if(isEmpty())
    {
         error("peek: Attempting to peek an empty queue");
    }

   return array[0].value;
}

double PriorityQueue::peekPriority()
{
    if(isEmpty())
    {
         error("peekPriority: Attempting to peekPriority an empty queue");
    }

   return array[0].priority;
}

PriorityQueue::PriorityQueue(const PriorityQueue & src)
{
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src)
{
   if (this != &src)
   {
      delete[] array;
      deepCopy(src);
   }
   return *this;
}
