/* @brief Assignment from chapter 9 drill. 2
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * This drill simply involves getting the sequence of versions of Date to work. For
 * each version define a Date called today initialized to June 25, 1978. Then, define a
 * Date called tomorrow and give it a value by copying today into it and increasing
 * its day by one using add_day(). Finally, output today and tomorrow using a <<
 * defined as in §9.8.
 * Your check for a valid date may be very simple. Feel free to ignore leap years.
 * However, don’t accept a month that is not in the [1,12] range or day of the month
 * that is not in the [1,31] range. Test each version with at least one invalid date (e.g.,
 * 2004, 13, –5).
 *
 * The version from §9.4.2
 *
 * LESSONS LEARNED:
 * - Constructors are super useful, and make the code more readable.
 * - The member initializer list is used for the constructor.
  */

#include "../std_lib_facilities.h"

// simple Date
// guarantee initialization with constructor
// provide some notational convenience
struct Date {
	int y, m, d; // year, month, day
	Date(int inYear, int inMonth, int inDay); // check for valid date and initialize
	void add_day(int n); // increase the Date by n days
	};

Date::Date( int inYear, int inMonth, int inDay)
	: y { inYear }, m { inMonth }, d { inDay }
{
	if ( m < 1 )	error("ERROR. <Date::Date>: Provided input argument inMonth is lower than one.");
	if ( m > 12 )	error("ERROR. <Date::Date>: Provided input argument inMonth is larger than twelve.");
	if ( d < 1 ) 	error("ERROR. <Date::Date>: Provided input argument inDay is lower than one.");
	if ( d > 31 )	error("ERROR. <Date::Date>: Provided input argument inDay is larger than the largest possible day which is 31.");
}

// @brief Increase inDate by n days
void Date::add_day( int n)
{
	// Precondition
	if ( n < 0 ) error("ERROR. <Date::add_day>: Provided input argument n is lower than zero.");
	d += n;
}

int main()
{
	Date today {1978, 6, 25};// a Date variable (a named object)

	Date tomorrow { today };
	tomorrow.add_day( 1 );

	cout << "Today's date: (" << today.y << ',' << today.m << ',' << today.d << ')' << endl;
	cout << "Tomorrow's date: (" << tomorrow.y << ',' << tomorrow.m << ',' << tomorrow.d << ')' << endl;

	Date invalidDay {1978, 6, -5};
	try
	{
		invalidDay.add_day( 5 );
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		Date invalidMonth {1978, -6, 5};
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	keep_window_open();
	return 0;
}
