/* @brief Assignment from chapter 5 exercise 5.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Add to the program so that it can also convert from Kelvin to Celsius.
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

double kToC(double k)
{
	/*@brief Convert Kelvin to Celsius*/
	if (k < 0)
	{
		cerr << "The temperature is below 0 degrees Kelvin. Only temperatures above 0 degrees Kelvin are physically possibly. Your input temperature: " << k << endl;
		return -1;
	}
	else
	{
		return k-273.15;
	}
}

int main()
{
	double k = 0; // declare input variable
	cin >> k; // retrieve temperature to input variable
	double c = kToC(k); // convert temperature
	cout << c << " degree Celsius\n" ; // print out temperature

	keep_window_open();
	return 0;
}
