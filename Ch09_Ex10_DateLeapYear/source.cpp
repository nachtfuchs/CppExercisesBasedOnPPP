/* @brief Assignment from chapter 9 exercise 10.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Implement leapyear() from §9.8.
 *
 * LESSONS LEARNED:
 */
#include "Library.h"

int main()
{
	/*Check Chrono functions.*/
	Chrono::Date startDate {2020, Chrono::Month::jan, 29};
	startDate.add_day(1);
	cout << startDate << endl;

	// Overrun of month
	startDate.add_day(2);
	cout << startDate << endl;

	// Take a look at "add_month"
	startDate.add_month( 3 );
	cout << startDate << endl;

	// Overrun of years
	startDate.add_month(12);
	cout << startDate << endl;

	// Overrun of years using days
	startDate.add_day(365);
	cout << startDate << endl;

	// Test the leap years
	Chrono::Date legalLeapYear {2004, Chrono::Month::feb, 29};
	cout << legalLeapYear << endl;

	legalLeapYear.add_day( 365 );
	cout << legalLeapYear << endl;

	Chrono::Date LeapYear400 {2000, Chrono::Month::feb, 29};
	cout << LeapYear400 << endl;

	LeapYear400.add_day( 366 ); // 366, because the year 2000 has 366 days
	cout << LeapYear400 << endl;

	Chrono::Date illegalLeapYear {1900, Chrono::Month::feb, 29};
	cout << illegalLeapYear << endl;
	keep_window_open();
	return 0;
}
