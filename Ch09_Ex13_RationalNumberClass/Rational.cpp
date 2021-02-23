/*
 * Rational.cpp
 *
 *  Created on: 14.02.2021
 *      Author: Nachtfuchs
 */

#include "Rational.h"

Rational::Rational ( int n, int d ) :
	denominator { d }, nominator { n }
{
	if( denominator == 0 ) error("Division by zero.");
	irrational = nominator / denominator;
}

ostream& operator<<( ostream& os, const Rational& r)
{
	return os << r.getNominator() << '/' << r.getDenominator();
}

Rational operator*( const Rational& a, const Rational& b)
{
	return Rational { a.getNominator() * b.getNominator(), a.getDenominator() * b.getDenominator() };
}

Rational operator/( const Rational& a, const Rational& b)
{
	return Rational { a.getNominator() * b.getDenominator(), a.getDenominator() * b.getNominator() };
}

Rational operator+( const Rational& a, const Rational& b)
{
	return Rational { a.getNominator() * b.getDenominator() + a.getDenominator() * b.getNominator(), a.getDenominator() * b.getDenominator() };
}

Rational operator-( const Rational& a, const Rational& b)
{
	return Rational { a.getNominator() * b.getDenominator() - a.getDenominator() * b.getNominator(), a.getDenominator() * b.getDenominator() };
}

bool operator==( const Rational& a, const Rational& b)
{
	// NOTE: This cannot be done with an arithmetic-if
	if( a.getNominator() == b.getNominator() && a.getDenominator() == b.getDenominator() ) return true;
	return false;
}

bool operator!=( const Rational& a, const Rational& b)
{
	return !( a == b );
}

bool operator<( const Rational& a, const Rational& b)
{
	if( a.toDouble() < b.toDouble() ) return true;
	return false;
}

bool operator>( const Rational& a, const Rational& b)
{
	if( a.toDouble() > b.toDouble() ) return true;
	return false;
}
