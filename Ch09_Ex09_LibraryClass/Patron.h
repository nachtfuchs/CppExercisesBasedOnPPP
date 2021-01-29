/*
 * Patron.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"
namespace LibPerson{

class Patron
{
public:

	Patron( string, string, double, double, bool );
	// READ-ONLY methods
	string getName( void ) const { return firstName + ' ' + lastName; };
	double getCardNumber( void ) const { return cardNumber; };
	double getFee( void ) const { return fee; };

	// Write methods
	void setFee( double );

	bool signedIn { false };// true, if Patron is in library. False if he is not.

private:
	string firstName {};
	string lastName {};
	double cardNumber {};
	double fee {};
};

void setSignedIn( const Patron&, bool );
bool inDebt( const Patron& );

} // LibPerson


