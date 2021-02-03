/* @brief Assignment from chapter 9 exercise 11.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Design and implement a set of useful helper functions for the Date class
 * with functions such as next_workday() (assume that any day that is not
 * a Saturday or a Sunday is a workday) and week_of_year() (assume that
 * week 1 is the week with January 1 in it and that the first day of a week is
 * a Sunday).
 *
 * LESSONS LEARNED:
 * - It is painful to find a definition of a "absolute" starting weekday. Once
 *  I found out that the first day of "1.1.1" was a Monday, I realised, that
 *  I wanted to identify the weekday of "1.1.0" according to the astronomical
 *  year numbering. Finding these things out was time consuming.
 * - It is strange again, to see that "int" takes numbers larger than 65535.
 */
#include "Library.h"

int main()
{
	/*Check Chrono functions.*/
	Chrono::Date startDate {2020, Chrono::Month::jan, 29};
	startDate.add_day(1);
	cout << startDate << endl;
	cout << "week of year: " << week_of_year( startDate ) << endl;

	Chrono::Date workDateEqual { 2017, Chrono::Month::jan, 1};
	cout << "Next work day (workDateEqual): " << Chrono::nextWorkday( workDateEqual ) << endl;

	Chrono::Date workDateAfterDefault { 2017, Chrono::Month::jan, 29};
	cout << "Next work day (workDateAfterDefault): " << Chrono::nextWorkday( workDateAfterDefault ) << endl;

	Chrono::Date workDateMonthOver { 2017, Chrono::Month::jan, 31};
	cout << "Next work day (workDateMonthOver): " << Chrono::nextWorkday( workDateMonthOver ) << endl;

	Chrono::Date workDateFriday { 2017, Chrono::Month::jan, 6};
	cout << "Next work day (workDateFriday): " << Chrono::nextWorkday( workDateFriday ) << endl;

	Chrono::Date workDateFriday2 { 2017, Chrono::Month::jan, 27};
	cout << "Next work day (workDateFriday2): " << Chrono::nextWorkday( workDateFriday2 ) << endl;

	Chrono::Date workDateSaturday { 2017, Chrono::Month::jan, 7};
	cout << "Next work day (workDateSaturday): " << Chrono::nextWorkday( workDateSaturday ) << endl;

	Chrono::Date workDateOverYear { 2017, Chrono::Month::dec, 29}; // Friday
	cout << "Next work day (workDateOverYear): " << Chrono::nextWorkday( workDateOverYear ) << endl;
	workDateOverYear.add_day( 1 ); // Saturday
	cout << "Next work day (workDateOverYear): " << Chrono::nextWorkday( workDateOverYear ) << endl;
	workDateOverYear.add_day( 1 ); // Sunday
	cout << "Next work day (workDateOverYear): " << Chrono::nextWorkday( workDateOverYear ) << endl;

	Chrono::Date workDateFuture { 2018, Chrono::Month::jun, 29}; // Friday
	cout << "Next work day (workDateFuture): " << Chrono::nextWorkday( workDateFuture ) << endl;

	Chrono::Date workDateSmaller { 2016, Chrono::Month::dec, 30};
	cout << "Next work day (workDateSmaller): " << Chrono::nextWorkday( workDateSmaller ) << endl;

	workDateSmaller.add_day(1);
	cout << "Next work day (workDateSmaller): " << Chrono::nextWorkday( workDateSmaller ) << endl;

	workDateSmaller.add_day(1);
	cout << "Next work day (workDateSmaller): " << Chrono::nextWorkday( workDateSmaller ) << endl;

	Chrono::Date workDateSmallerMonth { 2016, Chrono::Month::nov, 30};
	cout << "Next work day (workDateSmallerMonth): " << Chrono::nextWorkday( workDateSmallerMonth ) << endl;

	Chrono::Date workDateSmallerFriday { 2016, Chrono::Month::nov, 25};
	cout << "Next work day (workDateSmallerFriday): " << Chrono::nextWorkday( workDateSmallerFriday ) << endl;

	Chrono::Date workDateOutOfRange { 79, Chrono::Month::nov, 25};
	cout << "Next work day (workDateOutOfRange): " << Chrono::nextWorkday( workDateOutOfRange ) << endl;

	keep_window_open();
	return 0;
}
