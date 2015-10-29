/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the random writer problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "simpio.h"
using namespace std;

string randomTextGenerator(int order, int numberOfWords, string fileName);
void rotateNewLetter(string& word, char newLetter);

int main()
{
    string filename = "Cavaco.txt";

    while(true)
    {
        int order = getInteger("Markov order? (<1 to exit):");

        if(order < 1)
            break;

        int numberOfWords = getInteger("Number of words?:");

        cout << randomTextGenerator(order, numberOfWords, filename) << endl;
    }


	return 0;
}


string randomTextGenerator(int order, int numberOfWords, string fileName)
{
    Map<string, Vector<char>> data;
    ifstream fileStream;
    fileStream.open(fileName.c_str());

    //Analyze data
    string letterArray;
    for(int i = 0; i < order; ++i)
    {
        letterArray += fileStream.get();
    }

    int ch;
    while((ch = fileStream.get()) != EOF)
    {
        data[letterArray].add(ch);
        //Vector<char>& values = data[letterArray];
        //values.add(ch);
        rotateNewLetter(letterArray, ch);
    }

    fileStream.close();

    //Generate text
    string seed = "";
    int maxSize = 0;

    for(auto it = data.begin(); it != data.end(); it++)
    {
        string& key = *it;
        if(data[key].size() > maxSize)
        {
            maxSize = data[key].size();
            seed = key;
        }
    }

    string output = seed;

    while(output.size() < numberOfWords)
    {
        if(data.containsKey(seed))
        {
            Vector<char> values = data[seed];
            char newChar = values[randomInteger(0, values.size() - 1)];
            output += newChar;

            rotateNewLetter(seed, newChar);
        }
        else
        {
            break;
        }
    }

    return output;
}

void rotateNewLetter(string& word, char newLetter)
{
    for(int i = 0; i < word.size(); ++i)
    {
        if(i == word.size() - 1)
        {
            word[i] = newLetter;
        }
        else
        {
            word[i] = word[i+1];
        }
    }
}
