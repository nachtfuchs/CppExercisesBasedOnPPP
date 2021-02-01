/*
 * Library.cpp
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Library.h"
namespace LibraryNS {

/* @brief Add a book to the library
 * */
void Library::addBook( const Publications::Book& inBook){
	vBook.push_back( inBook );
	cout << "Added the following book to the library: " << inBook << endl;
}

/* @brief Add a patron to the library
 * */
void Library::addPatron( const LibPerson::Patron& inPatron){
	vPatron.push_back( inPatron );
	cout << "Added the following patron to the library: " << inPatron << endl;
}

/* @brief Checkout a book from the library using the provided book, patron, and
 * 		date.
 * */
void Library::checkoutBook( const Publications::Book& inBook, const LibPerson::Patron& inPatron, const Chrono::Date& inDate ){
	// Precondition: Check that book is part of the library
	bool bookExisting { false }; // Book exists in library
	for( Publications::Book x : vBook ) {
		if( x == inBook ) bookExisting = true;
	}
	if( !bookExisting ) {
		cout << "WARNING: Book does not exist in library." <<
				"Aborting the book checkout process." << endl;
		return;
	}
	if( !inBook.getAvailability() ) {
		cout << "WARNING: Book is not available in library." <<
				"Aborting the book checkout process." << endl;
		return;
	}

	// Check patron
	bool patronExisting { false }; // Check that patron is a registered user
	for( LibPerson::Patron x : vPatron )
	{
		if( inPatron == x ) patronExisting = true;
	}
	if( !patronExisting ) {
		cout << "WARNING: Patron is does not exist in database. Aborting book checkout process." << endl;
		return;
	}
	// Check signed status of patron
	if( !inPatron.signedIn ){
		cout << "WARNING: Patron is not signed in. Aborting book checkout process." << endl;
		return;
	}

	// At this point, book and patron are available
	if( inPatron.getFee() > 0 ){
		cout << "WARNING: Patron is in debt. Please pay debts first, and then " <<
				"return to checkout. Aborting book checkout process." << endl;
		return;
	}
	const Transaction newTrans { inBook, inPatron, inDate }; // I am not sure
				//if this is well done. I basically want to have vTrans to contain
				//only "const" elements.
	vTrans.push_back( newTrans );

	// Refresh the book state
	for( Publications::Book x : vBook ) {
		if( x == inBook ) {
			x.setAvailability( false );
			cout << "Book state was set to: " << x.getAvailability() << endl;
		}
	}
}

/* @brief Print the names of all patrons who owe fees
 * */
void Library::printInDebts( void ){
	for( LibPerson::Patron x: vPatron ){
		if( x.getFee() >  0) cout << "Debtor: " << x << endl;
	}

}

Transaction::Transaction( Publications::Book inBook, LibPerson::Patron inPatron, Chrono::Date inDate )
	: bookTrans {inBook}, patronTrans {inPatron}, dateTrans {inDate}
{}

} // LibraryNS
