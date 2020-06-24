#include "String.h"


void test_constructors()
{
    String s1("Hello");
    String s2;
    String s3(s1);
    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << " by copy" << endl;
}

void test_assignment()
{
    String s;
    String world("World");
    s = String("Hello");
    cout << "This should read Hello: " << s << endl;
    s = world;
    cout << "This should read World: " << s << endl;
}

void test_size_and_index()
{
    String s("Ooh wee");
    String one("A");
    cout << "Size should be 7: " << s.size() << endl;
    cout << "Size should be 1: " << one.size() << endl;
    cout << "Char should be w: " << s[4] << endl;
    cout << "Should produce A with error: " << one[1] << endl;
}

void test_indexOf()
{
    String daft("Daft");
    String punk("Punk");
    String empty;
    cout << "Index should be 3: " << daft.indexOf('t') << endl;
    cout << "Index should be -1: " << punk.indexOf('p') << endl;
    cout << "Index should be -1: " << empty.indexOf('0') << endl;
}

void test_relationals()
{
    String daft("Daft");
    String punk("Punk");
    String punk2("Punk");
    String daft2("daft");
    String long_punk("PunkPunk");
    cout << "< Should be 1: " << (daft < punk) << endl;
    cout << "< Should be 0: " << (punk < punk2) << endl;
    cout << "< Should be 1: " << (long_punk < punk2) << endl;
    cout << "== should be 1: " << (punk == punk2) << endl;
    cout << "== should be 0: " << (daft == daft2) << endl;
    cout << "== should be 0: " << (long_punk == punk) << endl;
}

void test_concat()
{
    String daft("Daft");
    String punk(" Punk");
    cout << "Should be Daft Punk: " << (daft+punk) << endl;
    cout << "Should be  PunkDaft: " << (punk+daft) << endl;
    cout << "Original should be Daft: " << daft << endl;
    cout << "Original should be  Punk: " << punk << endl;
    cout << "+= should return Daft Punk: " << (daft += punk) << endl;
    cout << "Original should now be Daft Punk: " << daft << endl;
}

void test_reverse()
{
    String aero("Aerodynamic");
    String palindrome("yay");
    cout << "Should be Aerodynamic backwards: " << aero.reverse() << endl;
    cout << "Original shouldn't change: " << aero << endl;
    cout << "Should be yay: " << palindrome.reverse() << endl;
}

int main()
{
    test_constructors();
    cout << "Constructors finished.\n" << endl;

    test_assignment();
    cout << "Assignment finished.\n" << endl;

    test_size_and_index();
    cout << "Size/index finished.\n" << endl;

    test_indexOf();
    cout << "indexOf finished.\n" << endl;

    test_relationals();
    cout << "Relationals finished.\n" << endl;

    test_concat();
    cout << "Concat finished.\n" << endl;

    test_reverse();
    cout << "Reverse finished.\n" << endl;

    return 0;
}
