/* @brief Assignment from chapter 9 exercise 5.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 *  This exercise and the next few require you to design and implement a Book
 *  class, such as you can imagine as part of software for a library. Class
 *  Book should have members for the ISBN, title, author, and copyright
 *  date. Also store data on whether or not the book is checked out. Create
 *  functions for returning those data values. Create functions for checking
 *  a book in and out. Do simple validation of data entered into a Book; for
 *  example, accept ISBNs only of the form n-n-n-x where n is an integer and
 *  x is a digit or a letter. Store an ISBN as a string.
 *
 * LESSONS LEARNED:
 * - It took me ages to make sure that the ISBN is correct.
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

	keep_window_open();
	return 0;
}
