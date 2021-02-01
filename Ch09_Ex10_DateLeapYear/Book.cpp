/*
 * Book.cpp
 *
 *  Created on: 27.01.2021
 *      Author: Nachtfuchs
 */

#include "Book.h"
namespace Publications {
Book::Book( string inIsbn, string inTitle, string inAuthor, string inCDate, Genre inGenre, bool avl)
	: isbn {inIsbn}, title {inTitle}, author {inAuthor}, cDate {inCDate}, bookGenre {inGenre}, isAvailable {avl}
{
	if( !isbnValid( inIsbn ) ) throw( "Runtime error: Book::Book() initialized with wrong ISBN format." );
}

bool isbnValid( const string& inIsbn )
{
	int cntDash { 0 }; // counts the '-' sign
	bool validX { false }; // flag that signalizes a valid "x"
	// Analyze the ISBN that it contains only digits, dashes, or the "x" as a digit or letter.
	for( int idx = 0; idx < inIsbn.length(); idx++)
	{
		// NOTE: The order of evaluation is important. cntDash needs to be
		// increased after identifying "x" -> the last element in the ISBN number
		if( cntDash == 3 ) // "3", because there are at most three dashes according to the requirements.
		{
			validX = isalpha( inIsbn[ idx ] ) || isdigit( inIsbn[ idx ] );
			// Also check that there is only exactly one letter after the third dash.
			// NOTE: If the format is correct, than "idx" at this point is the
			// 		last element of the string.
			if( ( (int)inIsbn.length() - ( idx + 1) ) > 0 ) return false;
		}

		if( inIsbn[ idx ] == '-') cntDash++;
		if( cntDash > 3 ) return false;

		// Each element should be a number or dash as long as the number of
		// dashes is less than three
		if ( cntDash < 3)
		{
			if( inIsbn[ idx ] != '-' ) // if not a dash, then a number!
			{
				if ( !isdigit( inIsbn[ idx ] ) ) return false;
			}
		}
	}
	return validX && true;
}

/* @brief Give the book away to a person.
 * */
bool checkout( Book& inBook)
{
	// PRECONDITION: Make sure that book is available
	if( !inBook.getAvailability() )
	{
		cout << "WARNING: Book is identified as not available. Checkout not possible." << endl;
		return false;
	}

	cout << "Checking out book." << endl;
	inBook.setAvailability( false );
	cout << "Book checked out." << endl;
	return true;
}

bool checkin( Book& inBook)
{
	// PRECONDITION: Make sure that book is available
	if( inBook.getAvailability() )
	{
		cout << "WARNING: Book is identified as available. Checkin not possible." << endl;
		return false;
	}
	cout << "Checking in book." << endl;
	inBook.setAvailability( true );
	cout << "Book checked in." << endl;
	return true;
}

void Book::setAvailability( bool inAvl )
{
	isAvailable = inAvl;
}

bool operator==( const Book& bookA, const Book& bookB)
{
	if ( bookA.getIsbn() == bookB.getIsbn() ) return true;
	else return false;
}

bool operator!=( const Book& bookA, const Book& bookB)
{
	return !( bookA == bookB );
}

ostream& operator<<(ostream& os, const Book& inBook)
{
	return os << "Title: " << inBook.getTitle() << ", "
			<< "Author: " << inBook.getAuthor() << ", "
			<< "ISBN: " << inBook.getIsbn() << ';';
}
} // Publications
