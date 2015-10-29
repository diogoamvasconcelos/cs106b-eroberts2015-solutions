#include <iostream>
#include "console.h"
#include "simpio.h"
#include "stack.h"
using namespace std;

struct HanoiTask
{
    int num_disks;
    char start_pile;
    char finish_pile;
    char temp_pile;
};

const char PILE_A = 'A';
const char PILE_B = 'B';
const char PILE_C = 'C';

void MoveHanoiTower(int n);
void MoveSingleDisk(char start, char finish);

int main()
{
    while(true)
    {
        int n = getInteger("Hanoi n:");

        if(n < 1)
            break;

        MoveHanoiTower(n);
    }

   return 0;
}

void MoveHanoiTower(int n)
{
    Stack<HanoiTask> tasks_stack;

    HanoiTask starting_task;
    starting_task.num_disks = n;
    starting_task.start_pile = PILE_A;
    starting_task.finish_pile = PILE_B;
    starting_task.temp_pile = PILE_C;

    tasks_stack.push(starting_task);

    while(tasks_stack.size() > 0)
    {
       HanoiTask current_task = tasks_stack.pop();

       if(current_task.num_disks < 2)
       {
            MoveSingleDisk(current_task.start_pile, current_task.finish_pile);
       }
       else
       {
           HanoiTask move_from_top_task;
           move_from_top_task.num_disks = current_task.num_disks - 1;
           move_from_top_task.start_pile = current_task.start_pile;
           move_from_top_task.finish_pile = current_task.temp_pile;
           move_from_top_task.temp_pile = current_task.finish_pile;

           HanoiTask move_single_disk_task;
           move_single_disk_task.num_disks = 1;
           move_single_disk_task.start_pile = current_task.start_pile;
           move_single_disk_task.finish_pile = current_task.finish_pile;
           move_single_disk_task.temp_pile = current_task.temp_pile;

           HanoiTask move_back_task;
           move_back_task.num_disks = current_task.num_disks - 1;
           move_back_task.start_pile = current_task.temp_pile;
           move_back_task.finish_pile = current_task.finish_pile;
           move_back_task.temp_pile = current_task.start_pile;

           //Stack, first in last out, so tasks need to be correctly stacked
           tasks_stack.push(move_back_task);
           tasks_stack.push(move_single_disk_task);
           tasks_stack.push(move_from_top_task);
       }
    }
}

void MoveSingleDisk(char start, char finish)
{
    cout << start << "->" << finish << endl;
}
