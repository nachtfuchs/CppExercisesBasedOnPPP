/* @brief Assignment from chapter 9 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Add operators for the Book class. Have the == operator check whether
 * the ISBN numbers are the same for two books. Have != also compare
 * the ISBN numbers. Have a << print out the title, author, and ISBN on
 * separate lines.
 *
 * LESSONS LEARNED:
 * - Getting user input and user output require as expected a lot of data
 *   handling. E.g.: Should the info about "==" be handled by the library
 *   or by the source.cpp-file. In this example I decided, that the libarary
 *   return the logical result, while the user needs to take care how
 *   the result is used, and whether more info is displayed with it.
 */

#include "../std_lib_facilities.h"
#include "Book.h"

int main()
{
	Book validBook {"1234-5678-9012-A", "My valid book", "Famous Author", "22.05.2015", true};
	checkout( validBook );
	checkin( validBook);

	// Try checking in an already checked in book
	checkin( validBook);

	// Try checking out an already checked out book
	checkout( validBook );
	checkout( validBook );

	// Create a copy of the book
	const Book copyBook { validBook };
	if ( copyBook == validBook ) cout << "Books have identical ISBN." << endl;
	if ( copyBook != validBook ) cout << "Books have different ISBN." << endl;

	cout << copyBook << endl;
	cout << validBook << endl;

	Book newBook {"2653-5698-5655-X", "My new book", "Another famous author", "22.03.2018", true};
	if ( newBook == validBook ) cout << "Books have identical ISBN." << endl;
	if ( newBook != validBook ) cout << "Books have different ISBN." << endl;

	keep_window_open();
	return 0;
}
