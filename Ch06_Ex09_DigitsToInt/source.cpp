/* @brief Assignment from chapter 8 exercise 9.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program that reads digits and composes them into integers. For
 * example, 123 is read as the characters 1, 2, and 3. The program should
 * output 123 is 1 hundred and 2 tens and 3 ones. The number should be
 * output as an int value. Handle numbers with one, two, three, or four
 * digits. Hint: To get the integer value 5 from the character '5' subtract '0',
 * that is, '5'–'0'==5.
 */

/* NOTE: My solution is very simple, and does not address a lot of the grammar
 * 		topic that was taught in the book in chapter 6. I wonder what the
 * 		assignment is about?
 * */

#include "../std_lib_facilities.h"

void printNumberAsDomain(vector<int> inputNumbers)
{
	/* @brief Print the numbers in the input vector by domain.
	 * 		E.g. "123 is 1 hundred and 2 tens and 3 ones"
	 *
	 * @input inputNumbers A vector up to four numbers that contains the highest value in the zero element
	 * 						e.g. 123 -> {1, 2, 3}
	 * */
	unsigned int sum {0};
	string res {" is"};
	cout << "DEBUG inputNumbers.size(): " << inputNumbers.size() << endl;
	for (int i = inputNumbers.size() - 1; i >= 0; i--)
	{
		cout << "DEBUG: " << i << endl;
		if (i == 3)
		{
			sum += inputNumbers[inputNumbers.size() - 1 - i] * 10 * 10 * 10;
			res += " " + to_string(inputNumbers[inputNumbers.size() - 1 - i]) + " thousand and";
		}
		if (i == 2)
		{
			sum += inputNumbers[inputNumbers.size() - 1 - i] * 10 * 10;
			res += " " + to_string(inputNumbers[inputNumbers.size() - 1 - i]) + " hundred and";
		}
		if (i == 1)
		{
			sum += inputNumbers[inputNumbers.size() - 1 - i] * 10;
			res += " " + to_string(inputNumbers[inputNumbers.size() - 1 - i]) + " tens and";
		}
		if (i == 0)
		{
			sum += inputNumbers[inputNumbers.size() - 1 - i];
			res += " " + to_string(inputNumbers[inputNumbers.size() - 1 - i]) + " ones";
		}
	}
	cout << sum << res << endl;
}

int main()
{
	cout << "This application will allow you to enter up to four digits." << endl;
	cout << "The digit should be a positive number between 0 an 9." << endl;
	cout << "Afterwards, it will process your digits and return the resulting integer number." << endl;
	cout << "You can finish your entries by typing the #-sign." << endl;
	cout << "Please type in your digits:" << endl;

	char usrInput {};
	vector<int> numbers {}; // will contain the four numbers
	for(unsigned int i = 0; i < 4 and usrInput != '#'; i++)// allow four numbers to be entered
	{
		cin >> usrInput;
		if (usrInput == '#')
			break; // exit the for loop
		switch (usrInput)
		{
			case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
				numbers.push_back(usrInput - '0'); // accumulate the numbers in the target vector, but be careful,
													// the first element has the highest rating
				break;
			case '#': // do nothing
				break;
			default:
				error("Bad input.");
				break;
		}
	}
	printNumberAsDomain(numbers);

	keep_window_open();
	return 0;
}
