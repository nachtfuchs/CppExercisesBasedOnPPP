/*
 * Chrono.cpp
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Chrono.h"
namespace Chrono {
// member function definitions:
Date::Date(int yy, Month mm, int dd)
: y{yy}, m{mm}, d{dd}
{
	if (!is_date(yy,mm,dd)) throw Invalid{};
}

const Date& default_date()
{
	static Date dd {2001,Month::jan,1}; // start of 21st century
	return dd;
}
Date::Date()
	:y{default_date().year()},
	 m{default_date().month()},
	 d{default_date().day()}
{}

/* @brief Recursive! Adds days and considers the change of months and years. Does NOT
 * 		consider leap years.
 * */
void Date::add_day(int n)
{
	// todo: Consider leap years.
	// Precondition
	if ( n < 0 ) error("ERROR. <Date::add_day>: Provided input argument n is lower than zero.");
	// Caution: Adding days can change months and years, so it needs some handling
	// check if a wrapping of months happens
	if( (d + n) > getDayInMonth( m ) )
	{
		n -= ( getDayInMonth( m ) - d + 1); // "+1" to account that below the
							// day is set to the first of the new month, already
		d = 1;
		++m; // increase the month
		// If month changes to January, then the year needs to be increased
		if( m == Month::jan ) y++;
		// recursive call
		add_day( n );
	}
	else d += n;
}

/* @brief Add n months to current months. Considers the wrap of years.
 * */
void Date::add_month(int n)
{
	// todo: Consider leap years.
	int monthInYear {12};
	// Precondition
	if ( n < 0 ) error("ERROR. <Date::add_month>: Provided input argument n is lower than zero.");
	// Caution: Adding months can change months and years, so it needs some handling
	// check if a wrapping of months happens
	if( ( (int)m + n) > monthInYear )
	{
		n -= monthInYear - (int) m + 1; // "+1" necessary to account the wrap up.
		m = Month::jan; // set as beginning of next year
		y++;
		// recursive call
		if( n > 0 ) add_month( n );
	}
	else
	{
//		Month moreMonth =  Month( n ); // for "Month operator+( const Month& mA, const Month& mB)"
		m = m + n;
		// Postcondition: Beware of February!
		// Currently, February has only 28 days!
		if( m == Month::feb && d > 28 )
		{
			++m;
			d = d-28;
		}
	}
}

void Date::add_year(int n)
{
	if (m==Month::feb && d==29 && !leapyear(y+n)) { // beware of leap years!
		m = Month::mar; // use March 1 instead of February 29
		d = 1;
	}
	y+=n;
}

/* @brief Returns the number of days of the given month
 * */
int getDayInMonth( const Month& m)
{
	int daysInMonth {-1};
	switch ( m )
	{
		case Month::jan:
		case Month::mar:
		case Month::may:
		case Month::jul:
		case Month::aug:
		case Month::oct:
		case Month::dec:
			daysInMonth = 31;
			break;
		case Month::feb:
			// NOTE: Does not deal with leapyears
			daysInMonth = 28;
			break;
		case Month::apr:
		case Month::jun:
		case Month::sep:
		case Month::nov:
			daysInMonth = 30;
			break;
	}
	return daysInMonth;
}

// helper functions:
bool is_date(int y, Month m, int d)
{
	// assume that y is valid
	if (d<=0) return false; // d must be positive
	if (m<Month::jan || Month::dec<m) return false;
	int days_in_month { 31 }; // most months have 31 days
	switch (m) {
		case Month::feb: // the length of February varies
			days_in_month = (leapyear(y))?29:28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30; // the rest have 30 days
		break;
	}
	if (days_in_month<d) return false;
	return true;
}


bool leapyear(int y)
{
	return false; // todo
// see exercise 10
}

bool operator==(const Date& a, const Date& b)
{
	return a.year()==b.year()
		&& a.month()==b.month()
		&& a.day()==b.day();
}
bool operator!=(const Date& a, const Date& b)
{
	return !(a==b);
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
			<< ',' << (int)d.month()
			<< ',' << d.day() << ')';
}

istream& operator>>(istream& is, Date& dd)
{
	int y, m, d;
	char ch1, ch2, ch3, ch4;
	is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
	if (!is) return is;
	if (ch1!= '(' || ch2!=',' || ch3!=',' || ch4!=')') { // oops: format error
		is.clear(ios_base::failbit); // set the fail bit
		return is;
	}
	dd = Date(y, Month(m),d); // update dd
	return is;
}

Month operator++( Month& inMonth )
{
	inMonth = (inMonth == Month::dec) ? Month::jan : Month( (int)inMonth + 1);
	return inMonth;
}

Month operator+( const Month& mA, int n)
{
//	int numericMonth { (int) mA + (int) mB };
	int numericMonth { (int) mA + n };
	if( numericMonth > 12 ) throw("Runtime-error: The calculated month is larger than allowed with 'Month'-enum.");
	return Month( numericMonth );
}

// todo:
//Chrono::Day day_of_week(const Date& d)
//{
//// . . .
//}
//Date next_Sunday(const Date& d)
//{
//// ...
//}
//Date next_weekday(const Date& d)
//{
//// . . .
//}
} // Chrono
