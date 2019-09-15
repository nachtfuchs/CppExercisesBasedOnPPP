/* @brief Assignment from chapter 4 exercise 21.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Modify the program from exercise 19 so that when you enter an integer,
 * the program will output all the names with that score or score not found.
 *
 * Exercise 19:
 * Write a program where you first enter a set of name-and-value pairs, such
 * as Joe 17 and Barbara 22. For each pair, add the name to a vector called
 * names and the number to a vector called scores (in corresponding positions,
 * so that if names[7]=="Joe" then scores[7]==17). Terminate input
 * with NoName 0. Check that each name is unique and terminate with an
 * error message if a name is entered twice. Write out all the (name,score)
 * pairs, one per line.
 */

#include "../std_lib_facilities.h"

bool checkUniqueName(string name, vector<string> names)
{
	/*@brief Check if name is part of input vector*/
	bool result {true}; // 'true' means that name  is unique
	for (string s : names)
	{
		if ( s == name) result = false;
	}
	return result;
}

void getName(double score, vector<string> names, vector<double> scores)
{
	/*@brief This function tries to find the score in the input scores and return all the corresponding names*/
	bool scoreFound {false}; // flag that is 'true' if a particular string was found
	for (int i = 0; i < scores.size(); i++)
	{
		if ( score == scores[i])
		{
			cout << "The score of " << score << " was found for: " << names[i] << endl;
			scoreFound = true;
		}
	}
	if (scoreFound == false)
		cout << "score not found!" << endl;
}

int main()
{
	string name {""};
	double score{};
	vector<string> names{}; 	// comes in pair with scores
	vector<double> scores{};	// comes in pair with names

	cout << "This application creates a list of name-score pairs that are created by the user." << endl;
	cout << "Please type in a name and its according score." << endl;
	cout << "You can terminate the input by using the name 'NoName'." << endl;
	cout << "Please type in the first name: ";
	while (cin >> name)
	{
		if (!checkUniqueName(name, names)) cerr << endl <<  "The name:" << name << " already exists. Each name should be unique. Please choose a new name: " << endl;
		else if (name == "NoName") break; // termination input
		else
		{
			// the regular case
			names.push_back(name);
			cout << "Please type in the according score: ";
			cin >> score;
			scores.push_back(score);
			cout << "Please type in the next name: ";
		}

	}

	double searchScore {};
	cout << "You can now search for the score you entered and the application will return the corresponding names. Your input:" << endl;
	while (cin >> searchScore)
	{
		getName(searchScore, names, scores);
		cout << "You can search for another score or exit the search by pressing 'Ctrl+Z'. Your Input:" << endl;
	}
	keep_window_open();
	return 0;
}
