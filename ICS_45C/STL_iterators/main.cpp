#include "SetList.h"
#include "MapArray.h"
#include <fstream>
using namespace std;


int main()
{
    //This section puts the stopwords into a set
    ifstream in1("stopwords.txt");
    SetList<string> stopwords;
    for_each(istream_iterator<string>(in1), istream_iterator<string>(),
	[&](string S) {stopwords.insert(S);});

    // This section puts the words into the map
    ifstream in2("sample_doc.txt");
    MapArray<string,int> M;
    for_each(istream_iterator<string>(in2), istream_iterator<string>(),
	[&](string S) {transform(begin(S), end(S), begin(S), ::tolower);
	if (stopwords.find(S) == stopwords.end()) ++M[S];});

    // This section writes the words to frequency.txt
    ofstream out("frequency.txt");
    for_each(begin(M), end(M), [&](pair<string,int> p) {
				out << p.first << " " << p.second << endl;});

    return 0;
}
