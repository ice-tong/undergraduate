#include <iostream>
#include "Coins.h"
#include <stdlib.h>

using namespace std;

void menu()
{
    cout << "* * * * * * * * * * * * * * * * * * * * * *\n"
	 << "*          PIGGY BANK MENU                *\n"
	 << "*                                         *\n"
	 << "*    OPTION                   ENTER       *\n"
	 << "*    Show Balance (in $)      B or b      *\n"
	 << "*    Show Coins in Bank       C or c      *\n"
	 << "*    Deposit Coins            D or d      *\n"
	 << "*    Get Coins                G or g      *\n"
	 << "*                                         *\n"
	 << "*    Quit                     Q or q      *\n"
	 << "*                                         *\n"
	 << "* * * * * * * * * * * * * * * * * * * * * *\n";
}

char getCommand(const char * prompt)
{
    char ch;
    cout << prompt << " (followed by enter): ";
    cin >> ch;
    return ch;
}

Coins askForCoins()
{
    int q, d, n, p;
    cout << "How many quarters?  ";
    cin >> q;
    cout << "How many dimes?  ";
    cin >> d;
    cout << "How many nickels?  ";
    cin >> n;
    cout << "How many pennies?  ";
    cin >> p;
 
    return Coins(q,d,n,p);
}

void evaluateCommand(Coins & piggyBank, char command)
{
    switch(command)
    {
	case 'B': case 'b':
	    cout << "Balance is $" << piggyBank.total_value_in_cents()/100. << endl;
	    break;
	case 'C': case 'c':
	    cout << piggyBank << endl;
	    break;
	case 'D': case 'd':
	{
	    Coins toBeAdded = askForCoins(); 
	    piggyBank.deposit_coins(toBeAdded);
	    cout << "You now have " << piggyBank << " in your piggy bank\n";
	    break;
	}
	case 'G': case 'g':
	{
	    Coins toBeRemoved = askForCoins();
	    if (piggyBank.has_exact_change_for_coins(toBeRemoved))
		piggyBank.extract_exact_change(toBeRemoved);
	    else
		cout << "You don't have enough coins\n";
	    break;
	}
	case 'Q': case 'q':
	    cout << "Done with Piggy Bank.\n\n";
	    exit(0);
	default:
	    cout << "Invalid command " << command << endl;
	    break;
    }
    cout << endl;
}



int main()
{
    Coins piggyBank(0,0,0,0);
    while (true)
    {
	menu();
	char command = getCommand("Enter a command character");
	evaluateCommand(piggyBank, command);
    }
    return 0;
}
