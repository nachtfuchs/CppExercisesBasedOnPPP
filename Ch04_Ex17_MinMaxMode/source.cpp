/* @brief Assignment from chapter 4 exercise 17 .
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that finds the min, max, and mode of a sequence of
 * strings.
 */

#include "../std_lib_facilities.h"

string getMode(vector<string> input)
{
	/*@brief Get the mode of the input vector
	 *
	 *@input A sequence of strings
	 *
	 *@output The mode of the input sequence, which is the string that
	 * 			appears the most times in the input sequence.
	*/

	int maxCnt {-1}; // The 'highscore' counter
	int currCnt {-1}; // The current counter
	string currMode {""};
	string maxMode{""};
	int len = input.size(); // the number of elements in the input vector

	// Step 0: create an index that shows which entries were already identified.
	vector<int> index(len); // '0' means not identified. '1' means identified.
	// Step 1: Get the first entry and count its appearance in the rest of the vector
	string val {""}; // saves the value that is currently identified
	for (int i = 0; i < len; i++)
	{
		if (index[i] == 0)
		{
			val	= input[i];
			currMode	= val;
			index[i]	= 1; // set the current value as identified
			currCnt	= 1;
			// check if the identified value exists in the next entries
			for (int k = i + 1; k < len; k++)
			{
				if (input[k] == val)
				{
					// reduce run time by "deactivating" the identified values
					currCnt++;
					index[k] = 1;
				}
			}
			if (currCnt > maxCnt)
			{
				maxCnt	= currCnt;	// update the highscore
				maxMode = currMode; // update the mode
			}
		}

	}
	// Step 2: Return the maximum counter.
	return maxMode;
}

int main()
{
	cout << "This application will return the 'mode', min and max of a series of strings." << endl;
	cout << "The mode is the value that appears most times in a sequence." << endl;
	cout << "Please create a sequence of numbers by typing the strings and pressing the enter button." << endl;
	cout << "Your input: " << endl;

	string userInput {""};
	vector<string> values; // stores the user entries
	while (cin >> userInput)
	{
		values.push_back(userInput);
	}
	string mode {""};
	mode = getMode(values);
	sort(values);

	cout << "The mode of the input sequence is: " << mode << endl;
	cout << "The min value of the input sequence is: " << values[0] << endl;
	int len = values.size() - 1;
	cout << "The max value of the input sequence is: " << values[len] << endl;

	keep_window_open();
	return 0;
}

