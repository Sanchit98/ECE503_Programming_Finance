// Fig. 10.10: Array.h
// Array class definition with overloaded operators.
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

class Array
{
	friend std::ostream &operator<<( std::ostream &, const Array & );
	friend std::istream &operator>>( std::istream &, Array & );
	
public:
	explicit Array( int = 10 ); // default constructor
	Array( const Array & ); // copy constructor
	~Array(); // destructor
	size_t getSize() const; // return size
	const Array &operator=( const Array & ); // assignment operator
	bool operator==( const Array & ) const; // equality operator
	// inequality operator; returns opposite of == operator
	bool operator!=( const Array &right ) const
	{
	return ! ( *this == right ); // invokes Array::operator==
	} // end function operator!=

	// subscript operator for non-const objects returns modifiable lvalue
	std::string &operator[]( int );

	// subscript operator for const objects returns rvalue
	std::string operator[]( int ) const;

private:
	size_t size; // pointer-based array size
	std::string *ptr; // pointer to first element of pointer-based array
}; // end class Array`

#endif