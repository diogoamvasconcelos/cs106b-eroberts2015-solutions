#include <iostream>
#include "console.h"
#include "simpio.h"
#include "set.h"
#include "foreach.h"
using namespace std;

Set<string> GeneratePermutations(string str);

int main()
{

    while(true)
    {
       string str = getLine("Enter a string:");

       cout << "Permutations of \"" << str << "\" are:" << endl;
       foreach (string s in GeneratePermutations(str))
       {
           cout << " \"" << s << "\"" << endl;
       }
    }

   return 0;
}

Set<string> GeneratePermutations(string str)
{
    Set<string> result;

    char ch = str[0];

    if(str == "")
    {
       result += "";
    }
    else
    {
        foreach (string s in GeneratePermutations(str.substr(1)))
        {
            for (int i = 0; i < s.length() + 1; ++i)
            {
                result.add(s.substr(0, i) + ch + s.substr(i));
            }
        }
    }

    return result;
}
