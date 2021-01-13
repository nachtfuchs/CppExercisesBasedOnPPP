/* @brief Assignment from chapter 8 exercise 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Create a vector of Fibonacci numbers and print them using the function
 * from exercise 2. To create the vector, write a function, fibonacci(x,y,v,n),
 * where integers x and y are ints, v is an empty vector<int>, and n is the
 * number of elements to put into v; v[0] will be x and v[1] will be y.
 * A Fibonacci number is one that is part of a sequence where each element is the
 * sum of the two previous ones. For example, starting with 1 and 2, we get
 * 1, 2, 3, 5, 8, 13, 21, . . . . Your fibonacci() function should make such a
 * sequence starting with its x and y arguments.
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
		v.push_back( v[idx - 2] + v[idx - 1] );
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

	keep_window_open();
	return 0;
}
