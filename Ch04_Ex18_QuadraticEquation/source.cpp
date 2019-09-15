/* @brief Assignment from chapter 4 exercise 18.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program to solve quadratic equations. A quadratic equation is of
 * the form
 * a*x^2 + b*x + c = 0
 * If you don’t know the quadratic formula for solving such an expression,
 * do some research. Remember, researching how to solve a problem is often
 * necessary before a programmer can teach the computer how to solve
 * it. Use doubles for the user inputs for a, b, and c. Since there are two
 * solutions to a quadratic equation, output both x1 and x2.
 */

#include "../std_lib_facilities.h"

void solveQuadraticEq(double a, double b, double c)
{
	/*@brief Solve a quadratic equation of the form:
	 * 		a*x^2 + b*x + c = 0
	 *
	 * @input a, b, c Parameters of the quadratic equation
	 * */
	double x0, x1; // solutions of the quadartic equation
	// precondition:
	// (b^2 - 4*a*c) < 0 (solution with "complex" numbers)
	if ((b*b - 4*a*c) < 0)
	{
		cerr << "There is no solution with real numbers available for your parameters. Consider using complex numbers" << endl;
	}
	else if(a == 0)
	{
		cerr << "The parameter a is zero. The application cannot handle this input." << endl;
	}
	else
	{
		x0 = (-b + sqrt(b*b - 4*a*c)) / (2*a);
		x1 = (-b - sqrt(b*b - 4*a*c)) / (2*a);
		cout << "The results for the quadratic equation are: " << x0 << " and: " << x1 << "." << endl;
	}
}

int main()
{
	double a{0}, b{0}, c{0}; // user inputs

	cout << "This application solves a quadratic equation, based on the user input." << endl;
	cout << "A quadratic equation is of the form:" << endl;
	cout << "a*x^2 + b*x + c = 0" << endl;
	cout << "Please type in your parameters a, b, and c starting with 'a'." << endl;
	cout << "Your input for a: " << endl;

	while (cin >> a)
	{
		cout << "Your input for b: " << endl;
		cin >> b;
		cout << "Your input for c: " << endl;
		cin >> c;

		solveQuadraticEq(a, b, c);

		cout << "Time for a new quadratic equation. Please type in your input for 'a':" << endl;
	}
	keep_window_open();
	return 0;
}
