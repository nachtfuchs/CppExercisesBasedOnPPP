/*
 * Book.h
 *
 *  Created on: 27.01.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"

enum class Genre{
	None = 0, fiction, nonfiction, periodical, biography, children
};

class Book
{
public:
	Book(string, string, string, string, Genre, bool); // constructor

	// Read-Only methods. Compatible with const-objects.
	string getIsbn() const { return isbn; };
	string getTitle() const { return title; };
	string getAuthor() const { return author; };
	string getCDate() const { return cDate; };
	Genre getGenre() const { return bookGenre; };
	bool getAvailability() const { return isAvailable; };

	// Write-methods
	void setAvailability( bool );

private:
	string isbn;	// format number-number-number-x. "x" is a letter or digit
	string title;
	string author;
	string cDate; 	// copyright date
	Genre  bookGenre;	// book genre
	bool isAvailable;
};

bool checkout( Book& );

/* @brief Return the book to the library.
 * */
bool checkin( Book& );

/* @brief Verify that isbn is valid, and follows the format number-number-number-x.
 * 		"x" is a letter or digit. Also makes sure that isbn is no longer than
 * 		necessary.
 * 		*/
bool isbnValid ( const string& );

/* @brief "==" checks that the ISBNs are identical
 * */
bool operator==( const Book&, const Book&);

/* @brief see operator "=="
 * */
bool operator!=( const Book&, const Book&);

/* @brief Print out the title, author, and ISBN on
 * separate lines
 * */
ostream& operator<<(ostream&, const Book&);
