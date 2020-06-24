#define STACK_CAPACITY 1000
using namespace std;

class Stack
{
char stk[STACK_CAPACITY];
int count;

public:
    Stack() 
    {
	count = 0;
    }

    void error(std::string s)
    {
	cout << "Error: " << s << endl;
    }

    void push(char c)
    {
	if (isFull())
	{
	    error("Push on a full stack");
	}
	stk[count++] = c;
    }

    char pop()
    {
	if (isEmpty())
	{
	    error("Pop on an empty stack");
	}
	return stk[--count];
    }

    char top()
    {
	if (isEmpty())
	{
	    error("Empty stack has no top");
	}
	return stk[count-1];
    }

    bool isEmpty()
    {
	return count == 0;
    }

    bool isFull()
    {
	return count == STACK_CAPACITY;
    }

    ~Stack() {};
};

