/* @brief Assignment from chapter 4 exercise 7.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Modify the “mini calculator” from exercise 5 to accept (just) single-digit
 * numbers written as either digits or spelled out.
 */

#include "../std_lib_facilities.h"

int spellToDig(string input)
{
	/*@brief COnvert spelled out numbers to digits
	 * @output Two cases: Case '-1' Error: The input number could not be identified as a digit between 1 and 9.
	 * 		   '>-1' The input is a valid number between 0 and 9.*/
	int out = -1;
	if (input == "zero")		out = 0;
	else if (input == "one") 	out = 1;
	else if (input == "two") 	out = 2;
	else if (input == "three") 	out = 3;
	else if (input == "four") 	out = 4;
	else if (input == "five") 	out = 5;
	else if (input == "six") 	out = 6;
	else if (input == "seven") 	out = 7;
	else if (input == "eight") 	out = 8;
	else if (input == "nine") 	out = 9;
	else
	{
		cerr << "This '" << input << "' is an unknown spelled out number." << endl;
		out = -1;
	}
	return out;
}

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
			cout << "The multiplication of " << input1 << " and " << input2 << " is " << input1 * input2 << "." << endl;
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

	cout << "This is a simple calculator. Please type in a positive single digit number," << endl;
	cout << "followed by an operator (+, -- *, /), a number, and the enter button." << endl;
	cout << "You can use spelled out numbers like 'one', 'seven' or digits '1', '7', etc.." << endl;
	cout << "Please use the space button ' ' between the entries." << endl;
	cout << "In one calculation, only one type of digits is allowed. Example for an invalid entry: 'seven * 5'." << endl;
	cout << "The computer will return the result of your calculation." << endl;

	string in1	{}, in2	{}; // save user input
	int val1 {}, val2{};
	char op {}; //operator

	// Allow multiple calculations using a loop
	while (cin >> in1)
	{
		//Interestingly, the application takes care of the correct processing of char and double!
		cin >> op;
		cin >> in2;

		// transform user input into numbers so that calculations can be performed
		val1 = spellToDig(in1);
		val2 = spellToDig(in2);
		if ( (val1 > -1) && (val2 > -1)) calc(val1, val2, op);
		else
		{
			//convert string inputs to integers
			val1 = stoi(in1);
			val2 = stoi(in2);
			calc(val1, val2, op);
		}
		cout << "You can perform a new calculation or abort with CTRL+Z." << endl;
	}

	keep_window_open();
	return 0;
}
