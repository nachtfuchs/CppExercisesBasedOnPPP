/* @brief Assignment from chapter 9 exercise 9.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Create a Library class. Include vectors of Books and Patrons. Include a
 * struct called Transaction. Have it include a Book, a Patron, and a Date
 * from the chapter. Make a vector of Transactions. Create functions to add
 * books to the library, add patrons to the library, and check out books.
 * Whenever a user checks out a book, have the library make sure that both
 * the user and the book are in the library. If they aren’t, report an error.
 * Then check to make sure that the user owes no fees. If the user does,
 * report an error. If not, create a Transaction, and place it in the vector of
 * Transactions. Also write a function that will return a vector that contains
 * the names of all Patrons who owe fees.
 *
 * LESSONS LEARNED:
 * - It is hard to create the methods that identify the status of a patron as
 *   signed in or not with a private member variable "signedIn". The "this"
 *   keyword was not introduced yet, but it is required to use it as part
 *   of a member function "setSignedIn()".
 */

#include "../std_lib_facilities.h"
#include "Chrono.h"

int main()
{
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

	keep_window_open();
	return 0;
}
