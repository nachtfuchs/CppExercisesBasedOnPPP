/*
 * Money.h
 *
 *  Created on: 16.02.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"

struct CurrConvTable
{
	const double usdToEur { 0.83 };
	const double eurToUsd { 1 / usdToEur };
	const double usdToRub { 73.69 };
	const double rubToUsd { 1 / usdToRub };
	const double eurToRub { 88.95 };
	const double rubToEur { 1 / eurToRub };
};

/* @brief A class that is used for monetary calculations
 * */
class Money
{
public:
	Money();
	Money( long int, string );
	long int getTotal( void ) const { return total; };
	void setTotal( double );
	void setCurrency( string );
	string getCurrency() const { return currency; };

private:
	long int total {-1}; // Total amount in currency.
	string currency {""}; // see available currencies in getAvlCurrency()
};

long int getInt( istream& );
const vector<string>& getAvlCurrency( void );
double getConversionFactor( const Money&, const Money&);

// helper functions
ostream& operator<<( ostream&, const Money& );
istream& operator>>( istream&, Money& );
Money operator+( const Money&, const Money&);
Money operator-( const Money&, const Money&);
