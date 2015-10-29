/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "foreach.h"
using namespace std;

void loadLexiconFromFile(Lexicon& lexicon, string file);
string findWordLadder(string startWord, string endWord, Lexicon& lexicon);

int main()
{
    Lexicon wordsLexicon;
    loadLexiconFromFile(wordsLexicon, "EnglishWords.txt");

    while(true)
    {
        string startWord = getLine("Enter start word (empty to exit):");
        string endWord = getLine("Enter end word:");

        if(startWord == "" || endWord == "")
            break;

        cout << findWordLadder(startWord, endWord, wordsLexicon) << endl;
    }

	return 0;
}

void loadLexiconFromFile(Lexicon& lexicon, string filename)
{
    ifstream infile;
    infile.open(filename.c_str());

    string line;
    while(getline(infile, line))
    {
        lexicon.add(line);
    }

    infile.close();
}

string findWordLadder(string startWord, string endWord, Lexicon& wordsLexicon)
{
    Queue<Vector<string>> ladderQueue;
    Lexicon usedWords;

    Vector<string> startingLadder;
    startingLadder.add(startWord);

    ladderQueue.enqueue(startingLadder);
    usedWords.add(startWord);

    while(ladderQueue.size() > 0)
    {
        Vector<string> wordLadder = ladderQueue.dequeue();
        string lastWord = wordLadder[wordLadder.size() - 1];

        if(lastWord == endWord)
        {
            string returnValue = "Ladder found:";
            foreach(string word in wordLadder)
            {
                returnValue += " " + word;
            }

            return returnValue;
        }

        for(int i = 0; i < lastWord.size(); ++i)
        {
           // for (char letra = 'a'; letra <= 'z'; ++letra)
            for(int j = 0; j < 26; ++j)
            {
                char newLetter = 'a' + j;

                if(newLetter == lastWord[i])
                    continue;

                string newWord = lastWord;
                newWord[i] = newLetter;

                if(!usedWords.contains(newWord) && wordsLexicon.contains(newWord))
                {
                    Vector<string> newLadder = wordLadder;
                    newLadder.add(newWord);
                    usedWords.add(newWord);
                    ladderQueue.enqueue(newLadder);
                }
            }
        }
    }

    return "No ladder found.";
}
