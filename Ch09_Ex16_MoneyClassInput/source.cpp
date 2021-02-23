/* @brief Assignment from chapter 9 exercise 15.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Refine the Money class by adding a currency (given as a constructor argument).
 * Accept a floating-point initializer as long as it can be exactly represented
 * as a long int. Don’t accept illegal operations. For example, Money*Money
 * doesn’t make sense, and USD1.23+DKK5.00 makes sense only if you provide a
 * conversion table defining the conversion factor between U.S. dollars (USD)
 * and Danish kroner (DKK).
 *
 * LESSONS LEARNED:
 * - "operator>>" requires to treat "currency string" nicely. This was to much
 *   work at this time, so I treated it with less input checks.
 * - Processing the "minor" currency unit cannot be done easily with "int"
 * - Processing the 4/5 rounding rule for double cannot be performed "implicitly"
 *   by type casting. See p.231 in the book, where it says that conversions from
 *   double to int truncate the number. It does NOT round.
 */

#include "Money.h"

int main()
{
	cout << "Hello world!" << endl;
	Money validM { 5, "USD" };
	cout << "validM: " << validM << endl;
	Money validD { 304, "EUR" };
	cout << "validD: " << validD << endl;

	cout << "sum (validM + validM): " << validM + validM << endl;
	cout << "sum (validD + validD): " << validD + validD << endl;

	try {
		cout << "sum (validM + validD): " << validM + validD << endl;
	}
	catch(exception& e ){
		cout << "sum (validM + validD) failed." << endl;
		cout << "error: " << e.what() << endl;
	}

	cout << "Please provide an input monetary value starting with a currency, followed" <<
			"by a 'space' and then followed by the major.minor unit. E.g. EUR 9.05 ." <<
			endl << "The following units are allowed: ";
	for( string x : getAvlCurrency() ) cout << x << "; ";
	cout << endl << '>';
	Money inputM;
	cin >> inputM;
	cout << inputM << endl;

	keep_window_open();
	return 0;
}


