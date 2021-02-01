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
 * - It is important to understand the difference between a book in the library
 *   and another book, that might be "free floating".
 */

#include "Library.h"
int main()
{
	/*Check Chrono functions.*/
//	Chrono::Date startDate {2020, Chrono::Month::jan, 29};
//	startDate.add_day(1);
//	cout << startDate << endl;
//
//	// Overrun of month
//	startDate.add_day(2);
//	cout << startDate << endl;
//
//	// Take a look at "add_month"
//	startDate.add_month( 3 );
//	cout << startDate << endl;
//
//	// Overrun of years
//	startDate.add_month(12);
//	cout << startDate << endl;
//
//	// Overrun of years using days
//	startDate.add_day(365);
//	cout << startDate << endl;

	/*Check Library functions.*/
	LibraryNS::Library myLibrary {};
	Publications::Book validBook {"1234-5678-9012-A", "My valid book", "Famous Author", "22.05.2015", Publications::Genre::fiction, true};
	myLibrary.addBook( validBook );

	LibPerson::Patron noDebtPatron { "Bob", "Lopez", 1, 0, true};
	myLibrary.addPatron( noDebtPatron );

	LibPerson::Patron debtPatron { "Alice", "Lopez", 2, 8, true};
	myLibrary.addPatron( debtPatron );

	myLibrary.printInDebts();

	Chrono::Date dateA {Chrono::Date (2021, Chrono::Month::feb, 1)};
	myLibrary.checkoutBook( validBook, noDebtPatron, dateA );
	cout << "validBook.getAvailablity(): " << validBook.getAvailability() << endl;

	LibPerson::Patron signedOutPatron { "Alice", "Lopez", 2, 8, false};
	myLibrary.addPatron( signedOutPatron );
	Publications::Book anotherValidBook {"6548-5678-9012-B", "My new book", "Another Famous Author", "22.05.2015", Publications::Genre::nonfiction, true};
	myLibrary.checkoutBook( anotherValidBook, signedOutPatron, Chrono::Date (2021, Chrono::Month::feb, 1) ); // Another was to provide a date.

	keep_window_open();
	return 0;
}
