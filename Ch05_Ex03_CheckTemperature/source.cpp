/* @brief Assignment from chapter 5 exercise 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * #include "../std_lib_facilities.h"
 *
 * double ctok(double c) // converts Celsius to Kelvin
 * {
 * 	double k = c + 273.15;
 * 	return k;
 * }
 *
 * int main()
 * {
 * 	double c = 0; // declare input variable
 * 	cin >> c; // retrieve temperature to input variable
 * 	double k = ctok(c); // convert temperature
 * 	cout << k << '\n' ; // print out temperature
 *
 * 	keep_window_open();
 * 	return 0;
 * }
 *
 *
 * Absolute zero is the lowest temperature that can be reached; it is –273.15°C,
 * or 0K. The above program, even when corrected, will produce erroneous results
 * when given a temperature below this. Place a check in the
 * main program that will produce an error if a temperature is given below
 * –273.15°C.
 */

#include "../std_lib_facilities.h"

double ctok(double c) // converts Celsius to Kelvin
{
	double k = c + 273.15;
	return k;
}

int main()
{
	double c = 0; // declare input variable
	cin >> c; // retrieve temperature to input variable
	if (c < -273.15) cerr << "The temperature is below -273.15 degrees Celsius. Only temperatures above -273.15 degrees celsius are physically possibly. Your input temperature: " << c << endl;
	double k = ctok(c); // convert temperature
	cout << k << '\n' ; // print out temperature

	keep_window_open();
	return 0;
}
