/*
 * Chrono.cpp
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Chrono.h"
namespace Chrono {
// member function definitions:
Date::Date( int dd )
:  d{dd}
{
	if (!is_date( dd )) throw Invalid{};
}

const Date& default_date()
{
	// Day 0 according to the assignment
	static Date dd {0};
	return dd;
}

Date::Date()
	: d{default_date().day()}
{}

/* @brief Add days to date.
 * */
void Date::add_day(int n)
{
	// Precondition
	if ( n < 0 ) error("ERROR. <Date::add_day>: Provided input argument n is lower than zero.");
	// Increase the number of days
	d += n;
}

// helper functions:
bool is_date( int d )
{
	// assume that y is valid
	if (d<0) return false; // d must be positive
	return true;
}

bool operator==(const Date& a, const Date& b)
{
	return a.day()==b.day();
}

bool operator!=(const Date& a, const Date& b)
{
	return !(a==b);
}

bool operator<(const Date& a, const Date& b)
{
	return a.day() < b.day();
}

bool operator>(const Date& a, const Date& b)
{
	return a.day() > b.day();
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << d.day();
}

istream& operator>>(istream& is, Date& dd)
{
	int d;
	is >> d;
	if (!is) return is;
	dd = Date( d ); // update dd
	return is;
}

} // Chrono
