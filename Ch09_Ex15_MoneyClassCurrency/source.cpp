/* @brief Assignment from chapter 9 exercise 15.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Define an input operator (>>) that reads monetary amounts with currency
 * denominations, such as USD1.23 and DKK5.00, into a Money variable. Also
 * define a corresponding output operator (<<).
 *
 * NOTE: Did this exercise already previously.
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


