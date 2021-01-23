/* @brief Assignment from chapter 9 drill. 1
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
 * The version from §9.4.1
 *
 * LESSONS LEARNED:
 * - The struct without a constructor is very complicated to initialize a member.
 */

#include "../std_lib_facilities.h"

// simple Date (too simple?)
struct Date {
	int y; // year
	int m; // month in year
	int d; // day of month
	};

// @brief Increase inDate by n days
void add_day( Date& inDate, int n)
{
	// Precondition
	if ( n < 0 ) error("ERROR. <add_day>: Provided input argument n is lower than zero.");
	if ( inDate.d <= 0 ) error("ERROR. <add_day>: Provided input argument inDate has an invalid day.");

	inDate.d += n;
}
int main()
{
	Date today;// a Date variable (a named object)
	today.y = 1978;
	today.m = 6;
	today.d = 25;

	Date tomorrow { today };
	add_day( tomorrow, 1 );

	cout << "Today's date: (" << today.y << ',' << today.m << ',' << today.d << ')' << endl;
	cout << "Tomorrow's date: (" << tomorrow.y << ',' << tomorrow.m << ',' << tomorrow.d << ')' << endl;

	Date invalid;
	invalid.y = 1978;
	invalid.m = 6;
	invalid.d = -5;
	try
	{
		add_day( invalid, 5);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}
	keep_window_open();
	return 0;
}
