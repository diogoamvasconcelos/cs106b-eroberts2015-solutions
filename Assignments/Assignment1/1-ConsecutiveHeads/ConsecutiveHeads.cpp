/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the coin-flipping problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "random.h"
using namespace std;

int main()
{
    int consecutiveCounter = 0;
    int flipCounter = 0;

    while(consecutiveCounter < 3)
    {
        if(randomChance(0.5))
        {
            cout << "Heads" << endl;
            consecutiveCounter++;
        }
        else
        {
            cout << "Tails" << endl;
            consecutiveCounter = 0;
        }

        flipCounter++;
    }
    cout << "It took " << flipCounter << " times to flip " << consecutiveCounter << " consecutive times" << endl;

    return 0;
}
