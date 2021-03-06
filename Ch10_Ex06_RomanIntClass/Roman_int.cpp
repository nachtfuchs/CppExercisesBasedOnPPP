/*
 * Roman_int.cpp
 *
 *  Created on: 19.02.2021
 *      Author: Nachtfuchs
 */

#include "Roman_int.h"

/* @brief Returns a vector with legal Roman numerals
 * */
const vector<char>& legalRomanDigit()
{
	static const vector<char> romanDigit { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	return romanDigit;
}

/* @brief Returns legal Roman subtractive notations based on "RomanMathGrammar.md"
 * */
const vector<string>& legalRomanSubtract()
{
	static const vector<string> romanSubtract { "IV", "IX", "XL", "XC", "CD", "CM" };
	return romanSubtract;
}

Roman_int::Roman_int() {};// Use the in-class initializer

Roman_int::Roman_int( string rNumber ):
		roman {rNumber}
{
	isOnlyRomanDigits( rNumber );
	isLegalRomanNumeral();
}

// Helper functions
/* @brief Throws, if input number contains an invalid "Roman digit"
 * */
void isOnlyRomanDigits( const string& inRomanNumber)
{
	for( int idx = 0; idx < inRomanNumber.length(); idx++ ) {
		bool isRomanNumeral { false };
		for( char x : legalRomanDigit() ) {
//			cout << "DEBUG x: " << x << endl;
//			cout << "DEBUG rNumber[ idx ]: " << rNumber[ idx ] << endl;
//			cout << "DEBUG rNumber[ idx ] == x: " << (rNumber[ idx ] == x) << endl;
			if( inRomanNumber[ idx ] == x ) {
				isRomanNumeral = true;
				break; // go to next literal
			}
		}
		if( !isRomanNumeral ) error("ERROR: Not a valid Roman numeral: ", inRomanNumber[ idx ] );
	}
}

/* @brief Checks if object is a legal Roman number. It is expected,
 * 		that the object contains only valid Roman digits.
 * @output [object].isLegal Sets the objects "isLegal" variable
 * @output [object].arabic  Sets the Arabic representation of the object's Roman
 * 							number
 * */
void Roman_int::isLegalRomanNumeral()
{
	int arabicTemp {0};	// the arabic representation of the number
	int cntRep {1};	// Repetition counter. Used to identify illegal numbers like "IIII"
	for( int idx = 0; idx < getRoman().length(); idx++ ){
//		cout << "DEBUG idx (begin): " << idx << endl;
		int digit { getIntFromRoman( getRoman()[ idx ] ) };
		// Check for notation type
		if( idx + 1 < getRoman().length() ) {
			int nextDigit { getIntFromRoman( getRoman()[ idx + 1 ] ) };
//			cout << "DEBUG nextDigit: " << nextDigit << endl;
			if( nextDigit <= digit ) { // additive notation
				if( nextDigit == digit) cntRep++;
				// Check for illegal number that repeat a Roman digit to often.
				if( cntRep > 3) {
					setLegalStatus( false );
					setArabic( -1 );
					return;
				}
				arabicTemp += digit;
			}
			else { // check for legal subtractive notation
				if( isSubtractiveNotation( getRoman()[ idx ], getRoman()[ idx + 1]) ) {
					arabicTemp += getIntFromRoman( getRoman()[ idx ], getRoman()[ idx + 1] );
					idx++; // artificially increase the idx to avoid analyzing the "second digit" twice.
				}
				else {
					setLegalStatus( false );
					setArabic( -1 );
					return;
				}
//				cout << "DEBUG idx (end subtractive notation): " << idx << endl;
			}
		}
		else arabicTemp += digit; // for numbers of length 1.
//		cout << "DEBUG: digit: " << digit << endl;
	}
	if( getLegalStatus() ) setArabic( arabicTemp );
	else setArabic( -1 );
//	cout << "arabicTemp: " << arabic << endl;
}

/* @brief Returns true, if the input digits are a legal subtractive
* 		notation based on RomanMathGrammar.md
 * */
bool isSubtractiveNotation( char firstDigit, char secondDigit)
{
	string twoDigitRoman { firstDigit };
	twoDigitRoman += secondDigit;
	for( string x : legalRomanSubtract() ){
		if( x == twoDigitRoman ) {
			return true;
		}
	}
	return false;
}

/* @brief Get the integer representation of a Roman digit.
 * */
int getIntFromRoman( char inRomanDigit )
{
	switch( inRomanDigit )
	{
		case 'I': return 1;
		case 'V': return 5;
		case 'X': return 10;
		case 'L': return 50;
		case 'C': return 100;
		case 'D': return 500;
		case 'M': return 1000;
	}
	error("ERROR: Undefined Roman digit: ", inRomanDigit );
	return -1; // to avoid warnings by the static code checker, and compiler.
}

/* @brief Get the integer representation of two Roman digits, e.g. "IV", "IX", etc.
 * */
int getIntFromRoman( char firstDigit, char secondDigit )
{
	string twoDigitRoman { firstDigit };
	twoDigitRoman += secondDigit;
	if( twoDigitRoman.length() > 2 ) error("ERROR: getIntFromRoman() works only on legal subtractive notations.");
	if( twoDigitRoman  == "IV") return 4;
	else if ( twoDigitRoman  == "IX") return 9;
	else if ( twoDigitRoman  == "XL") return 40;
	else if ( twoDigitRoman  == "XC") return 90;
	else if ( twoDigitRoman  == "CD") return 400;
	else if ( twoDigitRoman  == "CM") return 900;
	error("ERROR: Undefined Roman subtractive notation: ", twoDigitRoman );
	return -1; // to avoid warnings by the static code checker, and compiler.
}

// operator overloading
ostream& operator<<( ostream& os, const Roman_int& rNumber )
{
	return os << rNumber.getRoman();
}

istream& operator>>( istream& is, Roman_int& inRoman)
{
	string sTemp;
	is >> sTemp;
	Roman_int rTemp { sTemp }; // This takes care of error handling
	if( !rTemp.getLegalStatus() ) cout << "WARNING: The input Roman number is illegal. Your entry:" << sTemp << endl;
	inRoman.setRoman( rTemp.getRoman() );
	inRoman.setLegalStatus( rTemp.getLegalStatus() );
	inRoman.setArabic( rTemp.as_int() );
	return is;
}
