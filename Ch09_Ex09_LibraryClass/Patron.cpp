/*
 * Patron.cpp
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */

#include "Patron.h"
namespace LibPerson{
// Constructor
Patron::Patron( string inFirstName, string inLastName, double inCardNumber, double inFee, bool inSign)
	: firstName {inFirstName}, lastName {inLastName}, cardNumber {inCardNumber}, fee {inFee}, signedIn {inSign}
{}

/* @brief Set the patron's fee. Decided to make a member-function, because "fee"
 * 		should have a restricted access.
 * */
void Patron::setFee( double newFee)
{
	// PRECONDITION: negative fees are not allowed.
	if( newFee < 0 )
	{
		cout << "WARNING: Fee not set. Negative fees cannot be set for patrons." << endl;
		return;
	}
	fee = newFee;
}

/* @brief Set the Patron status to be signed in in library or not.
 * */
void setSignedIn( Patron& inPatron, bool inStatus ) {
	if ( inPatron.signedIn ) // signed in
	{
		if( inStatus ) cout << "WARNING: Patron is already signed in." << endl;
		else inPatron.signedIn = false; // sign out
	}
	else // not signed in
	{
		if( inStatus ) inPatron.signedIn = false; // sign in
		else cout << "WARNING: Patron is already signed out." << endl;
	}
}
/* @brief Returns true, if patron is in debt.
 */
bool inDebt( const Patron& inPatron)
{
	if( inPatron.getFee() > 0 ) return true;
	else return false;
}
} // LibPerson
