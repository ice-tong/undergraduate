#include <iostream>
using namespace std;

double convert(int knot)
{
	double fph = knot * 6076;
	double mph = fph / 5280;
	return mph / 60;
}


int main()
{
	int i;
	cin >> i;
	cout << convert(i) << endl;
	return 0;
}
