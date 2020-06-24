#include <iostream>
#include "Coins.h"
using namespace std;
const int CENTS_FOR_CHIPS = 68;
const int PIGGY_DEPOSIT = 205;
int main()
{
    Coins pocket(5,3,6,8);
    Coins piggyBank(50,50,50,50);
    cout << "I started with " << pocket << " in my pocket" << endl;
    cout << "I started with " << piggyBank << " in my piggy bank" << endl << endl;

    Coins payForChips = 
	    pocket.extract_exact_change(coins_required_for_cents(CENTS_FOR_CHIPS));
    cout << "I bought a bag of chips for " << CENTS_FOR_CHIPS
	<< " cents using " << payForChips << endl;
    cout << "I have " << pocket << " left in my pocket" << endl << endl;

    Coins fromPiggyBank = 
	    piggyBank.extract_exact_change(coins_required_for_cents(PIGGY_DEPOSIT));
    pocket.deposit_coins(fromPiggyBank);
    cout << "I took " << PIGGY_DEPOSIT
	<< " cents from my piggy bank and put them into my pocket" << endl;
    cout << "Now I have " << pocket << " in my pocket and " 
	<< piggyBank << " in my piggy bank" << endl << endl;

    Coins fromSofa = Coins(10,10,10,10);
    piggyBank.deposit_coins(fromSofa);
    cout << "After finding money in my sofa, I now have $"
	<< piggyBank.total_value_in_cents()/100. << " in my piggy bank" << endl << endl;

    return 0;
}
