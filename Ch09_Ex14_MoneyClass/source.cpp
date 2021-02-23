/* @brief Assignment from chapter 9 exercise 14.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Design and implement a Money class for calculations involving dollars
 * and cents where arithmetic has to be accurate to the last cent using the
 * 4/5 rounding rule (.5 of a cent rounds up; anything less than .5 rounds
 * down). Represent a monetary amount as a number of cents in a long int,
 * but input and output as dollars and cents, e.g., $123.45. Do not worry
 * about amounts that don’t fit into a long int.
 *
 * LESSONS LEARNED:
 * - "Money readM;" requires the default constructor to be defined!
 * - It was difficult to define the "setTotal"-function. I forgot how to
 *   access the private member of "this" object.
 * - I had to think more than a moment about the return operator for the
 *   overloaded "operator+". First, I used "long int".
 * - I forgot to use a "return" in "operator>>".
 */

#include "Money.h"

int main()
{
	cout << "Hello world!" << endl;
	Money validM { 5 };
	cout << "validM: " << validM << endl;
	Money validD { 303 };
	cout << "validD: " << validD << endl;

	Money sumM { validM + validD };
	cout << "sumM (validM + validD): " << sumM << endl;

	Money diffM { validD - validM };
	cout << "diffM (validD - validM): " << diffM << endl;

	try {
		// invalid diff
		diffM = validM - validD;
	}
	catch(...) {
		cout << "Invalid difference calculation." << endl;
	}

	Money readM; // requires the default constructor to be defined!
	cout << "DEBUG readM: " << readM << endl;
	cout << "Please enter your money value as a 'dollar.cents' entry." << endl;
	cout << ">";
	cin >> readM;
	cout << "The following amount was recorded: "<< readM << endl;

	Money invalidM { -303 };
	keep_window_open();
	return 0;
}


