/*
 * Roman_int.h
 *
 *  Created on: 19.02.2021
 *      Author: Nachtfuchs
 */
#include "../std_lib_facilities.h"

class Roman_int
{
public:
	Roman_int();
	Roman_int( string );
	int as_int() const { return arabic; };
	string getRoman() const { return roman; };
	void setRoman( string inRoman ) { roman = inRoman; };
	void setArabic( int inNumber ) { arabic = inNumber; };
	void isLegalRomanNumeral();
	bool getLegalStatus() const { return isLegal; };
	void setLegalStatus( bool inStatus ) { isLegal = inStatus; };

private:
	string roman {""}; // The Roman representation
	int arabic {-1}; // The integer representation
	bool isLegal { true }; // Signalizes whether number is a legal
			// representation of a Roman numeral based on RomanMathGrammar.md
};

//helper functions
void isOnlyRomanDigits( const string& );
bool isSubtractiveNotation( char, char );
int getIntFromRoman( char );
int getIntFromRoman( char, char );
string to_roman( int );
// operator overloading
ostream& operator<<( ostream& , const Roman_int& );
istream& operator>>( istream& , Roman_int& );
Roman_int operator+( Roman_int& , Roman_int& );
Roman_int operator-( Roman_int& , Roman_int& );
Roman_int operator*( Roman_int& , Roman_int& );
Roman_int operator/( Roman_int& , Roman_int& );
