/* @brief Assignment from chapter 5 exercise 4.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Do exercise 3 again, but this time handle the error inside ctok().
 */

#include "../std_lib_facilities.h"

double ctok(double c) // converts Celsius to Kelvin
{
	// Check precondition
	if (c < -273.15)
	{
		cerr << "The temperature is below -273.15 degrees Celsius. Only temperatures above -273.15 degrees celsius are physically possibly. Your input temperature: " << c << endl;
		return -1;
	}
	else
	{
		double k = c + 273.15;
		return k;
	}
}

int main()
{
	double c = 0; // declare input variable
	cin >> c; // retrieve temperature to input variable
	double k = ctok(c); // convert temperature
	cout << k << '\n' ; // print out temperature

	keep_window_open();
	return 0;
}
