#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

string reverse(string str);

int main()
{
    while(true)
    {
        string text = getLine("Enter text:");
        cout << reverse(text) << endl;
    }

   return 0;
}

string reverse(string str)
{
    if(str == "")
        return "";

    return str[str.size() - 1] + reverse(str.substr(0, str.size() - 1));
}
