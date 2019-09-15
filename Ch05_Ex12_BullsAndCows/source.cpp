/* @brief Assignment from chapter 5 exercise 12.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Implement a little guessing game called (for some obscure reason) “Bulls
 * and Cows.” The program has a vector of four different integers in the
 * range 0 to 9 (e.g., 1234 but not 1122) and it is the user’s task to discover
 * those numbers by repeated guesses. Say the number to be guessed is 1234
 * and the user guesses 1359; the response should be “1 bull and 1 cow”
 * because the user got one digit (1) right and in the right position (a bull)
 * and one digit (3) right but in the wrong position (a cow). The guessing
 * continues until the user gets four bulls, that is, has the four digits correct
 * and in the correct order.
 */

#include "../std_lib_facilities.h"

vector<int> getSingleDigits(double inputNumber)
{
	/* @brief Divide the input number into single digits of singles, tens, hundreds, and thousands.
	 * 		Example: 4321 returns a vector of {1, 2, 3, 4}
	 *
	 * @input inputNumber a four digit number.
	 * @ouput digitizedNumber The four digit number as a vector. Example: 4321 returns a vector of {1, 2, 3, 4}
	 * */
	int thousand 	= 0;
	int hundred		= 0;
	int ten		= 0;
	int single	= 0;

	//get the digits
	thousand	= inputNumber / 1000;
	hundred	= (inputNumber - thousand * 1000) / 100;
	ten	= (inputNumber - thousand * 1000 - hundred * 100) / 10;
	single	= (inputNumber - thousand * 1000 - hundred * 100 - ten * 10);

	vector<int> digitizedNumber = {single, ten, hundred, thousand};
//	cout << "DEBUG - digitizedNumber = " << digitizedNumber[0] << " " << digitizedNumber[1] << " " << digitizedNumber[2] << " " << digitizedNumber[3] << endl;
 	return digitizedNumber;
}

bool handleInput(double usrInput)
{
	/* @brief Handle the user input and return faults if the input does not comply with the expectations.
	 * . An integer number with four digits is expected.
	 *
	 * @input usrInput An input number that should be a four digit number, e.g 9870.
	 * */
	bool inputValid = true; // if true, then the usrInput is correct.
	// handle numbers less than 1000 and larger than 9999. Less than 1000, or else the "preceding zeros" would be non-unique.
	if ( (usrInput < 1000) || (usrInput > 9999) )
	{
		inputValid = false;
		cout << "The input you provided '" << usrInput << "' is invalid, because it is out of range. Please provide a four digit number." << endl;
	}
	// make sure that only integer numbers are provided
	if ( (usrInput - int(usrInput)) != 0)
	{
		inputValid = false;
		cout << "The input you provided is invalid, because it is not an integer number, but a decimal number. Your input was: " << usrInput << endl;
	}
	// handle doubles. A digit is not allowed to be used twice within the number. E.g. 4365 is allowed, but 4436, or 3123 are not allowed.
	vector<int> usrInputSingles = {};
	usrInputSingles = getSingleDigits(usrInput);
	sort(usrInputSingles); // makes it easier to identify unique entries
	for (int i = 1; i < usrInputSingles.size(); ++i)
	{
		if(usrInputSingles[i-1] == usrInputSingles[i])
		{
			inputValid = false;
			cout << "The input you provided '" << usrInput << "' is invalid, because it has a non-unique digit. The non-unique digit is: " << usrInputSingles[i] << ". " << endl;
			break; // avoid displaying the above message more than once, if a digit is repeated more than two times.
		}
	}
	return inputValid;
}

