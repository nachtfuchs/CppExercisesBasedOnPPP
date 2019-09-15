/* @brief Assignment from chapter 5 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that converts from Celsius to Fahrenheit and from
 * Fahrenheit to Celsius (formula in §4.3.3). Use estimation (§5.8)
 * to see if your results are plausible.
 * Formula: df = 9.0/5*dc+32 // from Celsius to Fahrenheit
 */

#include "../std_lib_facilities.h"

double cToF(double c) // Converts from Celsius to Fahrenheit
{
	if (c < -273.15) throw runtime_error("ERROR: The temperature is below the absolute zero of -273.15 degrees Celsius.");
	else
	{
		double f = 9.0/5*c+32;
		return f;
	}
}

double fToC(double f) // Converts from Fahrenheit to Celsius
{
	if (f < -459.67) throw runtime_error("ERROR: The temperature is below the absolute zero of -459.67 degrees Fahrenheit.");
	else
	{
		double c = 5.0/9*(f-32);
		return c;
	}
}

int main()
{
	double temp;
	cout << "Please type in a temperature in Fahrenheit: " << endl;
	cin >> temp;
	cout << "Your temperature in C: " << fToC(temp) << endl;
//	cout << "DEBUG: " << cToF(fToC(temp)) << endl;
	cout << "Please type in a temperature in Celsius: " << endl;
	cin >> temp;
	cout << "Your temperature in F: " << cToF(temp) << endl;
	keep_window_open();
	return 0;
}
