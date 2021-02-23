/* @brief Assignment from chapter 10 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Define a Roman_int class for holding Roman numerals (as ints) with a
 * << and >>. Provide Roman_int with an as_int() member that returns the
 * int value, so that if r is a Roman_int, we can write cout << "Roman"
 * << r << " equals " << r.as_int() << '\n';.
 *
 * LESSONS LEARNED:
 * - I might have misunderstood the assignment! Maybe Roman_int was supposed
 *   to be initialized with an integer, instead of a string!
 * - indexing of a string is a char! E.g. string s = "bob", then s[1] is a "char".
 * - Creating strings from a set of chars is not as easy. "string s { ch1 + ch2}",
 *   obviously does NOT work, as expected. Even "string s { (string)ch1 + (stirng)ch2}"
 *   does NOT work. Check "twoDigitRoman" how it can be done.
 * - Creating a grammar can be performed "easily" in this case, compared to
 *   the calculator.
 */

#include "Roman_int.h"

int main()
{
	cout << "Hello world!" << endl;

	Roman_int rI { "I" };
	cout << "rI: " << rI << "; as int: " << rI.as_int() << endl;
	Roman_int rV { "V" };
	cout << "rV: " << rV << "; as int: " << rV.as_int() << endl;
	Roman_int rX { "X" };
	cout << "rX: " << rX << "; as int: " << rX.as_int() << endl;
	Roman_int rL { "L" };
	cout << "rL: " << rL << "; as int: " << rL.as_int() << endl;
	Roman_int rC { "C" };
	cout << "rC: " << rC << "; as int: " << rC.as_int() << endl;
	Roman_int rD { "D" };
	cout << "rD: " << rD << "; as int: " << rD.as_int() << endl;
	Roman_int rM { "M" };
	cout << "rM: " << rM << "; as int: " << rM.as_int() << endl;

	// Check the legal subtractive notations
	Roman_int rIV { "IV" };
	cout << "rIV: " << rIV << "; as int: " << rIV.as_int() << endl;
	Roman_int rIX { "IX" };
	cout << "rIX: " << rIX << "; as int: " << rIX.as_int() << endl;
	Roman_int rXL { "XL" };
	cout << "rXL: " << rXL << "; as int: " << rXL.as_int() << endl;
	Roman_int rXC { "XC" };
	cout << "rXC: " << rXC << "; as int: " << rXC.as_int() << endl;
	Roman_int rCD { "CD" };
	cout << "rCD: " << rCD << "; as int: " << rCD.as_int() << endl;
	Roman_int rCM { "CM" };
	cout << "rCM: " << rCM << "; as int: " << rCM.as_int() << endl;

	Roman_int rXIX { "XIX" };
	cout << "rXIX: " << rXIX << "; as int: " << rXIX.as_int() << endl;

	Roman_int rVII { "VII" };
	cout << "rVII: " << rVII << "; as int: " << rVII.as_int() << endl;

	Roman_int rVIII { "VIII" };
	cout << "rVIII: " << rVIII << "; as int: " << rVIII.as_int() << endl;

	Roman_int rXLIV { "XLIV" };
	cout << "rXLIV: " << rXLIV << "; as int: " << rXLIV.as_int() << endl;

	Roman_int rXLIX { "XLIX" };
	cout << "rXLIX: " << rXLIX << "; as int: " << rXLIX.as_int() << endl;

	Roman_int rMMMCMXCIX { "MMMCMXCIX" };
	cout << "rMMMCMXCIX: " << rMMMCMXCIX << "; as int: " << rMMMCMXCIX.as_int() << endl;

	Roman_int rMMMM { "MMMM" };
	cout << "rMMMM: " << rMMMM << "; as int: " << rMMMM.as_int() << endl;

	try {
		Roman_int rVIIII { "VIIII" };
		cout << "rVIIII: " << rVIIII << "; as int: " << rVIIII.as_int() << endl;
		cout << "rVIIII legal: " << rVIIII.getLegalStatus() << endl;
	}
	catch( exception& e) {
		cout << e.what() << endl;
		cout << "rVIIII failed as NOT expected." << endl;
	}
	try {
		Roman_int rArbitrary { "ILDCMXV" };
	}
	catch( exception& e) {
		cout << e.what() << endl;
		cout << "rArbitrary (ILDCMXV) failed as expected." << endl;
	}
	try {
		Roman_int rVX { "VX" };
	}
	catch (exception& e) {
		cout << e.what() << endl;
		cout << "rVX failed as expected." << endl;
	}

	// Checking the input operator:
	cout << "Please enter your Roman number, e.g. 'IX'." << endl
			<< '>';
	for( Roman_int rInput; cin >> rInput;)
	{
		cout << rInput << "; as int: " << rInput.as_int() << endl;
		cout << '>';
	}
	keep_window_open();
	return 0;
}
