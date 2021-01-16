/* @brief Assignment from chapter 8 exercise 5.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write two functions that reverse the order of elements in a vector<int>.
 * For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1. The first reverse function
 * should produce a new vector with the reversed sequence, leaving its original
 * vector unchanged. The other reverse function should reverse the
 * elements of its vector without using any other vectors (hint: swap).
 */

#include "../std_lib_facilities.h"

vector<int> reverseVector( vector<int> inVec)
{
	vector<int> outVec( inVec.size() );
	for (int idx = 0; idx < inVec.size(); idx++)
	{
		outVec[ idx ] = inVec[ inVec.size() - 1 - idx];
	}
	return outVec;
}

bool reverseVectorByRef( vector<int>& inVec )
{
	for (int idx = 0; idx < inVec.size() / 2; idx++ ) // use "/2" in order to "swap" once!
	{
		swap( inVec[ idx ], inVec[inVec.size() - 1 - idx]);
	}
	return true;
}
int main()
{
	vector<int> inVec { 0, 1, 2, 3, 4, 5, 6 };
	vector<int> outVec( inVec.size() );

	outVec = reverseVector( inVec );

	cout << "Reverse by value:" << endl;
	for (int x : outVec) cout << x << endl;
	for (int x : inVec) cout << x << endl;

	cout << "Reverse by reference:" << endl;
	reverseVectorByRef( inVec );
	for (int x : inVec) cout << x << endl;
	keep_window_open();
	return 0;
}
