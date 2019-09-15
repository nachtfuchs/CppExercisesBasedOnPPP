/* @brief Assignment from chapter 6 exercise 4.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Define a class Name_value that holds a string and a value. Rework
 * exercise 19 in Chapter 4 to use a vector<Name_value> instead of two vectors.
 */

#include "../std_lib_facilities.h"

class Name_value
{
public:
	string name{""};
	int score{};
};

bool checkUniqueName(string name, vector<Name_value> players)
{
	/*@brief Check if name is part of input vector*/
	bool result {true}; // 'true' means that name  is unique
	for (Name_value player : players)
	{
		if ( player.name == name) result = false;
	}
	return result;
}

int main()
{
	string name {""};	//input variable for a player's name
	double score{};		//input variable for a player's score
	Name_value newPlayer{};	// used to push_back a new player
	vector<Name_value> players{};

	cout << "This application creates a list of name-score pairs that are created by the user." << endl;
	cout << "Please type in a name and its according score." << endl;
	cout << "You can terminate the input by using the name 'NoName'." << endl;
	cout << "Please type in the first name: ";
	while (cin >> name)
	{
		if (!checkUniqueName(name, players)) cerr << endl <<  "The name:" << name << " already exists. Each name should be unique. Please choose a new name: " << endl;
		else if (name == "NoName") break; // termination input
		else
		{
			// the regular case
			cout << "Please type in the according score: ";
			cin >> score;
			newPlayer.name	= name;
			newPlayer.score	= score;
			players.push_back(newPlayer);
			cout << "Please type in the next name: ";
		}
	}

	for (int i = 0; i < players.size(); i++)
	{
		cout << "Name: " << players[i].name << " - score: " << players[i].score << endl;
	}
	keep_window_open();
	return 0;
}
