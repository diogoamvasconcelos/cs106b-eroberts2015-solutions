/*
 * File: PQTest.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This is the starter file for the test program for Assignment #5.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "pqueue.h"
#include "simpio.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/* Function prototypes */

void helpCommand();
void enqueueCommand(PriorityQueue & pq, string arg);
void dequeueCommand(PriorityQueue & pq);
void peekCommand(PriorityQueue & pq);
void peekPriorityCommand(PriorityQueue & pq);
void sizeCommand(PriorityQueue & pq);
void isEmptyCommand(PriorityQueue & pq);
void listCommand(PriorityQueue pq);
void clearCommand(PriorityQueue & pq);

/* Main program */

int main() {
   PriorityQueue pq;
   while (true) {
      string cmd = getLine("> ");
      if (cmd == "help")
      {
         helpCommand();
      }
      else if (cmd.find("enqueue(") != std::string::npos && cmd[cmd.length() - 1] == ')')
      {
          std::size_t pos = cmd.find('(') + 1;
          string args = cmd.substr(pos, cmd.length() - pos - 1);
          enqueueCommand(pq, args);
      }
      else if (cmd == "dequeue")
      {
          dequeueCommand(pq);
      }
      else if (cmd == "peek")
      {
          peekCommand(pq);
      }
      else if (cmd == "peekPriority")
      {
          peekPriorityCommand(pq);
      }
      else if (cmd == "size")
      {
          sizeCommand(pq);
      }
      else if (cmd == "isEmpty")
      {
          isEmptyCommand(pq);
      }
      else if (cmd == "list")
      {
          listCommand(pq);
      }
      else if (cmd == "clear")
      {
          clearCommand(pq);
      }
      else
      {
         cout << "Undefined command: " << cmd << endl;
      }
   }
   return 0;
}

/*
 * Function: helpCommand
 * ---------------------
 * Displays a list of the required commands.  If you extend this program,
 * you should add new entries to this function.
 */

void helpCommand() {
   cout << "enqueue value priority -- Enqueues value at priority" << endl;
   cout << "dequeue -- Dequeues the most urgent item" << endl;
   cout << "peek -- Peeks at the first item without removing it" << endl;
   cout << "peekPriority -- Reports the priority of the first item" << endl;
   cout << "clear -- Clears the queue" << endl;
   cout << "size -- Reports the size of the queue" << endl;
   cout << "isEmpty -- Reports whether the queue is empty" << endl;
   cout << "list -- Lists the elements of the queue" << endl;
   cout << "help -- Prints this message" << endl;
}


void enqueueCommand(PriorityQueue & pq, string arg)
{
    auto found_comma = arg.find(',');

    if(found_comma == std::string::npos) // comma not found
    {
        pq.enqueue(arg);
    }
    else
    {
        string value = arg.substr(0, found_comma);
        string priority_string =  arg.substr(found_comma + 1);
        double priority = std::stod(priority_string);
        pq.enqueue(value, priority);
    }
}

void dequeueCommand(PriorityQueue & pq)
{
    if(pq.isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << pq.dequeue() << endl;
}

void peekCommand(PriorityQueue & pq)
{
    if(pq.isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << pq.peek() << endl;
}

void peekPriorityCommand(PriorityQueue & pq)
{
    if(pq.isEmpty())
    {
        cout << "Queue is empty" << endl;
        return;
    }

    cout << pq.peekPriority() << endl;
}

void sizeCommand(PriorityQueue & pq)
{
    cout << "size = " << pq.size() << endl;
}

void isEmptyCommand(PriorityQueue & pq)
{
    cout << ((pq.isEmpty()) ? ("True") : ("False"))  << endl;
}

void listCommand(PriorityQueue pq)
{
    string msg = "Queue :";

    while(!pq.isEmpty())
    {
        msg += " " + pq.dequeue();
    }

    cout << msg << endl;
}

void clearCommand(PriorityQueue & pq)
{
    pq.clear();
}
