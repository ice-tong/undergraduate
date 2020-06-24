#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    // This section puts the ints into the vector and sorts them
    vector<int> V;
    ifstream in("rand_numbers.txt");
    copy(istream_iterator<int>(in), istream_iterator<int>(), back_inserter(V));
    sort(begin(V), end(V));

    //This section writes the ints to their proper parity files
    ofstream odd("odd.txt");
    ofstream even("even.txt");
    for_each(begin(V), end(V), [&](int i) {if (i % 2 == 0) even << i << endl;
					else odd << i << " ";});
    return 0;
}
