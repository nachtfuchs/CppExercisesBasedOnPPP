/* @brief Assignment from chapter 8 exercise 4.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * An int can hold integers only up to a maximum number. Find an
 * approximation of that maximum number by using fibonacci().[See
 * previous exercise].
 *
 * LESSON LEARNED: Using the pass-by-reference method, values that
 * are much larger than the regular int can be stored. It looks like
 * the number is interpreted as an "unsigned int". This interpretation
 * is rooted in the observation that the maximum number returned
 * was "1836311903" which requires log2(1836311903) ~= 31 bits.
 * The observation is still strange, because the sum of the two last
 * numbers is less than 2^(32), actually:
 * 1134903170 + 1836311903 = 2971215073.
 */

#include "../std_lib_facilities.h"

void print( string label, const vector<int>& inVec)
{
	cout << label << endl;
	for ( int x : inVec ) cout << x << endl;
}

bool fibonacci(int x, int y, vector<int>& v, int n)
{
	/* @brief: Calculates n fibonacci numbers starting with the first two x, and y
	 * */
	if (n < 2) error("ERROR: <fibonacci> Input argument n should be larger than 1.");
	v.push_back( x );
	v.push_back( y );
	for (int idx = 2; idx < n; idx++)
	{
		v.push_back( v[idx - 2] + v[idx - 1] ); // remember that index starts with zero. --> "-1"
		// check that "int" limits were not violated
		if ( v[ v.size() - 1 ] < v[ v.size() - 2] )
		{
			cout << "WARNING:The fibonacci numbers could not be calculated, because of an 'integer overflow'." << endl;
			cout << "Last two valid number were: " << v[ v.size() - 3] << "; " << v[ v.size() - 2] << endl;
			return false;
		}
	}
	return true;
}

int main()
{
	vector<int> myVector {};

	fibonacci(1, 1, myVector, 2);
	print("My vector values:", myVector);
	myVector.clear();

	fibonacci(1, 1, myVector, 5);
	print("My vector values:", myVector);
	myVector.clear();

	fibonacci(5, 6, myVector, 5);
	print("My vector values:", myVector);
	myVector.clear();

	fibonacci(1, 1, myVector, 50);
	print("My vector values:", myVector);
	myVector.clear();

	keep_window_open();
	return 0;
}