vector<int> getBullsAndCows(double guess, int goal)
{
	/*@brief Guess the number of bulls and cows from an input guess and the goal number.
	 *
	 * @input guess The guessed number is a number between 0 and 9999.
	 * @input goal The reference number is the number that needs to be guessed correctly.
	 *
	 * @output bullsAndCows A vector containing the bulls and cows based on the comparison
	 * 		of the two input numbers. The zero element are the bulls and the first element
	 * 		are the cows.
	 * */
	vector<int> bullsAndCows	= {0, 0};
	vector<int> guessSingles	= {}; 	// contains the singles, tens, hundres and thousands
										//as single digits in the zero element, first element, second element etc.
	vector<int> goalSingles	= {};	// contains the singles, tens, hundres and thousands
									//as single digits in the zero element, first element, second element etc.
	// idea: Divide the number in the thousands, hundreds, tens, and singles. Then compare them.
	// step 1: divide the numbers into digits
	guessSingles	= getSingleDigits(guess);
	goalSingles	= getSingleDigits(goal);

	// step 2: search for bulls and cows
	for(int i = 0; i < guessSingles.size(); i++)
	{
		for(int j = 0; j < goalSingles.size(); j++)
		{
			if(guessSingles[i] == goalSingles[j])
			{
				// if it is the same position in the number, then it is a bull
				if (i == j)
					bullsAndCows[0] += 1;
				else // if it equals at different positions, then it is a cow
					bullsAndCows[1] += 1;
			}
		}
	}
	return bullsAndCows;
}

bool getResult(vector<int> bullsAndCows)
{
	/* @brief Determine if all all bulls are discovered.
	 *
	 * @input bullsAndCows If the first element equals 4, then four bulls were discovered.
	 * 		The output is true
	 * */
	if(bullsAndCows[0] == 4)
		return true;
	if(bullsAndCows[0] < 4)
		cout << "You found " << bullsAndCows[0] << " bulls, and " << bullsAndCows[1] << " cows." << endl;
	return false;
}

int main()
{
	int goal = 1248; // the "random" number that the player should guess
	double usrInput = -1; // the user input should always be larger than 0
	bool winFlag	= false; // A flag that signalises if the player has won the match
	bool inputValid	= false; // If true, then the user input number is valid and can be processed for guessing.
	vector<int> bullsAndCows = {0, 0}; // The amount of bulls (0th element) and cows (1st element).

	cout << "Dear player. Welcome to the 'bulls and cows' guessing game. " << endl;
	cout << "The guessing game consists of guessing correctly a four digit number." << endl;
	cout << "The program will process your input and compare it with the random digit number that oyu need to guess correctly." << endl;
	cout << "If you guess a number correctly and the correct position, then you get a bull." << endl;
	cout << "If you guess a number correctly, but at the wrong position, then you get a cow." << endl;
	cout << "Example: the number to be guessed is: 9876. The player's guess is 7456." << endl;
	cout << "Then the result is 1 bull, 1 cow. The bull for digit 6 and the cow for digit 7." << endl;
	cout << "The number should have unique digits only, e.g. 1234 is allowed, but 1123 is not." << endl;
	cout << "Your guess is also only allowed to be a number with unique digits." << endl;
	cout << "The player can abort the game by pressing the buttons 'Ctrl + Z'" << endl;
	cout << "Let the game begin!" << endl;
	cout << endl << "Please type in your guess and push the 'Enter' button: " << endl;

	// Repeatedly process the user input and check if the user guessed the random number correctly.
	// Only one number is provided in the application.
	// Application finishes once the random number was guessed correctly.
	while (winFlag == false)
	{
		cin >> usrInput;
		if (!cin) throw runtime_error("The input you have entered is invalid. Only numbers are allowed as input values. Please restart the application.");
		inputValid = handleInput(usrInput);
		if (inputValid)
		{
			bullsAndCows = getBullsAndCows(usrInput, goal);
			winFlag	= getResult(bullsAndCows);
		}
		if (winFlag)
		{
			cout << "You have won the game. The random number was: " << goal << endl;
			cout << "Your guess is: " << usrInput << endl;
			cout << "The application will be closed, now." << endl;
			break; // exit the application
		}
		else
		{
			cout << "That's not the number I am looking for. Please try again: " << endl;
		}
	}
	keep_window_open();
	return 0;
}
