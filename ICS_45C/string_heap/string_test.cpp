#include <iostream>
using namespace std;

#include "String.h"

void test_constructors()
{
    String s("Hello World");
    cout << s << endl;
    cout << String("Hola Mundo") << endl;
    String x(s);
    cout << x << " by copy." << endl;
}

void test_assignment()
{
    String s;
    String test("Text");
    s = test;
    cout << s << " of assigned string works!" << endl;
    cout << test << " of original string works!" << endl;
    test = String("NEW text");
    cout << test << " should have changed..." << endl;
    cout << "...but " << s << " should have stayed the same" << endl;
}

void test_relations()
{
    String first("First");
    String second("Second");
    String third("Third");
    cout << "== test should be 1: " << (first == String("First")) << endl;
    cout << "== test should be 0: " << (first == second) << endl;
    cout << "!= test should be 0: " << (third != String("Third")) << endl;
    cout << "!= test should be 1: " << (first != third) << endl;
    cout << "> test should be 0: " << (first > first) << endl;
    cout << "> test should be 0: " << (first > String("first")) << endl;
    cout << "< test should be 1: " << (third < String("Third1")) << endl;
    cout << ">= test should be 0: " << (first >= second) << endl;
    cout << "<= test should be 1: " << (second >= second) << endl;
}

void test_reverse()
{
    String hello("Hello World!");
    String palindrome("123454321");
    cout << "This should say Hello World! backwards: " << hello.reverse() << endl;
    cout << "This should be the same as 123454321: " << palindrome.reverse() << endl;
}

void test_concat()
{
    String s1("Hello ");
    String s2("World");
    cout << (s1 + s2) << endl;
    cout << (String("Around the ") += s2) << endl;
}

void test_indexOf()
{
    String hello("Hello!");
    String hola("Hola");
    cout << "Index should be 1: " << hello.indexOf('e') << endl;
    cout << "Index should be 2: " << hello.indexOf('l') << endl;
    cout << "Not in string, should be -1: " << hola.indexOf('e') << endl;

    cout << "Index should be 0: " << hola.indexOf(String("Hola")) << endl;
    cout << "Index should be 3: " << hello.indexOf(String("lo")) << endl;
    cout << "Not in string, should be -1: " << hello.indexOf(String("elll")) << endl;
}

int main()
{
    test_constructors();
    cout << "Constructors finished\n" << endl;

    test_assignment();
    cout << "Assignment finished\n" << endl;

    test_relations();
    cout << "Relationals finished\n" << endl;

    test_concat();
    cout << "Concat finished\n" << endl;

    test_reverse();
    cout << "Reverse finished\n" << endl;

    test_indexOf();
    cout << "indexOf finished\n" << endl;

    cout << "Number of new allocations minus number of delete deallocations is " << String::allocations() << endl;

    return 0;
}
