/*
 * Library.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Book.h"
#include "Patron.h"
#include "Chrono.h"

namespace LibraryNS { // LibraryNS (NameSpace)

struct Transaction
{
	Transaction( Publications::Book inBook, LibPerson::Patron inPatron, Chrono::Date inDate );
	Publications::Book 	bookTrans;
	LibPerson::Patron	patronTrans;
	Chrono::Date		dateTrans;
};

class Library
{
public:
	// NOTE: Constructor is not used, because of in-class initializers

	void addBook( const Publications::Book& );
	void addPatron( const LibPerson::Patron& );
	void checkoutBook( const Publications::Book&, const LibPerson::Patron&, const Chrono::Date& );
	vector<string> getInDebts( void );
	void printInDebts( void );

private:
	vector<Publications::Book> 	vBook {};
	vector<LibPerson::Patron>	vPatron {};
	vector<Transaction> vTrans {};
}; // Library

}// LibraryNS
