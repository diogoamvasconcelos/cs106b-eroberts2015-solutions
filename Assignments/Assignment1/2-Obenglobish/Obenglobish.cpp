/*
 * File: Obenglobish.java
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Obenglobish problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

string obenglobish(const string word);
bool isCharAVowel(const char c);

/* Main program */

int main()
{
   while(true)
   {
       string word = getLine("Enter word: ");
       if(word == " ")
           break;

    string trans = obenglobish(word);

       cout << word << " -> " << trans << endl;
   }
   return 0;
}

string obenglobish(const string word)
{
    string transword;

    for (int i = 0; i < word.size(); ++i)
    {
        if(isCharAVowel((word[i])) && !((i > 0 && isCharAVowel(word[i - 1]))))
        {
           transword += "ob";
        }

        if(!(i == word.size() - 1 && word[i] == 'e'))
        {
             transword += word[i];
        }
    }

    return transword;
}

bool isCharAVowel(const char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'w';
}
