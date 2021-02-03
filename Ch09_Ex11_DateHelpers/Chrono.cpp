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
	// Chosen so that 1st, January is a Sunday. Which is then aligned
	// with the weekday enumeration class Day to be a "zero". This will make
	// it easier to calculate the weekday of a Date.
	static Date dd {2017,Month::jan,1};
	return dd;
}

/* @brief According to the Microsoft calendar, the "default_date()"
 * 	was a Sunday.
 * */
const Day& defaultDay( void )
{
	static const Day defDay { Day::sunday };
	return defDay;
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
	// Precondition
	if ( n < 0 ) error("ERROR. <Date::add_day>: Provided input argument n is lower than zero.");
	// Caution: Adding days can change months and years, so it needs some handling
	// check if a wrapping of months happens
	if( (d + n) > getDayInMonth( m, y ) )
	{
		n -= ( getDayInMonth( m, y ) - d + 1); // "+1" to account that below the
							// day is set to the first of the new month, already
		d = 1;
		++m; // increase the month
		// If month changes to January, then the year needs to be increased
		if( m == Month::jan ) y++;
		// recursive call
		add_day( n );
	}
	else {
		d += n;
		// Postcondition: Beware of February!
		if( m == Month::feb && d > 28){
			if( !leapyear( y ) ){
				++m;
				d -= 28;
			}
			else if( leapyear( y ) && d > 29) {
				++m;
				d -= 29;
			}
		}

	}
}

/* @brief Add n months to current months. Considers the wrap of years.
 * */
