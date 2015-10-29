#include <iostream>
#include "console.h"
#include "simpio.h"
#include "vector.h";
#include "foreach.h"
using namespace std;

int CutStock(Vector<int>& requests, int stock_length);
bool RecursiveCutStock(Vector<int>& requests, int stock_length, int number_of_stock, int remaning_length);

int main()
{
    Vector<int> requests;
    requests.add(4);
    requests.add(3);
    requests.add(8);
    requests.add(1);
    requests.add(7);
    requests.add(4);

    while(true)
    {
        int stock_length = getInteger("Enter stock pipe length:");

        if (stock_length < 0)
            break;

        cout << "It is required " << CutStock(requests, stock_length) << " pipes." << endl;
    }

   return 0;
}

int CutStock(Vector<int>& requests, int stock_length)
{
    int number_of_stock = 0;
    Vector<int> requests_copy = requests;

    while(!RecursiveCutStock(requests_copy, stock_length, ++number_of_stock, stock_length))
    {
        cout << "Failed with " << number_of_stock << " stocks" << endl;
    }

    return number_of_stock;
}

bool RecursiveCutStock(Vector<int>& requests, int stock_length, int number_of_stock, int remaning_length)
{
    //Success case, solution found
    if(requests.size() == 0)
        return true;

    if(number_of_stock < 1) //run out of stocks
        return false;

    for (int i = 0; i < requests.size(); ++i)
    {
        int requested_stock = requests[i];

        while(remaning_length < requested_stock)
        {
            number_of_stock--;
            remaning_length = stock_length;

            if(number_of_stock < 1) //run out of stocks
                return false;
        }

        remaning_length -= requested_stock; //apply configuration
        requests.remove(i);

        if(RecursiveCutStock(requests, stock_length, number_of_stock, remaning_length))
            return true;

        remaning_length += requested_stock; //revert the configuration
        requests.add(requested_stock);
    }

    return false; //Return false to proceed the backtrack
}
