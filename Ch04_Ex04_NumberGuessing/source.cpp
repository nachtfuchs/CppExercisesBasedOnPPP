/* @brief Assignment from chapter 4 exercise 4.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program to play a numbers guessing game. The user thinks of a
 * number between 1 and 100 and your program asks questions to figure
 * out what the number is (e.g., “Is the number you are thinking of less than
 * 50?”). Your program should be able to identify the number after asking
 * no more than seven questions. Hint: Use the < and <= operators and the
 * if-else construct.
 */

#include "../std_lib_facilities.h"

int numberGuess( int inputMax, int inputMin);

int main()
{

	cout << "This is a number guessing game. Please enter an integer between 1 and 100 and the " << endl;
	cout << "computer will guess your number by asking at most seven questions." << endl;
	cout << "Please enter your number: " << endl;

	int userInput {-1};
	int guessedNumber {-1};
	int largest {10}; // the largest number that can be guessed
	int smallest {1}; // The lowest allowed input
	cin >> userInput;

	guessedNumber = numberGuess(largest, smallest);

	cout << "The computer guessed the number: " << guessedNumber << endl;
	keep_window_open();
	return 0;
}


int numberGuess( int inputMax, int inputMin)
{
	/*@brief Guess the number based on the input. Recursive function!*/
	char guessCheck {'n'}; // Overwritten by player whether guess was correct or not.
	char uResponse {}; // user response. Expects 'y' or 'n'.
	// todo: base case???
	if (inputMax/2 <= inputMin)
	{
		cout << "I guess your number is: " << inputMax/2 << endl;
		cout << "Did I guess successfully? ('y', 'n')?" << endl;
		cout << "Your response: " << endl;
		cin >> guessCheck;
		if (guessCheck == 'y')
		{
			cout << "Thank you for playing!" << endl;
		}
		else if (guessCheck == 'n')
		{
			cout << "But I tried so hard! My logic must be flawed :-(." << endl;
		}
		else
		{
			cout << "I do not understand your response :-(." << endl;
		}
	}
	else
	{
		cout << "Is your number smaller or equal than " << inputMax/2 << " ?" << endl;
		cout << "Please answer with 'y'es or 'n'o: " << endl;
		cin >> uResponse;

		if (uResponse == 'y')
		{
			numberGuess(inputMax/2, inputMin);
		}
		else if (uResponse == 'n')
		{
			// The largest number has to be increased by "50 Percent";
			// Tne new lowest number is taken from the previous largest number.
			numberGuess(inputMax/2 + inputMax/4, inputMax/2);
		}
	}
	return inputMax/2;
}
