/* @brief Assignment from chapter 8 exercise 14.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Can we declare a non-reference function argument const (e.g., void
 * f(const int);)? What might that mean? Why might we want to do that?
 * Why don’t people do that often? Try it; write a couple of small programs
 * to see what works.
 *
 * ANSWERS:
 * - It is possible to create such an argument. It is a read-only argument.
 * - It might be used when a small argument needs to be created for read-only
 *   purposes.
 * - I cannot see the benefits compared to a const pass-by-reference argument.
 * 	 It is computationally more expensive, too. So I guess people sometimes
 * 	 do that for comfort reasons?
 */

#include "../std_lib_facilities.h"

// First try: sum of two numbers
int f( const int a, int b )
{
	return a + b;
}

int fm( const int a, int b )
{
	a = 3; // obviously, this is not allowed and results in an error while compiling.
	return a + b;
}

int main()
{
	int a1 { 2 };
	int b1 { 2 };
	cout << "Result of f: " << f( 1, 1) <<  endl;
	cout << "Result of f: " << f( 2, 1) <<  endl;
	cout << "Result of f: " << f( a1, b1) <<  endl;
	cout << "Result of fm: " << fm( a1, b1) <<  endl;
	keep_window_open();
	return 0;
}
