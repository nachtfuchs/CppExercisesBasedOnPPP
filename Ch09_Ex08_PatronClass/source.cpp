/* @brief Assignment from chapter 9 exercise 8.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Create a Patron class for the library. The class will have a user’s name,
 * library card number, and library fees (if owed). Have functions that access
 * this data, as well as a function to set the fee of the user. Have a helper
 * function that returns a Boolean (bool) depending on whether or not the
 * user owes a fee.
 */

#include "../std_lib_facilities.h"
#include "Patron.h"

int main()
{
	Patron noDebtPatron { "Bob", "Lopez", 1, 0};

	cout << "inDebt( noDebtPatron ): " << inDebt( noDebtPatron ) << endl;
	cout << "Increasing fee for noDebtPatron." << endl;
	noDebtPatron.setFee( 25 );
	cout << "inDebt( noDebtPatron ): " << inDebt( noDebtPatron ) << endl;
	noDebtPatron.setFee( -1 );
	keep_window_open();
	return 0;
}
