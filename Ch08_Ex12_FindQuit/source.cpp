/* @brief Assignment from chapter 8 exercise 12.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Improve print_until_s() from §8.5.2. Test it. What makes a good set of
 * test cases? Give reasons. Then, write a print_until_ss() that prints until it
 * sees a second occurrence of its quit argument.
 */

#include "../std_lib_facilities.h"

void print_until_s( const vector<string>& v, string quit) // improved "pass-by-const-reference"
{
	//Improved precondition: check that input is non-empty
	if ( v.size() == 0 ) error("ERROR <print_until_s>: input argument 'v' is empty.");
	if ( quit == "") error("ERROR <print_until_s>: input argument 'quit' is empty.");

	for( string s : v ) { // bugfix: int --> string
		if (s == quit) return;
		cout << s << '\n';
	}
}

void print_until_ss( const vector<string>& v, string quit)
{
	// Check precondition: input is non-empty
	if ( v.size() == 0 ) error("ERROR <print_until_s>: input argument 'v' is empty.");
	if ( quit == "") error("ERROR <print_until_s>: input argument 'quit' is empty.");

	int cnt {0}; // counts the amount of identified "quit"
	for( string s : v ) {
		if (s == quit) {
			cnt ++;
			if (cnt == 2) return;
		}
		else cout << s << '\n'; // using else to avoid printing "quit" once.
	}
}

int main()
{
	/* To determine a good set of test cases, the "equivalence classes" approach
	 * can be used.
	 * In this case, the input data should be tested for valid and invalid input
	 * values.
	 * And the output should be tested with a valid input where the quit condition
	 * is fulfilled, and where the quit condition is not fulfilled.
	 * */

	// Test case with valid inputs:
	vector<string> vValid {"Bob", "Alice"};
	string quitValid {"stop"};
	print_until_s( vValid, quitValid );

	// Test case with empty vector. Use "try...catch" to continue with test cases.
	vector<string> vEmpty {};
	try {
		print_until_s( vEmpty, quitValid );
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	// test case with empty quitting criteria
	string quitEmpty {};
	try {
		print_until_s( vValid, quitEmpty );
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	// Now check that the quit criteria is identified correctly.
	vector<string> vValidQuit {"Bob", "Alice", "Zoe", quitValid};
	print_until_s( vValidQuit, quitValid );

	// Now check that the quit criteria is identified correctly.
	vector<string> vValidBeyond {"Bob", "Alice", "Zoe", quitValid, "Joe", "Charlie"};
	print_until_s( vValidBeyond, quitValid );

	// Check print_until_ss
	print_until_ss( vValidBeyond, quitValid );

	vector<string> vValidBeyondTwice {"Bob", "Alice", "Zoe", quitValid, "Joe", "Charlie", quitValid, "Lee", "David"};
	print_until_ss( vValidBeyondTwice, quitValid );

	keep_window_open();
	return 0;
}
