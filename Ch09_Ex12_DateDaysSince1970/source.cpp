/* @brief Assignment from chapter 9 exercise 12.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Change the representation of a Date to be the number of days since January
 * 1, 1970 (known as day 0), represented as a long int, and re-implement the
 * functions from §9.8. Be sure to reject dates outside the range we can
 * represent that way (feel free to reject days before day 0, i.e., no negative
 * days)
 *
 * LESSONS LEARNED:
 * - Because of the reduction to a "day" only, the Date becomes a kind of number.
 */
#include "Chrono.h"

int main()
{
	/*Check Chrono functions.*/
	Chrono::Date legalDate { 0 };
	cout << "legalDate: " << legalDate << endl;

	Chrono::Date largeDate { 6235 };
	cout << "largeDate: " << largeDate << endl;

	Chrono::Date illegalDate { -5 };
	cout << "illegalDate: " << illegalDate << endl;
	keep_window_open();
	return 0;
}
