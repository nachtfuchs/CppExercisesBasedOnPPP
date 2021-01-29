/* @brief Assignment from chapter 9 exercise 7.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Create an enumerated type for the Book class called Genre. Have the
 * types be fiction, nonfiction, periodical, biography, and children. Give
 * each book a Genre and make appropriate changes to the Book constructor and
 * member functions.
 *
 * LESSONS LEARNED:
 */

#include "../std_lib_facilities.h"
#include "Book.h"

int main()
{
	Book validBook {"1234-5678-9012-A", "My valid book", "Famous Author", "22.05.2015", Genre::fiction, true};
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

	Book newBook {"2653-5698-5655-X", "My new book", "Another famous author", "22.03.2018", Genre::periodical, true};
	if ( newBook == validBook ) cout << "Books have identical ISBN." << endl;
	if ( newBook != validBook ) cout << "Books have different ISBN." << endl;

	// test case with "integer" as enumeration
	int myTarGenre { 1 }; // target genre
	try
	{
//		Book invalidGenre {"2653-5698-5655-X", "My new book", "Another famous author", "22.03.2018", myTarGenre, true}; // As expected, does not compile!
	}
	catch(...)
	{
		cout << "Invalid Book initialization with integer: " << myTarGenre << endl;

	}
	keep_window_open();
	return 0;
}
