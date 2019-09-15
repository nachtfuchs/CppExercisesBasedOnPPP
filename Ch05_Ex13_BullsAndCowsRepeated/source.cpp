/* @brief Assignment from chapter 5 exercise 13.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * The program (from chapter 5 exercise 12) is a bit tedious because the answer is hard-coded into the
 * program. Make a version where the user can play repeatedly (without
 * stopping and restarting the program) and each game has a new set of
 * four digits. You can get four random digits by calling the random number
 * generator randint(10) from std_lib_facilities.h four times. You will note
 * that if you run that program repeatedly, it will pick the same sequence of
 * four digits each time you start the program. To avoid that, ask the user
 * to enter a number (any number) and call srand(n) where n is the number
 * the user entered before calling randint(10). Such an n is called a seed, and
 * different seeds give different sequences of random numbers.
 */
// NOTE: randint(10) does not generate random numbers with different seeds. Therefore, use
//		 rand()%10 to generate random numbers in the range of [0-9]

#include "../std_lib_facilities.h"

vector<int> getSingleDigits(double inputNumber)
{
	/* @brief Divide the input number into single digits of singles, tens, hundreds, and thousands.
	 * 		Example: 4321 returns a vector of {1, 2, 3, 4}
	 *
	 * @input inputNumber a four digit number.
	 * @ouput digitizedNumber The four digit number as a vector. Example: 4321 returns the vector {1, 2, 3, 4}
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

int bullsAndCowsNumber(unsigned int seed)
{
	/* @brief Create a random number between 1000 and 9999 that fulfills the conditions of
	 * the "Bulls and Cows" guessing game. It should be a four digit number where each digit
	 * is unique.
	 * */
	vector<int> randNumSingles(4); // the random number that should contain four digits
	int randomNumber = 0; //the random number that should fulfill the conditions of the guessing game
	int digit = -1; //one digit that will be used for the four digit number
	bool guessing = true; // Flag that shows if new digit was determined.
	srand(seed);
//	randNumSingles[0] = randint(0, 10); // start with the first digit
	randNumSingles[0] = rand()%10; // start with the first digit
//	cout << "DEBUG - randNumSingles[0] = " << randNumSingles[0] << endl;
	// create three more random digits. Each of the digits should be "unique"
	for (int i = 1; i < 4; i++) // "1", because one number was already created. "4", because in total, a four digit number is necessary
	{
		// guess until the random digit is a unique digit of the target four digit number.
		while (guessing)
		{
			int nonUniqueCounter = 0; // Counts the number of repetitions of a digit in the target random number
			digit = rand()%10;
			// check if new random digit is "unique"
			for (int j = 0; j < randNumSingles.size(); j++)
			{
				if (digit == randNumSingles[j])
				{
					nonUniqueCounter++; // new digit is not unique. Continue guessing
				}
			}
			if (nonUniqueCounter > 0)
				guessing = true; // continue searching for a non-unique digit
			else
				guessing = false; // a new unique digit was found
		}
//		cout << "DEBUG - guessing for the " << i << " digit. Found digit: " << digit << endl;
		randNumSingles[i] = digit; // add a new, unique digit to the target random four-digit number
		guessing = true; // start guessing again
	}
	// create the random number as a single digit number from the single digits:
	randomNumber = randNumSingles[0] + randNumSingles[1] * 10 + randNumSingles[2] * 100 + randNumSingles[3] * 1000;
	cout << "DEBUG - randomNumber = " << randomNumber << endl;
	return randomNumber;
}

int main()
{
	int goal = -1; // the "random" number that the player should guess
	double usrInput = -1; // the user input should always be larger than 0
	bool winFlag	= false; // A flag that signalizes if the player has won the match
	bool newGame	= false; // A flag that signalizes if the player wants to start a new game.
	bool inputValid	= false; // If true, then the user input number is valid and can be processed for guessing.
	unsigned int seed = 0;
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
	cout << "Before the game can begin, you need to enter the current minute of the time:" << endl;
	cout << "Please enter the minute: " << endl;
	cin >> seed;
	if (!cin) throw runtime_error("The input you have entered is invalid! Only numbers are allowed as input values. Please restart the application.");
	//create the goal goal number that the user should guess:
	goal = bullsAndCowsNumber(seed);
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
		if (inputValid) // start the game only if the user provided a valid four digit number.
		{
			bullsAndCows = getBullsAndCows(usrInput, goal);
			winFlag	= getResult(bullsAndCows);
		}
		if (winFlag) // if player guessed correctly, then either a new game can be started or the game can be aborted.
		{
			cout << "You have WON the game. The random number was: " << goal << endl;
			cout << "Your guess is: " << usrInput << endl;
			cout << "Do you want to start a new game? Please type in [1] if you want to start a new game, or [0], if you want to exit the game." << endl;
			cout << "Your choice: " << endl;
			cin >> newGame;
			if (!cin) throw runtime_error("Your entry is invalid! Only the numbers 0 or 1 are allowed as entry. The application will close now. Please restart the application for a new game.");

			if (newGame) // create a new random number that should be guessed by the player
			{
				winFlag = false; // reset winFlag
				goal = bullsAndCowsNumber(rand());
				cout << "A new random number was created. Let the game begin!" << endl;
				cout << "Please type in your guess  and push the 'Enter' button: " << endl;
			}
			else// abort the game
			{
				cout << "The application will be closed, now." << endl;
				break; // exit the application
			}
		}
		else // The player guesses again.
		{
			cout << "That's not the number I am looking for. Please try again: " << endl;
		}
	}
	keep_window_open();
	return 0;
}
