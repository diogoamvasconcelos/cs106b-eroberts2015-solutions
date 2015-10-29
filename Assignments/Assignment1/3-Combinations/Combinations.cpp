/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the recursive combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

int c(int n, int k);

int main()
{
    while(true)
    {
        int n = getInteger("n?");
        int k = getInteger("k?");

        if (n < 0 || k < 0)
            break;

        cout << "c = " << c(n, k) << endl;
    }


   return 0;
}

int c(int n, int k)
{
   if (n == 0 || k == 0 || k == n)
       return 1;

    return (c(n-1, k-1) + c(n-1, k));
}
