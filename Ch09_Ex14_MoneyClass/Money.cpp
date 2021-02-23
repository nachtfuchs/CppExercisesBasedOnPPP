/*
 * Money.cpp
 *
 *  Created on: 16.02.2021
 *      Author: Nachtfuchs
 */

#include "Money.h"
const char& getDefaultSeparator( void )
{
	static const char separator {'.'};
	return separator;
}

Money::Money( ) {};

Money::Money( long int cent ) :
	total { cent }
{
	if( cent < 0 ) {
		total = -1;
		error("Only positive money amounts are allowed. Your entry: ", cent);
	}
}

void Money::setTotal( long int inDollar, int inCent)
{
	total = inDollar * 100 + inCent;
}

ostream& operator<<( ostream& os, const Money& inMoney )
{
	// display dollars and cents
	return os << "$" << (double)inMoney.getTotal() / 100;
}

istream& operator>>( istream& is, Money& inMoney )
{
	long int dollar {-1};
	int cent{-1};
	char separator {' '};
	cin >> dollar >> separator >> cent;
	if( dollar < 0 ) error("Only positive dollar amounts can be entered. Your entry: ", dollar);
	if( cent < 0 || cent > 99 ) error("Only positive cent amounts and less than 100 can be entered. Your entry: ", cent);
	if( separator != getDefaultSeparator() ) error("Please use '.' for separating dollars and cents.");
	if( !cin ){
		if( dollar == -1 ) error("Please enter a dollar value larger than 0. Your entry: ", dollar);
		if( cent == -1 ) error("Please enter a cent value larger than 0. Your entry: ", cent);
		error("Could not read your monetary value.");
	}

	cout << "DEBUG dollar: " << dollar << endl;
	cout << "DEBUG cent: " << cent << endl;

	if( cent < 10 ) cent = cent * 10; //e.g. 12.9 --> 12.90
	inMoney.setTotal( dollar, cent );
	return is;
}

Money operator+( const Money& a, const Money& b)
{
	return Money{ a.getTotal() + b.getTotal() };
}

Money operator-( const Money& a, const Money& b)
{
	return Money{ a.getTotal() - b.getTotal() };
}
