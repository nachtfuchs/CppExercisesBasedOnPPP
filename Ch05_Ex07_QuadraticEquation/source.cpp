/* @brief Assignment from chapter 5 exercise 7.
 * Book: Programming Principle and Practice using C++ (Second Edition) - Stroustrup
 *
 * Quadratic equations are of the form
 * a*(x^2) + b*x + c = 0
 * To solve these, one uses the quadratic formula:
 * x_1, x_2 = (-b -+ sqrt(b^2 - 4*a*c) ) / (2*a)
 *
 * There is a problem, though: if b2–4ac is less than zero, then it will fail.
 * Write a program that can calculate x for a quadratic equation. Create a
 * function that prints out the roots of a quadratic equation, given a, b, c.
 * When the program detects an equation with no real roots, have it print
 * out a message. How do you know that your results are plausible? Can
 * you check that they are correct?
 *
 */

#include "../std_lib_facilities.h"

void solveQuadraticEquation(double a, double b, double c)
{
	/*@brief solve a quadaratic equation of the form a*(x^2) + b*x + c = 0
	 * and return its solutions*/

	// Pre-Conditions:
	if(( b*b -4*a*c ) < 0) throw runtime_error("ERROR: The solution for the quadratic equation has complex numbers.");
	if(a == 0) throw runtime_error("The parameter 'a' is zero. The application cannot handle this input.");

	// actual calculation
	double x0{}, x1{};
	x0 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
	x1 = (-b - sqrt(b*b - 4*a*c)) / (2*a);

	// Post - Conditions: Both solutions should result in "0" regarding numerical inaccuracies.
	double s0 {a*(x0*x0) + b*x0 + c}, s1 {a*(x1*x1) + b*x1 + c};
	if ( s0 > -0.001 && s0 < 0.001 && s1 > -0.001 && s1 < 0.001)
		cout << "The results for the quadratic equation are: " << x0 << " and: " << x1 << "." << endl;
	else
		throw runtime_error("ERROR: Post conditions not fulfilled. Solutions are not close to zero.");
}

int main()
{
	cout << "This application is able to solve quadratic equations of the form:" << endl;
	cout << " a*(x^2) + b*x + c = 0 " << endl;
	cout << "Please type in the values for a, b, and c separated by a space and push the enter button." << endl;
	cout << "Your input: " << endl;

	double a {}, b {}, c {};

	// get the user input
	cin >> a;
	cin >> b;
	cin >> c;

	solveQuadraticEquation(a, b, c);

	keep_window_open();
	return 0;
}
