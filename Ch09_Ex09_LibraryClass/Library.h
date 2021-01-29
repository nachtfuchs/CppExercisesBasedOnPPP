/*
 * Library.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Book.h"
#include "Patron.h"
#include "Chrono.h"

namespace BuildingOfKnowledge {

struct Transaction
{
	Publications::Book 	bookTrans;
	LibPerson::Patron	patronTrans;
	Chrono::Date		dateTrans;
};

class Library
{
public:
	void addBook( const Publications::Book& );
	void addPatron( const LibPerson::Patron& );
	void checkoutBook( void );
private:
	vector<Publications::Book> 	vBook {};
	vector<LibPerson::Patron>	vPatron {};
	vector<Transaction> vTrans {};
}; // Library
}
