/*
 * Patron.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"
class Patron
{
public:

	Patron( string, string, double, double );
	// READ-ONLY methods
	string getName( void ) const { return firstName + ' ' + lastName; };
	double getCardNumber( void ) const { return cardNumber; };
	double getFee( void ) const { return fee; };

	// Write methods
	void setFee( double );

private:
	string firstName {};
	string lastName {};
	double cardNumber {};
	double fee {};
};

bool inDebt( const Patron& );
