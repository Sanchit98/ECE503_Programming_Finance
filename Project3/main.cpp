#include <iostream>
#include <stdexcept>
#include "array.h"
using namespace std;

int main()
{
    Array strings1( 7 ); // seven-element Array
    Array strings2; // 10-element Array by default

    // print strings1 size and contents
    cout << "Size of Array strings1 is " << strings1.getSize() << "\nArray after initialization:\n" << strings1;

    // print strings2 size and contents
    cout << "\nSize of Array strings2 is " << strings2.getSize() << "\nArray after initialization:\n" << strings2;

    // input and print strings1 and strings2
    cout << "\nEnter 17 strings:" << endl;
    cin >> strings1 >> strings2;

    cout << "\nAfter input, the Arrays contain:\n" << "strings1:\n" << strings1 << "strings2:\n" << strings2;

    // use overloaded inequality (!=) operator
    cout << "\nEvaluating: strings1 != strings2" << endl;

    if (strings1 != strings2)
        cout << "strings1 and strings2 are not equal" << endl;

    // create Array strings3 using strings1 as an
    // initializer; print size and contents
    Array strings3( strings1 ); // invokes copy constructor

    cout << "\nSize of Array strings3 is " << strings3.getSize() << "\nArray after initialization:\n" << strings3;

    // use overloaded assignment (=) operator
    cout << "\nAssigning strings2 to strings1:" << endl;
    strings1 = strings2; // note target Array is smaller

    cout << "strings1:\n" << strings1 << "strings2:\n" << strings2;

    // use overloaded equality (==) operator
    cout << "\nEvaluating: strings1 == strings2" << endl;

    if (strings1 == strings2)
    {
        cout << "strings1 and strings2 are equal" << endl;
    }

    // use overloaded subscript operator to create rvalue
    cout << "\nstrings1[5] is " << strings1[5];

    // use overloaded subscript operator to create lvalue
    cout << "\n\nAssigning Apple to strings1[5]" << endl;
    strings1[ 5 ] = "Apple";
    cout << "strings1:\n" << strings1;

    // attempt to use out-of-range subscript
    try
    {
        cout << "\nAttempt to assign Mango to strings1[15]" << endl;
        strings1[ 15 ] = "Mango"; // ERROR: subscript out of range
    } // end try

    catch ( out_of_range &ex )
    {
        cout << "An exception occurred: " << ex.what() << endl;
    } // end catch
} // end main




