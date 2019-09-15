/* @brief Assignment from chapter 4 exercise 5.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that performs as a very simple calculator. Your calculator
 * should be able to handle the four basic math operations — add, subtract,
 * multiply, and divide — on two input values. Your program should prompt
 * the user to enter three arguments: two double values and a character to
 * represent an operation. If the entry arguments are 35.6, 24.1, and '+', the
 * program output should be The sum of 35.6 and 24.1 is 59.7. In Chapter 6
 * we look at a much more sophisticated simple calculator.
 */

#include "../std_lib_facilities.h"

void calc( double input1, double input2, char op)
{
	/*@brief Perform a calculation based on the input parameters
	 * @input1 a double number
	 * @input2 a double number
	 * @op Mathematical operator. Allowed oerators: +, -, *, /
	 *
	 * @return display calculation result into command window
	 * */
	switch (op)
	{
		case '+':
			cout << "The sum of " << input1 << " and " << input2 << " is " << input1 + input2 << "." << endl;
			break;
		case '-':
			cout << "The difference of " << input1 << " and " << input2 << " is " << input1 - input2 << "." << endl;
			break;
		case '*':
			cout << "The multplication of " << input1 << " and " << input2 << " is " << input1 * input2 << "." << endl;
			break;
		case '/':
			cout << "The division of " << input1 << " and " << input2 << " is " << input1 / input2 << "." << endl;
			break;
		default:
			cerr << "The operator you have entered '" << op << "' is unknown to my CPU." << endl;
			break;
	}
}

int main()
{

	cout << "This is a simple calculator. Please type in a number," << endl;
	cout << "followed by an operator (+, -- *, /), a number, and the enter button." << endl;
	cout << "The computer will you return the result of your calculation." << endl;

	double in1 {}, in2{}; // save user input
	char op {}; //operator

	// ALlow mulitple calculations using a loop
	while (cin >> in1)
	{
		//Interestingly, the application takes care of the correct processing of char and double!
		cin >> op;
		cin >> in2;
		calc(in1, in2, op);
		cout << "You can perform a new calculation or abort with CTRL+Z." << endl;
	}

	keep_window_open();
	return 0;
}
