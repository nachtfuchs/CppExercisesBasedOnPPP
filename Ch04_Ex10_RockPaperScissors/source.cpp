/* @brief Assignment from chapter  exercise .
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that plays the game “Rock, Paper, Scissors.” If you are not
 * familiar with the game do some research (e.g., on the web using Google).
 * Research is a common task for programmers. Use a switch-statement to
 * solve this exercise. Also, the machine should give random answers (i.e.,
 * select the next rock, paper, or scissors randomly). Real randomness is too
 * hard to provide just now, so just build a vector with a sequence of values
 * to be used as “the next value.” If you build the vector into the program,
 * it will always play the same game, so maybe you should let the user enter
 * some values. Try variations to make it less easy for the user to guess
 * which move the machine will make next.
 */

#include "../std_lib_facilities.h"

void generateOutput(char userGuess, vector<string> solution, int cnt)
{
	/* @brief Use the input to try to generate an unexpected answer of the computer
	 *
	 * @input userGuess A char that represent 'r'ock, 'p'aper, or 's'cissors. Other inputs are not allowed.
	 * @input solution A vector that represents the three options 'r'ock, 'p'aper, or 's'cissors. {'rock', 'paper', 'scissors'}
	 * @input cnt A counter.
	 * */
	int mod {solution.size()}; // '-1', because index starts at 0
	string pcGuess {""};
	switch (userGuess)
	{
		case 'r':
			pcGuess = solution[cnt % mod];
			cout << "The computer guessed: " << pcGuess << "!" << endl;
			if (pcGuess == "rock") cout << "That's a TIE!" << endl;
			else if (pcGuess == "paper") cout << "You LOST this point!" << endl;
			else cout << "You WON this point!" << endl;
			break;
		case 'p':
			pcGuess = solution[(cnt+1) % mod];
			cout << "The computer guessed: " << pcGuess << "!" << endl;
			if (pcGuess == "paper") cout << "That's a TIE!" << endl;
			else if (pcGuess == "scissors") cout << "You LOST this point!" << endl;
			else cout << "You WON this point!" << endl;
			break;
		case 's':
			pcGuess = solution[2 - (cnt % mod)];
			cout << "The computer guessed: " << pcGuess << "!" << endl;
			if (pcGuess == "scissors") cout << "That's a TIE!" << endl;
			else if (pcGuess == "rock") cout << "You LOST this point!" << endl;
			else cout << "You WON this point!" << endl;
			break;
		default:
			cerr << "The input you have entered '" << userGuess <<"' is unknown to me. Please use: 'r', 'p', or 's' as input." << endl;
			break;
	}
}

int main()
{
	cout << "This application plays a guessing game which is called rock, paper, scissors." << endl;
	cout << "Enter one of the three letters (r)ock, (p)aper, (s)cissors, and the application will respond." << endl;
	cout << "You can abort this game by pressing 'CTRL+Z'." << endl;
	cout << "Please enter your input: " << endl;

	char userInput {'0'};
	vector<string> solutionSet = {"rock", "paper", "scissors"};
	int cnt {0};
	while (cin >> userInput)
	{
		generateOutput(userInput, solutionSet, cnt);
		cnt++;
		cout << "Let's start a new round! Please enter your input: " << endl;
	}

	keep_window_open();
	return 0;
}
