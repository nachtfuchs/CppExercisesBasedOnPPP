/*
 * Rational.h
 *
 *  Created on: 14.02.2021
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"

class Rational // A rational class, that can represent "rational numbers"
{
public:
	Rational( int, int );	// nominator, denominator
	int getDenominator() const { return denominator; };
	int getNominator() const { return nominator; };
	double getIrrational() const { return irrational; };
	double toDouble() const { return (double) nominator / denominator; }; // caution: Convert to double!

private:
	int denominator {};
	int nominator {};
	double irrational {};
};


// helper functions
ostream& operator<<( ostream&, const Rational&);
Rational operator*( const Rational&, const Rational&);
Rational operator/( const Rational&, const Rational&);
Rational operator+( const Rational&, const Rational&);
Rational operator-( const Rational&, const Rational&);
bool operator==( const Rational&, const Rational&);
bool operator!=( const Rational&, const Rational&);
bool operator<( const Rational&, const Rational&);
bool operator>( const Rational&, const Rational&);
