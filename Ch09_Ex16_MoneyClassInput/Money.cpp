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

/* @brief A set of available currencies
 * */
const vector<string>& getAvlCurrency( void )
{
	static const vector<string> avlCurr { "USD", "EUR", "RUB" };
	return avlCurr;
}

Money::Money( ) {};

Money::Money( long int cent, string inCurr ) :
	total { cent }, currency { inCurr }
{
	if( cent < 0 ) {
		total = -1;
		error("Only positive money amounts are allowed. Your entry: ", cent);
	}
	bool isKnownCurr {false}; // Flag that shows whether "available" currency is used.
	for( string x : getAvlCurrency() ) {
		if( inCurr == x ) isKnownCurr = true;
	}
	if( !isKnownCurr ) error("Please use only available currencies.");
}

void Money::setTotal( double inValue )
{
	// convert to "cents" using the 4/5 rounding rule.
	long int temp { inValue * 1000 }; // "*1000" to make the number visible that is less than one cent
	if( temp % 10 != 0 ) {
		if( temp % 10 < 5 ) total = (long int) ( inValue * 10000 ) / 100; // round down
		else total = (long int) ( inValue * 10000 ) / 100 + 1; // round up
	}
	else total = (long int) ( inValue * 100 );
}

void Money::setCurrency( string inCurr )
{
	bool isCurrency {false};
	for( string x : getAvlCurrency() ) if( inCurr == x ) isCurrency = true;
	if( isCurrency ) {
		currency = inCurr;
		return;
	}
	error("The provided currency is not supported by the application: ", inCurr);
}
/* @brief Return the conversion factor from input b to input a
 * */
double getConversionFactor( const Money& a, const Money& b)
{
	CurrConvTable convTable {};
	if( a.getCurrency() == "USD" ) {
		if( b.getCurrency() == "EUR" ) return convTable.eurToUsd;
		if( b.getCurrency() == "RUB" ) return convTable.rubToUsd;
	}

	if( a.getCurrency() == "EUR" ) {
		if( b.getCurrency() == "USD" ) return convTable.usdToEur;
		if( b.getCurrency() == "RUB" ) return convTable.rubToEur;
	}

	if( a.getCurrency() == "RUB" ) {
		if( b.getCurrency() == "USD" ) return convTable.usdToRub;
		if( b.getCurrency() == "EUR" ) return convTable.eurToRub;
	}

	error("Error: getConversionFactor() did not identify valid currencies!");
	return -1;
}

ostream& operator<<( ostream& os, const Money& inMoney )
{
	// display dollars and cents
	return os << inMoney.getCurrency() << (double)inMoney.getTotal() / 100;
}

istream& operator>>( istream& is, Money& inMoney )
{
	string currency {""};
	bool isCurrency {false}; // a flag that is true, if currency is accepted by application
	double mValue {-1};	// Monetary value
	cin >> currency >> mValue;
	for( string x : getAvlCurrency() ) if( currency == x ) isCurrency = true;
	if( !isCurrency ) error("The currency you have entered is not supported by this application.");
	if( mValue < 0 ) error("Only positive amounts can be entered. Your entry: ", mValue);
	if( !cin ){
		if( mValue == -1 ) error("Please enter a monetary value larger than 0. Your entry: ", mValue);
		error("Could not read your monetary value.");
	}

	inMoney.setTotal( mValue );
	inMoney.setCurrency( currency );
	return is;
}

Money operator+( const Money& a, const Money& b)
{
	if( a.getCurrency() != b.getCurrency() ) {
		// try to convert currencies
		bool isKnownCurrA {false}; // Flag that shows whether "available" currency is used for input a
		bool isKnownCurrB {false};
		for( string x : getAvlCurrency() ) {
			if( a.getCurrency() == x ) isKnownCurrA = true;
			if( b.getCurrency() == x ) isKnownCurrB = true;
		}
		if( isKnownCurrA && isKnownCurrB ) {
			// avoid compiler warnings, by explicitly converting to (long int).
			// It also does automatically the 4/5-rounding-rule.
			return Money{ a.getTotal() + (long int) ( b.getTotal() * getConversionFactor( a, b ) ), a.getCurrency() };
		}
		error("Entries have unknown currencies. Please use known currencies only.");
	}
	return Money{ a.getTotal() + b.getTotal(), a.getCurrency() };
}

Money operator-( const Money& a, const Money& b)
{
	if( a.getCurrency() != b.getCurrency() ) {
		error("Entries have different currencies. Please use identical currencies when substracting two monetary values.");
	}
	return Money{ a.getTotal() - b.getTotal(), a.getCurrency() };
}
