#include<iostream>
#include<iomanip>
#include<stdexcept>

#include "array.h" // Array class definition
using namespace std;

// default constructor for class Array (default size 10)
Array::Array( int arraySize )
: size( arraySize > 0 ? arraySize : throw invalid_argument( "Array size must be greater than 0" ) ), ptr( new std::string[ size ] )
{
    for ( size_t i = 0; i < size; ++i )
        ptr[ i ] = '0'; // set pointer-based array element
} // end Array default constructor

// copy constructor for class Array;
// must receive a reference to an Array
Array::Array( const Array &arrayToCopy )
: size( arrayToCopy.size ),
ptr( new std::string[ size ] )
{
    for ( size_t i = 0; i < size; ++i )
        ptr[ i ] = arrayToCopy.ptr[ i ]; // copy into object
} // end Array copy constructor

// destructor for class Array
Array::~Array()
{
    delete [] ptr; // release pointer-based array space
} // end destructor

// return number of elements of Array
size_t Array::getSize() const
{
    return size; // number of elements in Array
} // end function getSize
 
// overloaded assignment operator;
// const return avoids: ( a1 = a2 ) = a3
const Array &Array::operator=( const Array &right )
{
    if ( &right != this )
    {
        // for Arrays of different sizes, deallocate original
        // left-side Array, then allocate new left-side Array
        if ( size != right.size )
        {
            delete [] ptr; // release space
            size = right.size; // resize this object
            ptr = new std::string[ size ]; // create space for Array copy
        } // end inner if

        for ( size_t i = 0; i < size; ++i )
            ptr[ i ] = right.ptr[ i ]; // copy array into object
    } // end outer if

    return *this; // enables x = y = z, for example
} // end function operator=

// determine if two Arrays are equal and
// return true, otherwise return false
bool Array::operator==( const Array &right ) const
{
    if ( size != right.size )
        return false; // arrays of different number of elements

    for ( size_t i = 0; i < size; ++i )
        if ( ptr[ i ] != right.ptr[ i ] )
            return false; // Array contents are not equal

    return true; // Arrays are equal
} // end function operator==

// overloaded subscript operator for non-const Arrays;
// reference return creates a modifiable lvalue
std::string &Array::operator[]( int subscript )
{
    // check for subscript out-of-range error
    if ( subscript < 0 || subscript >= size )
        throw out_of_range( "Subscript out of range" );

    return ptr[ subscript ]; // reference return
} // end function operator[]

// overloaded subscript operator for const Arrays
// const reference return creates an rvalue
std::string Array::operator[]( int subscript ) const
{
    // check for subscript out-of-range error
    if ( subscript < 0 || subscript >= size )
        throw out_of_range( "Subscript out of range" );

    return ptr[ subscript ]; // returns copy of this element
} // end function operator[]

// overloaded input operator for class Array;
// inputs values for entire Array
istream &operator>>( istream &input, Array &a )
{
    for ( size_t i = 0; i < a.size; ++i )
        input >> a.ptr[ i ];

    return input; // enables cin >> x >> y;
} // end function

// overloaded output operator for class Array
ostream &operator<<( ostream &output, const Array &a )
{
    // output private ptr-based array
    for ( size_t i = 0; i < a.size; ++i )
    {
        output << setw( 12 ) << a.ptr[ i ];

        if ( ( i + 1 ) % 4 == 0 ) // 4 numbers per row of output
            output << endl;
    } // end for

    if ( a.size % 4 != 0 ) // end last line of output
        output << endl;

    return output; // enables cout << x << y;
} // end function operator<<