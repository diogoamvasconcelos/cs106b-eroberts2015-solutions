/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
using namespace std;

PriorityQueue::PriorityQueue()
{
    capacity = INITIAL_CAPACITY;
    count = 0;
    head = 0;
    array = new ValuePriorityPair[capacity];
}

PriorityQueue::~PriorityQueue()
{
    delete[] array;
}

int PriorityQueue::size() {
   return count;
}

bool PriorityQueue::isEmpty() {
   return count == 0;
}

void PriorityQueue::clear()
{
    count = 0;
    head = 0;
}

void PriorityQueue::enqueue(string value, double priority)
{
    //Find index to insert
    int index = 0;
    for (index = 0; index < count; ++index)
    {
        if(priority < array[(head + index) % capacity].priority)
            break;
    }

    if(++count == capacity)
        expandCapacity();

    //Move right hand values
    for (int i = count; i > index; --i)
    {
        array[(head + i) % capacity] = array[(head + i - 1) % capacity];
    }

    //insert the value
    ValuePriorityPair new_value;
    new_value.priority = priority;
    new_value.value = value;
    array[(head + index) % capacity] = new_value;
}

string PriorityQueue::dequeue()
{
   if(isEmpty())
   {
        error("dequeue: Attempting to dequeue an empty queue");
   }

   int prev_head = head;
   head = (head + 1) % capacity;
   count--;

   return array[prev_head].value;
}

string PriorityQueue::peek()
{
    if(isEmpty())
    {
         error("peek: Attempting to peek an empty queue");
    }

   return array[head].value;
}

double PriorityQueue::peekPriority()
{
    if(isEmpty())
    {
         error("peekPriority: Attempting to peekPriority an empty queue");
    }

   return array[head].priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   deepCopy(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
