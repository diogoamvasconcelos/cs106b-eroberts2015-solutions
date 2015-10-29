/*
 * File: NumericConversion.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the numeric-conversion problem
 * in which you implement the functions intToString and stringToInt.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
#include "map.h"
using namespace std;

Map<int, char> numbersMap;
Map<char, int> stringsMap;

/* Function prototypes */

void populateMaps();
string intToString(int n);
int stringToInt(string str);

/* Main program */

int main()
{
    populateMaps();

    while(true)
    {
        string n = getLine("Insert number to add 1");

        if(n == "break")
            break;

        cout << intToString(stringToInt(n)+1) << endl;
    }

   return 0;
}

void populateMaps()
{
    numbersMap.add(0, '0');
    numbersMap.add(1, '1');
    numbersMap.add(2, '2');
    numbersMap.add(3, '3');
    numbersMap.add(4, '4');
    numbersMap.add(5, '5');
    numbersMap.add(6, '6');
    numbersMap.add(7, '7');
    numbersMap.add(8, '8');
    numbersMap.add(9, '9');

    stringsMap.add('0', 0);
    stringsMap.add('1', 1);
    stringsMap.add('2', 2);
    stringsMap.add('3', 3);
    stringsMap.add('4', 4);
    stringsMap.add('5', 5);
    stringsMap.add('6', 6);
    stringsMap.add('7', 7);
    stringsMap.add('8', 8);
    stringsMap.add('9', 9);
}

string intToString(int n)
{
    if (n == 0)
        return "";

    int firstNumbers = n / 10;
    int finalNumber = n % 10;

    char finalChar = numbersMap[finalNumber];

    return intToString(firstNumbers) + finalChar;
}

int stringToInt(string str)
{
    if(str.size() == 0)
        return 0;

    string firstString = str.substr(0, str.length() - 1);
    char finalChar = str[str.length() - 1];

    int finalNumber = stringsMap[finalChar];

    return stringToInt(firstString) * 10 + finalNumber;
}
