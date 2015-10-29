#include <iostream>
#include "console.h"
#include "simpio.h"
#include "foreach.h"
using namespace std;

bool WildcardMatch(string filename, string pattern);

int main()
{
    while(true)
    {
        string filename = getLine("Enter filename:");
        string pattern = getLine("Enter pattern:");

        cout << WildcardMatch(filename, pattern) << endl;
    }

   return 0;
}

bool WildcardMatch(string filename, string pattern)
{
    if (pattern == "")
        return true;

    auto pattern_analyzed = pattern[0];
    int num_analyzed_chars = 0;

    if (pattern_analyzed == '*')
    {
        //Last *
        if(pattern.size() == 1)
            return true;
    }
    else
    {
        if(filename.size() == 0)
            return false;

        if (pattern_analyzed == '?')
        {
            if(filename.size() == 0)
                return false;

            num_analyzed_chars = 1;
        }
        else
        {
            if (filename[0] != pattern_analyzed)
                return false;
            else
                num_analyzed_chars = 1;
        }
    }

    if (num_analyzed_chars == 1)
    {
        return WildcardMatch(filename.substr(1, filename.length() - 1), pattern.substr(1, pattern.length() - 1));
    }
    else
    {
        for (int i = 0; i < filename.length(); ++i)
        {
            if (WildcardMatch(filename.substr(i, filename.length() - i), pattern.substr(i, pattern.length() - 1)))
            {
                return true;
            }
        }

        return false;
    }
}
