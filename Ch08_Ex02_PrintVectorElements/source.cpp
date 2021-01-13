/* @brief Assignment from chapter 8 exercise 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a function print() that prints a vector of ints to cout. Give it two
 * arguments: a string for “labeling” the output and a vector.
 *
 * LESSONS LEARNED:
 * - make use of the qualifiers in function arguments.
 * - If possible, use pass-by-reference.
 */

#include "../std_lib_facilities.h"

void print( string label, const vector<int>& inVec)
{
	cout << label << endl;
	for ( int x : inVec ) cout << x << endl;
}

int main()
{
	cout << "Hello world!" << endl;
	vector<int> myVector {1, 2, 3};

	print("My vector values:", myVector);

	keep_window_open();
	return 0;
}
