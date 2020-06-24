#include <iostream>
#include "stack.h"
using namespace std;


int main()
{
    string in;
    Stack stk;
    while (getline(cin, in))
    {
	for (int i = 0; i < in.size(); ++i)
	{
	    stk.push(in[i]);
	}
	while (!stk.isEmpty())
	{
	   cout << stk.pop();
	}
	cout << endl;
    }
}
