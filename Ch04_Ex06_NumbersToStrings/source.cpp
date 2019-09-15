/* @brief Assignment from chapter 4 exercise 6.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Make a vector holding the ten string values "zero", "one", . . . "nine".
 * Use that in a program that converts a digit to its corresponding
 * spelled-out value; e.g., the input 7 gives the output seven. Have the same
 * program, using the same input loop, convert spelled-out numbers into
 * their digit form; e.g., the input seven gives the output 7.
 */

#include "../std_lib_facilities.h"

bool spellToDig(string input)
{
	/*@brief COnvert spelled out numbers to digits.*/
	if (input == "zero") cout 		<< "Digit: " << 0 << endl;
	else if (input == "one") cout 	<< "Digit: " << 1 << endl;
	else if (input == "two") cout 	<< "Digit: " << 2 << endl;
	else if (input == "three") cout << "Digit: " << 3 << endl;
	else if (input == "four") cout 	<< "Digit: " << 4 << endl;
	else if (input == "five") cout 	<< "Digit: " << 5 << endl;
	else if (input == "six") cout 	<< "Digit: " << 6 << endl;
	else if (input == "seven") cout << "Digit: " << 7 << endl;
	else if (input == "eight") cout << "Digit: " << 8 << endl;
	else if (input == "nine") cout 	<< "Digit: " << 9 << endl;
	else
	{
		cout << "This is an unknown spelled out number." << endl;
		return false;
	}
	return true;
}

bool digToSpell(int input)
{
	/*@brief Converts a digit number into a spelled out number.*/
	switch (input)
	{
		case 0:
			cout << "Spelled out number: " << "zero" << endl;
			break;
		case 1:
			cout << "Spelled out number: " << "one" << endl;
			break;
		case 2:
			cout << "Spelled out number: " << "two" << endl;
			break;
		case 3:
			cout << "Spelled out number: " << "three" << endl;
			break;
		case 4:
			cout << "Spelled out number: " << "four" << endl;
			break;
		case 5:
			cout << "Spelled out number: " << "five" << endl;
			break;
		case 6:
			cout << "Spelled out number: " << "six" << endl;
			break;
		case 7:
			cout << "Spelled out number: " << "seven" << endl;
			break;
		case 8:
			cout << "Spelled out number: " << "eight" << endl;
			break;
		case 9:
			cout << "Spelled out number: " << "nine" << endl;
			break;
		default:
			cout << "The spelled out number " << input << " is unknown to me." << endl;
			return false;
			break;
	}
	return true;
}

int main()
{
	string userInput {};

	cout << "Please type a spelled out number or a digit and it will be converted to the 'opposite'. " << endl;
	cout << "Example: your input 'seven' returns '7'. The input '2' two returns 'two'." << endl;
	cout << "Only numbers between 0 and 9 are allowed for one entry." << endl;
	cout << "Your input, please: " << endl;

	vector<string> spelledNumbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	for (int i = 0; cin >> userInput; i++)
	{
		if (spellToDig(userInput))
		{
			// do nothing
		}
//		else digToSpell( stoi(userInput) ); //Solution without vector
		else cout << "The spelled out number is: " << spelledNumbers[stoi(userInput)] << endl; // solution with vector
		cout << "Try a new run, or abort by pressing 'CTRL + Z'" << endl;
		cout << "Your input, please: " << endl;
	}

	keep_window_open();
	return 0;
}
