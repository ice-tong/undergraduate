#include <iostream>
using namespace std;


const int QUARTER = 25, DIME = 10, NICKEL = 5;

class Coins
{
public:

    Coins(int q, int d, int n, int p)
      : quarters(q), dimes(d), nickels(n), pennies(p)
    { }

    void deposit_coins(Coins & c)
    {
	quarters += c.quarters;
	dimes += c.dimes;
	nickels += c.nickels;
	pennies += c.pennies;
	c.pennies = 0;
	c.nickels = 0;
	c.dimes = 0;
	c.quarters = 0;
    }

    bool has_exact_change_for_coins(Coins c)
    {
	return quarters >= c.quarters && dimes >= c.dimes
	&& nickels >= c.nickels && pennies >= c.pennies;
    }


    Coins extract_exact_change(Coins c)
    {
	quarters -= c.quarters;
	dimes -= c.dimes;
	nickels -= c.nickels;
	pennies -= c.pennies;
	return c;
    }


    int total_value_in_cents()
    {
	return quarters*QUARTER + dimes*DIME + nickels*NICKEL + pennies;
    }


    void print(ostream & out)
    {
	out << quarters << " quarters, " << dimes << " dimes, "
	    << nickels <<  " nickels, " << pennies << " pennies";
    }


private:
    int quarters, dimes, nickels, pennies;

};

ostream & operator << (ostream & out, Coins c)
{
    c.print(out);
    return out;
}

Coins coins_required_for_cents(int amount_in_cents)
{
   int quarters = amount_in_cents/QUARTER;
   amount_in_cents %= QUARTER;
   int dimes = amount_in_cents/DIME;
   amount_in_cents %= DIME;
   int nickels = amount_in_cents/NICKEL;
   amount_in_cents %= NICKEL;
   
   return Coins(quarters, dimes, nickels, amount_in_cents);
}
