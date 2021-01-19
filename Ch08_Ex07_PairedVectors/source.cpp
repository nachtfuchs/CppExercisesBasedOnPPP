/* @brief Assignment from chapter 8 exercise 7.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 *  Read five names into a vector<string> name, then prompt the user for
 *  the ages of the people named and store the ages in a vector<double> age.
 *  Then print out the five (name[i],age[i]) pairs. Sort the names (sort(name
 *  .begin(),name.end())) and print out the (name[i],age[i]) pairs. The tricky
 *  part here is to get the age vector in the correct order to match the sorted
 *  name vector. Hint: Before sorting name, take a copy and use that to
 *  make a copy of age in the right order after sorting name. Then, do that
 *  exercise again but allowing an arbitrary number of names.
 */

#include "../std_lib_facilities.h"


/* @brief The "unsorted" inputs are pairs of (name, age). The target is to
 * 		return a vector which is aligned with the sorted Name
 * */
vector<double> assignAgeToName( const vector<string>& sortedName, const vector<string>& unsortedName, const vector<double>& unsortedAge)
{
	vector<double> sortedAge( sortedName.size() );

	for( int idx = 0; idx < sortedName.size(); idx++)
	{
		for( int unsortedIdx = 0; unsortedIdx < unsortedName.size(); unsortedIdx++)
		{
			if( unsortedName[ unsortedIdx ] == sortedName[ idx ] ) sortedAge[ idx ] = unsortedAge[ unsortedIdx ];
		}
	}
	return sortedAge;
}

int main()
{
	int nNames {0};	// The number of names that should be recorded.
	char prompt {'>'};

	cout << "This application is capable to save (name, age) pairs and return " << endl <<
			"them in alphabetical order. You have to type in the names first. " << endl <<
			"After each name, please use the <enter>-button. Then, please type " << endl <<
			"the age of the respective names." << endl <<
			"Please start with the NUMBER of names you want to record: " << endl <<
			prompt;

	cin >> nNames;
	vector<string> name( nNames );
	vector<double> age( nNames );
	cout << "Please type a name to save it: " << endl;
//	cout << "DEBUG nNames: " << nNames << endl;
	for( int i = 0; i < nNames; i++)
	{
		cout << prompt;
		cin >> name[ i ] ;
	}

	cout << "You have entered " << nNames << " names. Now, please type " <<
			"in their respective ages: " << endl;
	for( int i = 0; i < nNames; i++)
	{
		cout << prompt;
		cin >> age[ i ] ;
	}

	cout << "You have entered " << nNames << " ages. The recorded data " <<
			"is as follows: " << endl;
	for (int i = 0; i < nNames; i++)
	{
		cout << name[ i ] << ": " << age[ i ] << endl;
	}

	cout << "Let me sort the names alphabetically. The result is as follows:" << endl;
	vector<string> nameSorted	= name;
	vector<double> ageSorted	= age;

	sort( nameSorted.begin(), nameSorted.end() );
	ageSorted = assignAgeToName( nameSorted, name, age);
	for (int i = 0; i < nNames; i++)
	{
		cout << nameSorted[ i ] << ": " << ageSorted[ i ] << endl;
	}
	keep_window_open();
	return 0;
}
