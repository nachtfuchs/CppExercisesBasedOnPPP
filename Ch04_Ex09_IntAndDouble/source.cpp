/* @brief Assignment from chapter 4 exercise 9.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Try to calculate the number of rice grains that the inventor asked for in
 * exercise 8 above. You’ll find that the number is so large that it won’t fit
 * in an int or a double. Observe what happens when the number gets too
 * large to represent exactly as an int and as a double. What is the largest
 * number of squares for which you can calculate the exact number of
 * grains (using an int)? What is the largest number of squares for which
 * you can calculate the approximate number of grains (using a double)?
 *
 * Note: The inventor asked for sum of grains on 64 chess squares, if each
 * chess square doubled the amount of grains on the square before. Starting
 * with one grain.
 * Note: Pay attention, that "unsigned" is not supposed to be used. Then,
 * the statement in the assignment is true.
 */

#include "../std_lib_facilities.h"

int main()
{
	int grain_i {1}; // First square is already considered
	double grain_d {1};
	int grainTotal_i {1}; // considers the first square
	double grainTotal_d {1};
	int cnt {0}; // counter

	// SOLUTION: The amount of grains the inventor asked for is 2^(64)-1.

	// on a typical computer, an int takes 4 bytes of memory.
	for (cnt = 1; cnt < 4*8; cnt++) // calculate up to 2^(31). Neglect the first calculation, since it is already considered in the definition above.
	{
		if (grainTotal_i > (grainTotal_i + grain_i * 2)) // previous calculation is larger than the current calculation because of an overrun
		{
			// This is a little bit of a brain teaser. The easiest way to understand it, is using only four squares in total
			// -> (2^(4)-1)/2 = 7 is the max number. Divided by two, because four bytes are used for positive AND negative numbers.
			// 1.square = 1;	sum = 1; 	// cnt = 0
			// 2.square = 2;	sum = 3; 	// cnt = 1
			// 3.square = 4;	sum = 7;	// cnt = 2
			// 4.square = 8;	sum = 15; 	// cnt = 3 // ERROR: NOT possible, because max number is "7"
			// As you can see in the 4th step, cnt equals 3, which returns the number of the last square that can correctly calculate the amount of grains.
			cout << "The number of squares for which you can calculate the exact number of squares using an int is: " << cnt << endl;
			cout << "The amount of grains on the square " << cnt << " is: " << grain_i << endl;
			cout << "The calculated amount of grains using an int on the " << cnt  + 1 << " square would be: " << grain_i * 2 << endl;
			cout << "The summed up grains until the square " << cnt << " is: " << grainTotal_i << endl;
			break; // leave the loop
		}
		grain_i *= 2;
		grainTotal_i += grain_i;
		cout << "Summed up grains using int: " << grainTotal_i << endl; // careful, this will have an overrun of the
	}

	// on a typical computer, a double takes double amount of memory as an int -> 8 bytes.
	for (cnt = 1; cnt < 8*8; cnt++) // calculate up to 2^(63). Neglect the first calculation, since it is already considered in the definition above.
	{
		if (grainTotal_d > (grainTotal_d + grain_d * 2)) // previous calculation is larger than the current calculation because of an overrun
		{
			cout << "The number of squares for which you can calculate the exact number of squares using a double is: " << cnt << endl;
			cout << "The amount of grains on the square " << cnt << " is: " << grain_d << endl;
			cout << "The calculated amount of grains using a double on the " << cnt  + 1 << " square would be: " << grain_d * 2 << endl;
			cout << "The summed up grains until the square " << cnt << " is: " << grainTotal_d << endl;
			break; // leave the loop
		}
		cout << "debug - cnt: " << cnt << endl; //debug
		grain_d *= 2;
		grainTotal_d += grain_d;
		cout << "Summed up grains using double: " << grainTotal_d << endl; // careful, this will have an overrun of the
	}

	keep_window_open();
	return 0;
}
