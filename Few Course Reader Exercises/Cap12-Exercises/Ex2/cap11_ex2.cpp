#include <iostream>
#include "simpio.h"
#include "console.h"

//pg 572
/*
void strcpy(char *dst, char *src) {
while (*dst++ = *src++);
}
*/

using namespace std;

char *CopyCString(char *str);

int main()
{
    string test_string = "Hello world!";

    char *copied_string = CopyCString(&test_string[0]);

    cout << copied_string << endl;

    return 0;
}

char *CopyCString(char *str)
{
    //Check str size
    char *str_curr = str;

    while(*str_curr++);

    int str_size = str_curr - str;

    //Creat dynamic array to copy
    char *dst = new char[str_size];
    //Copy
    str_curr = str;
    char *dst_curr = dst;
    while (*dst_curr++ = *str_curr++);

    return dst;
}
