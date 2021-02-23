/*
 * Money.h
 *
 *  Created on: 16.02.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"

/* @brief A class that is used for monetary calculations
 * */
class Money
{
public:
	Money();
	Money( long int );
	long int getTotal( void ) const { return total; };
	void setTotal( long int, int );

private:
	long int total {-1}; // Total amount in $-Cents.

};

long int getInt( istream& );

// helper functions
ostream& operator<<( ostream&, const Money& );
istream& operator>>( istream&, Money& );
Money operator+( const Money&, const Money&);
Money operator-( const Money&, const Money&);
