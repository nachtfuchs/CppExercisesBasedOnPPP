/* @brief Assignment from chapter 8 exercise 10.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a function maxv() that returns the largest element of a vector
 * argument.
 */

#include "../std_lib_facilities.h"

/* @brief Find the maximum value of an input vector.
 * */
double maxv( const vector<double>& inVec)
{
	vector<double> v = inVec;
	if( inVec.size() > 0 )
	{
		sort(v.begin(), v.end());
		return v[ v.size() - 1 ]; // the largest element is at the end of the vector.
	}
	error("ERROR: Something unexpected happened. The code should not get here.");
}

int main()
{
	vector<double> v {3, 0, 6, 7.9, -1, 2.5, -11};

	cout << "Largest element in vector v: " << maxv( v) << endl;
	keep_window_open();
	return 0;
}
