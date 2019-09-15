/* @brief Assignment from chapter 6 exercise 8.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Redo the “Bulls and Cows” game from exercise 12 in Chapter 5 to use
 * four letters rather than four digits.
 *
 * REMINDER from chapter 5 exercise 12:
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

vector<char> getSingleLetters(string usrInput)
{
	/* @brief Divide the input string into single letters.
	 * 		Example: 'clan' returns a vector of {c, l, a, n}
	 *
	 * @input getSingleLetters Four letters.
	 * @ouput digitizedNumber The four digit letters as a vector. Example: 'clan' returns a vector of {c, l, a, n}
	 * */

	vector<char> slicedLetters = {usrInput[0], usrInput[1], usrInput[2], usrInput[3]}; // Careful! Accessing one element of a string returns a a char (!)
 	return slicedLetters;
}

bool handleInput(string usrInput)
{
	/* @brief Handle the user input and return faults if the input does not comply with the expectations.
	 * . A string with four unique letters is expected.
	 *
	 * @input usrInput An string that should be four letters, e.g 'clan'.
	 * */
	bool inputValid = true; // if true, then the usrInput is correct.
	// handle inputs that are not equal to four letters
	if ( usrInput.length() != 4)
	{
		inputValid = false;
		cerr << "The input you provided '" << usrInput << "' is invalid, because it is out of range. Please provide exactly four letters." << endl;
	}
	// handle doubles. A letter is not allowed to be used twice within the string, e.g. "cool" contains "o" twice
	vector<char> usrInputSingles = {};
	usrInputSingles = getSingleLetters(usrInput);
	sort(usrInputSingles); // makes it easier to identify unique entries
	for (int i = 1; i < usrInputSingles.size(); ++i)
	{
		if(usrInputSingles[i-1] == usrInputSingles[i]) // This logic is only possible, because a sorted vector is used
		{
			inputValid = false;
			cerr << "The input you provided '" << usrInput << "' is invalid, because it has a non-unique letter. The non-unique letter is: " << usrInputSingles[i] << ". " << endl;
			break; // avoid displaying the above message more than once, if a digit is repeated more than two times.
		}
	}
	return inputValid;
}

vector<int> getBullsAndCows(string guess, string goal)
{
	/*@brief Guess the number of bulls and cows from an input guess and the goal letters.
	 *
	 * @input guess The guessed letters contains four letters.
	 * @input goal The reference letters are a four letters that need to be guessed correctly.
	 *
	 * @output bullsAndCows A vector containing the bulls and cows based on the comparison
	 * 		of the two inputs. The zero element is  the bulls and the first element
	 * 		is the cows.
	 * */
	vector<int> bullsAndCows	= {0, 0};
	vector<char> guessSingles	= {}; 	// Contains the 'guess' -> user input.
	vector<char> goalSingles	= {};	// contains the four letters that have to be guessed correctly.
	// idea: Divide the number in the thousands, hundreds, tens, and singles. Then compare them.
	// step 1: divide the numbers into digits
	guessSingles	= getSingleLetters(guess);
	goalSingles	= getSingleLetters(goal);

	// step 2: search for bulls and cows
	for(unsigned int i = 0; i < guessSingles.size(); i++)
	{
//		cout << "DEBUG guessSingles[" << i  << "] =" << guessSingles[i] << endl;
//		cout << "DEBUG goalSingles[" << i  << "] =" << goalSingles[i] << endl;
		for(unsigned int j = 0; j < goalSingles.size(); j++)
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
	/* @brief Determine if all bulls are discovered.
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
	string goal = "crow"; // the "random" number that the player should guess
	string usrInput = ""; // the user input should always be larger than 0
	bool winFlag	= false; // A flag that signalizes whether the player has won the match
	bool inputValid	= false; // If true, then the user input number is valid and can be processed for guessing.
	vector<int> bullsAndCows = {0, 0}; // The amount of bulls (0th element) and cows (1st element).

	cout << "Dear player. Welcome to the 'bulls and cows' guessing game. " << endl;
	cout << "The guessing game consists of guessing correctly four letters." << endl;
	cout << "The program will process your input and compare it with the random letters that you need to guess correctly." << endl;
	cout << "If you guess a letter correctly and at the correct position, then you get a bull." << endl;
	cout << "If you guess a letter correctly, but at the wrong position, then you get a cow." << endl;
	cout << "Example: the letters to be guessed are: 'caso'. The player's guess is 'clan'." << endl;
	cout << "Then the result is 1 bull, 1 cow. The bull for letter 'c' and the cow for letter 'a'." << endl;
	cout << "The letters should have unique letters only, e.g. 'clan' is allowed, but 'casa' is not." << endl;
	cout << "In other words: your guess is also only allowed to contain unique letters." << endl;
	cout << "The player can abort the game by pressing the buttons 'Ctrl + Z'" << endl;
	cout << "Let the game begin!" << endl;
	cout << endl << "Please type in your guess and push the 'Enter' button: " << endl;

	// Repeatedly process the user input and check if the user guessed the random word correctly.
	// Only one word is provided in the application.
	// Application finishes once the random word was guessed correctly.
	while (winFlag == false)
	{
		cin >> usrInput;
		if (!cin) throw runtime_error("The input you have entered is invalid. Only letters are allowed as input values. Please restart the application.");
		inputValid = handleInput(usrInput);
		if (inputValid)
		{
			bullsAndCows = getBullsAndCows(usrInput, goal);
			winFlag	= getResult(bullsAndCows);
		}
		if (winFlag)
		{
			cout << "You have won the game. The random letters were: " << goal << endl;
			cout << "Your guess is: " << usrInput << endl;
			cout << "The application will be closed, now." << endl;
			break; // exit the application
		}
		else
		{
			cout << "This are not the letters I am looking for. Please try again: " << endl;
		}
	}
	keep_window_open();
	return 0;
}