void Date::add_month(int n)
{
	int monthInYear {12};
	// Precondition
	if ( n < 0 ) error("ERROR <Date::add_month>: Provided input argument n is lower than zero.");
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
		m = m + n;
		// Postcondition: Beware of February!
		if( m == Month::feb && d > 28 )
		{
			if( !leapyear( y ) ){
				++m;
				d -= 28;
			}
			else if( leapyear( y ) && d > 29) {
				++m;
				d -= 29;
			}
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

/* @brief Returns the number of days of the given month m in a given year y.
 * */
int getDayInMonth( const Month& m, int y)
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
			if( leapyear( y ) ) daysInMonth = 29;
			else daysInMonth = 28;
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
/* @brief Returns true, if input values represent a valid date.
 * 		Checks for plausible day, month and year. Considers leap years.
 * */
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

/* @brief Returns true if input year is a leap year. (Gregorian calendar)
 * */
bool leapyear(int y)
{
	// Precondition: Only positive values are allowed.
	if( y < 0 ) cout << "WARNING: Only positive values for the input year are allowed." << endl;
	// PSEUDO: Most years that are divisible by four are leap years
	if( y % 4 == 0)
	{
		if( y % 100 == 0){ // 1500, 1700, 1800,...
			if( y % 400 == 0) return true;// 1600, 2000,...
			return false;
		}
		return true;
	}
	return false; // all the other years
}

/* @brief Returns the week of the year in the given Date.*/
int week_of_year(const Date& inDate)
{
	int w {-1};	// weeks since 1st, January , of given year
	int daySince {-1}; // days since 1st, January in given year.
	// IDEA: Count days since first of January up to the given date
	daySince = inDate.day();
	// Take into account the months
	if( (int) inDate.month() > (int)Month::jan) {
		for( int month = (int)Month::jan; month < (int)inDate.month(); month++) {
			daySince += getDayInMonth( Month(month), inDate.year() );
		}
	}
	w = daySince / 7 + 1; 	// Calculate the number of weeks. "+1" to consider
							//"int"-division
	return w;
}

/* @brief Return the date of the next working day. All days are working days
 * 		except of Saturday and Sunday.
 * */
Date nextWorkday( const Date& inDate)
{
	// Count the days since the default day, and use the %7-operation on it
	int daySince {-1}; // days since 1st, January in given year.
	int	inDateDay {}; // The weekday of inDate;
	int newYear { inDate.year() }; // To account of changing years
	Month newMonth { inDate.month() }; 	// To account of changing months.
	int newDay {-1}; 	// The day of the next working day.
	if( ( inDate > default_date() ) ){
		// IDEA: Count days since first of January up to the given date
		daySince = inDate.day();
		// Take into account the months
		if( (int) inDate.month() > (int)Month::jan) {
			for( int month = (int)Month::jan; month < (int)inDate.month(); month++) {
				daySince += getDayInMonth( Month(month), inDate.year() );
			}
		}
		// Now count the days in the years
		for( int startYear = inDate.year() - 1; startYear >= default_date().year(); startYear--){
			daySince += leapyear( startYear) ? 366 : 365;
			// "int" can calculate back only "pow(2, 16)-1" days. Then an overrun
			// to negative number occurs.
			if( daySince < 0 ) throw("ERROR <nextWorkday>: An overrun occured.");
		}

		inDateDay = ( daySince - 1 ) % 7; // This works only, because the defaultDay()
								// is a Sunday, which again is a "zero". "-1" to account
								// that there is no day zero.
		// Adapt the day, for the special cases
		switch ( Day( inDateDay ) )
		{
		case Day::friday:
			newDay = inDate.day() + 3; // "+3", to count to Monday.
			break;
		case Day::saturday:
			newDay = inDate.day() + 2; // "+2", to count to Monday.
			break;
		default:
			newDay = inDate.day() + 1; // for Sunday till Thursday.
			break;
		}

		// Beware of changes in month
		if( newDay > getDayInMonth( inDate.month(), inDate.year() )){
			++newMonth;
			newDay -= getDayInMonth( inDate.month(), inDate.year() );
			// Consider a change of years
			if( newMonth == Month::jan ) newYear++;
		}
	}
	else if( inDate < default_date() ) {
		// IDEA: Count days since first of January up to the given date
		daySince = getDayInMonth( inDate.month(), inDate.year() ) - inDate.day() + 1; // +1 to account that zero is not existing.
		// Take into account the months
		if( (int) inDate.month() < (int)Month::dec) {
			for( int month = (int)inDate.month() + 1; month <= (int)Month::dec; month++) { //"+1" to avoid counting the "inDate.month()" twice
				daySince += getDayInMonth( Month(month), inDate.year() );
			}
		}
		// Now count the days in the years
		for( int startYear = inDate.year() + 1; startYear < default_date().year(); startYear++){
			cout << "DEBUG <nextWorkday>. startYear: " << startYear << endl;
			cout << "DEBUG <nextWorkday>. daySince: " << daySince << endl;
			daySince += leapyear( startYear) ? 366 : 365;
		}
		// CAREFUL: "%7" does not return the aligned days of the enum class Day().
		// 		Think of default_date()-1 = (2016,12,31) which is actually a Saturday,
		// 		although inDateDay Day(daySince % 7) would return a "Monday".
		inDateDay = daySince % 7; // This works only, because the defaultDay()
								// is a Sunday, which again is a "zero".
		// Adapt the day, for the special cases
		switch ( inDateDay )
		{
		case 1: // Saturday
			newDay = inDate.day() + 2; // "+3", to count to Monday.
			break;
		case 2:	// Friday
			newDay = inDate.day() + 3; // "+2", to count to Monday.
			break;
		default:
			newDay = inDate.day() + 1; // for Sunday till Thursday.
			break;
		}

		// Beware of changes in month
		if( newDay > getDayInMonth( inDate.month(), inDate.year() )){
			++newMonth;
			newDay -= getDayInMonth( inDate.month(), inDate.year() );
			// Consider a change of years
			if( newMonth == Month::jan ) newYear++;
		}
	}
	else if( inDate == default_date() ){ // The default_date
		newYear = inDate.year();
		newMonth = inDate.month();
		newDay	= inDate.day() + 1; // As defined, the default date is a Sunday, so one day later will be Monday.
	}
	else error("ERROR <nextWorkday>: Workday cannot be determined!");
	return Date {newYear, newMonth, newDay};
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

bool operator<(const Date& a, const Date& b)
{
	if( a.year() < b.year() ) return true;
	if( a.year() == b.year() && (int)a.month() < (int) b.month() ) return true;
	if( a.year() == b.year() && (int)a.month() == (int) b.month() && a.day() < b.day()) return true;
	return false;
}

bool operator>(const Date& a, const Date& b)
{
	if( a.year() > b.year() ) return true;
	if( a.year() == b.year() && (int)a.month() > (int) b.month() ) return true;
	if( a.year() == b.year() && (int)a.month() == (int) b.month() && a.day() > b.day()) return true;
	return false;
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

} // Chrono
