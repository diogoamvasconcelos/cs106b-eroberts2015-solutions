/*
 * File: pqueue.h (array version)
 * ------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file exports the PriorityQueue class, a collection in which
 * values are processed in priority order.  The public section of the
 * class is common to all implementations of the queue, but the private
 * section is tailored to the array-based implementation.
 * [TODO: extend the documentation]
 */

#ifndef _pqueue_h
#define _pqueue_h

#include "error.h"

/*
 * Class: PriorityQueue
 * -----------------------
 * This class models a structure called a priority queue in which
 * values are processed in order of priority.  As in conventional
 * English usage, lower priority numbers correspond to higher effective
 * priorities, so that a priority 1 item takes precedence over a
 * priority 2 item.
 */

class PriorityQueue {

public:

/*
 * Constructor: PriorityQueue
 * Usage: PriorityQueue pq;
 * ---------------------------
 * Initializes a new priority queue, which is initially empty.
 */

   PriorityQueue();

/*
 * Destructor: ~PriorityQueue
 * --------------------------
 * Frees any array storage associated with this priority queue.
 */

   ~PriorityQueue();

/*
 * Method: size
 * Usage: int n = pq.size();
 * -------------------------
 * Returns the number of values in the priority queue.
 */

   int size();

/*
 * Method: isEmpty
 * Usage: if (pq.isEmpty()) ...
 * ----------------------------
 * Returns true if the priority queue contains no elements.
 */

   bool isEmpty();

/*
 * Method: clear
 * Usage: pq.clear();
 * ------------------
 * Removes all elements from the priority queue.
 */

   void clear();

/*
 * Method: enqueue
 * Usage: pq.enqueue(value, priority);
 * -----------------------------------
 * Adds value to the queue with the specified priority.  Lower priority
 * numbers correspond to higher priorities, which means that all
 * priority 1 elements are dequeued before any priority 2 elements.
 * If not specified, the priority is set to 1.
 */

   void enqueue(std::string value, double priority = 1);

/*
 * Method: dequeue
 * Usage: std::string first = pq.dequeue();
 * ------------------------------
 * Removes and returns the highest priority value.  If multiple
 * entries in the queue have the same priority, those values are
 * dequeued in the same order in which they were enqueued.
 */

   std::string dequeue();

/*
 * Method: peek
 * Usage: std::string first = pq.peek();
 * ---------------------------
 * Returns the value of highest priority in the queue, without
 * removing it.
 */

   std::string peek();

/*
 * Method: peekPriority
 * Usage: double priority = pq.peekPriority();
 * -------------------------------------------
 * Returns the priority of the first element in the queue, without
 * removing it.
 */

   double peekPriority();

/*
 * Method: copy constructor
 * ------------------------
 * The copy constructor makes it possible to pass a PriorityQueue by value.
 * Its signature follows a standard pattern for all copy constructors.
 */

   PriorityQueue(const PriorityQueue & src);

/*
 * Method: assignment operator
 * ---------------------------
 * The assignment operator makes it possible to assign a PriorityQueue.
 * Its signature follows a standard pattern for all assignment operators.
 */

   PriorityQueue & operator=(const PriorityQueue & src);

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

/* Type used for each heap entry */

   struct ValuePriorityPair {
      std::string value;
      double priority;
   };

/* Constants */

   static const int INITIAL_CAPACITY = 10;

/* Instance variables */

   ValuePriorityPair *array;
   int count;
   int capacity;
   int head;

/* Private methods */

   void expandCapacity()
   {
      ValuePriorityPair *old_array = array;
      int old_capacity = capacity;
      capacity *= 2;
      array = new ValuePriorityPair[capacity];
      for (int i = 0; i < count; i++)
      {
         array[i] = old_array[(head + i) % old_capacity];
      }
      head = 0;
      delete[] old_array;
   }

   void deepCopy(const PriorityQueue & src)
   {
      count = capacity = src.count;
      head = 0;
      if (capacity < INITIAL_CAPACITY) capacity = INITIAL_CAPACITY;
      array = new ValuePriorityPair[capacity];
      for (int i = 0; i < count; i++) {
         array[i] = src.array[(src.head + i) % src.capacity];
      } 
   }

};

#endif
