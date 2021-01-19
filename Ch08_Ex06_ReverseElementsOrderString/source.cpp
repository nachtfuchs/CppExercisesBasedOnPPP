/* @brief Assignment from chapter 8 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write versions of the functions from exercise 5, but with a vector<string>.
 *
 * LESSON LEARNED:
 * Use pass-by-const-reference especially if the function uses the argument for reading only.
 */

#include "../std_lib_facilities.h"

vector<string> reverseVector( const vector<string>& inVec)
{
	vector<string> outVec( inVec.size() );
	for (int idx = 0; idx < inVec.size(); idx++)
	{
		outVec[ idx ] = inVec[ inVec.size() - 1 - idx];
	}
	return outVec;
}

bool reverseVectorByRef( vector<string>& inVec )
{
	for (int idx = 0; idx < inVec.size() / 2; idx++ ) // use "/2" in order to "swap" once!
	{
		swap( inVec[ idx ], inVec[inVec.size() - 1 - idx]);
	}
	return true;
}
int main()
{
	vector<string> inVec { "a", "b", "c", "d", "e", "f", "g" };
	vector<string> outVec( inVec.size() );

	outVec = reverseVector( inVec );

	cout << "Reverse by value:" << endl;
	for (string x : outVec) cout << x << endl;
	for (string x : inVec) cout << x << endl;

	cout << "Reverse by reference:" << endl;
	reverseVectorByRef( inVec );
	for (string x : inVec) cout << x << endl;
	keep_window_open();
	return 0;
}
