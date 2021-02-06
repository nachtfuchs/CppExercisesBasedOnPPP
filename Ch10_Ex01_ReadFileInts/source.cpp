/* @brief Assignment from chapter 10 assignment 1.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program that produces the sum of all the numbers in a file of
 * whitespace-separated integers.
 *
 * LESSONS LEARNED:
 * - Understanding the abstract idea, and that the "stream"-objects can be handled
 *   like variables helps to understand the code.
 */

#include "../std_lib_facilities.h"

/* @brief From the input stream try to find the next number.
 * */
void skip_to_int( ifstream& is )
{
	if( is.fail() ) {
//		cout << "DEBUG <skip_to_int>: input stream failed." << endl;
		is.clear(); // try to read the input as a char
		string invalidInput {""}; // used to identify the invalid characters in ifstream
		for( char ch; is >> ch; ) {
			// Try to find a first digit or "negative number" and return this
			// first valid input back to the stream
//			cout << "DEBUG <skip_to_int>: analysing input: " << ch << endl;
			if( isdigit( ch ) || ch == '-')
			{
//				cout << "DEBUG <skip_to_int>: next digit found:" << ch << endl;
				cout << "WARNING: Found the following unexpected input: " << invalidInput << endl;
				is.unget();
				return;
			}
			else invalidInput += ch;
		}
		error("No relevant input identified. Last unidentified input was: ", invalidInput);
	}
}

/* @brief Get an integer out of the input stream
 * */
int get_int( ifstream& is )
{
	// First, check for unsuccessful stream
	int t {0};
	while( true )
	{
		if( is >> t ) return t;
		cout << "Sorry, that was not a number. " << endl;
		skip_to_int( is );
	}
}

int main()
{
	cout << "This application calculates the sum of a series of integers in a "
			"certain file." << endl;
	string fName { "myInt.txt" };
	ifstream ifs { fName };
	int total { 0 }; // Used for the sum of all integers.

	// somewhere: make ifs throw an exception if it goes bad:
	ifs.exceptions( ifs.exceptions()|ios_base::badbit );

	// Try a stepwise approach
	for( int num; ifs >> num; )
	{
		if( ifs.fail() )	{
			ifs.clear();
			for( char ch; ifs >> ch;) {
				if( isdigit(ch) || ch == '-') {
					ifs.unget(); // Now that a number was found, put the digit back
					break;
				}
			}
		}
		if( ifs.eof() ) { /* do nothing*/}
		// Looks like the input is correct. Sum up the numbers:
		total += num;
	}
	cout << "(Stepwise) The sum is:" << total << endl;

	// Try a functional approach
	string fNameFunc { "myInt.txt" };
	ifstream ifsFunc { fName };
	total = 0; // reset
	// read until the end of the file
	while( ifsFunc.eof() == false )
	{
		total += get_int( ifsFunc );
	}
	cout << "(Functional) The sum is: " << total << endl;

	// Try with corrupted input
	string fNameCor { "myIntCor.txt" };
	ifstream ifsCor { fNameCor };
	total = 0; //  reset
	// read until the end of the file
	while( ifsCor.eof() == false )
	{
		total += get_int( ifsCor );
//		cout << "DEBUG - ifsCor.eof(): " << ifsCor.eof() << endl;
	}
	cout << "(Corrupted) The sum is: " << total << endl;
	keep_window_open();
	return 0;
}


