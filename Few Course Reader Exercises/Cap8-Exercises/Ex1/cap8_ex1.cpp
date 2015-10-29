#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

void CountHanoiMoves(int n);
void MoveTower(int n, char start, char finish, char temp, int& moves);
void MoveSingleDisk(char start, char finish);

int main()
{
    while(true)
    {
        int n = getInteger("Hanoi n:");

        if(n < 1)
            break;

        CountHanoiMoves(n);
    }

   return 0;
}

void CountHanoiMoves(int n)
{
    int moves = 0;
    MoveTower(n, 'A', 'B', 'C', moves);

    cout << "Moves: " << moves << endl;
}

void MoveTower(int n, char start, char finish, char temp, int& moves)
{
    if ( n == 1)
    {
        MoveSingleDisk(start, finish);
    }
    else
    {
        MoveTower(n-1, start, temp, finish, moves);
        MoveSingleDisk(start, finish);
        MoveTower(n-1, temp, finish, start, moves);
    }

    moves++;
}

void MoveSingleDisk(char start, char finish)
{
    cout << start << "->" << finish << endl;
}
