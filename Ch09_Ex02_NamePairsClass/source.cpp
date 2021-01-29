/* @brief Assignment from chapter 9 exercise 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Design and implement a Name_pairs class holding (name,age) pairs where
 * name is a string and age is a double. Represent that as a vector<string>
 * (called name) and a vector<double> (called age) member. Provide an input
 * operation read_names() that reads a series of names. Provide a read_ages()
 * operation that prompts the user for an age for each name. Provide a print()
 * operation that prints out the (name[i],age[i]) pairs (one per line) in the
 * order determined by the name vector. Provide a sort() operation that sorts
 * the name vector in alphabetical order and reorganizes the age vector to
 * match. Implement all “operations” as member functions. Test the class (of
 * course: test early and often).
 *
 * LESSONS LEARNED:
 * - The "read-user"-methods can be a good point to make sure that objects
 *   are "valid". This can be used to reduce the validity checks
 *
 */

#include "../std_lib_facilities.h"

class Name_pairs
{
	public:
		// Introduce read user-input methods.
		void read_names( void );
		void read_ages( void );

		// read-only-methods
		void print() const;

		// manipulation of the objects
		void sort( void );
	private:
		vector<string>	name {}; // initialized with empty vector.
		vector<int>		age {};
};

// @brief Exercise on using a "global" variable. This can be made easier, most likely.
const string& quit( void )
{
	static const string quit {";"};
	return quit;
}

/* @brief A function that prompts the user to provide names that will
 * 		be saved in the objects name-vector.
*/
void Name_pairs::read_names( void )
{
	cout << "Please type in a series of names, each followed by an <enter>." << endl;
	cout << "If you want to stop entering names, please use the '" << quit() << "' sign." << endl;
	cout << '>';
	string inName {}; // The name entered by the user.
	while ( inName != quit() ) // Might be a bug, because string is compared to char.
	{
		cin >> inName;
		if ( inName != quit() ) name.push_back( inName );
	}
}

/* @brief A function that prompts the user to provide ages that will
 * 		be saved in the objects age-vector.
*/
void Name_pairs::read_ages( void )
{
	cout << "Please type in a series of ages for the respective names, that "<<
			"were entered previously, each followed by an <enter>." << endl;
	cout << "The prompt will be close once you provided the age for all names." << endl;
	cout << '>';
	int inAge{}; // The name entered by the user.
	for ( int idx = 0; idx < name.size(); idx++ )
	{
		cin >> inAge;
		if ( cin ) age.push_back( inAge );
		else cerr << "ERROR <Name_pairs::read_ages> read an invalid input." << endl;
		if ( inAge < 0 )
			cout << "WARNING: The age you provided is less than zero."  << endl;
		// POST-condition: Make sure to enter only as many ages as there are names.
		if ( age.size() == name.size() )
		{
			cout << "INFO: Reached the last name. Thank you for providing the ages." << endl;
		}
	}
}

/* @brief Sort the names ASCIIbetically and their respective ages.
 * */
void Name_pairs::sort()
{
	// Precondition: There should be at least one name and age saved
	if ( name.size() < 1 ) cerr << "ERROR: There are is no name data saved for this object." << endl;
	if ( age.size() < 1) cerr << "ERROR: There are is no age data saved for this object." << endl;
	// PSEUDO: Create copies of the age-name pairs to later match the ages in
	//		the sorted name-vector
	vector<int> ageUnsorted { age };
	vector<string> nameUnsorted { name };

	// make sure to use the right sort-function
	std::sort( name.begin(), name.end() ); // name is now sorted!

	// PSEUDO: Sort the ages according to the names.
	for (int idx = 0; idx < name.size(); idx++)
	{
		for (int unsortedIdx = 0; unsortedIdx < nameUnsorted.size(); unsortedIdx++)
		{
			if ( name[ idx ] == nameUnsorted [ unsortedIdx ])
				age[idx] = ageUnsorted[ unsortedIdx ];
		}
	}
}

/* @brief Print the names that are saved in a Name_pairs-object.
 * */
void Name_pairs::print( void ) const
{
	// Precondition: There should be at least one name saved
	if ( name.size() < 1 ) cout << "WARNING: There are is no name data saved for this object." << endl;
	else if ( age.size() < 1) cout << "WARNING: There are is no age data saved for this object." << endl;
	else
	{
		cout << "The saved names and ages are:" << endl;
		for (int idx = 0; idx < name.size(); idx++)
		{
			cout << name[ idx ] << ", " << age[ idx ] << endl;
		}
	}
}
int main()
{
	Name_pairs myNamePair {};
	myNamePair.read_names();
	myNamePair.read_ages();
	myNamePair.print();

	// Exercise: Try to use "read-only"-method on a
	const Name_pairs unsortedPair { myNamePair };
	myNamePair.sort();
	myNamePair.print();

	unsortedPair.print();
	// Test case for an empty pair
	Name_pairs emptyPair {};
	emptyPair.print();

	// Test case for existing names, but empty ages
	Name_pairs emptyAge {};
	emptyAge.read_names();
	emptyAge.print();
	keep_window_open();
	return 0;
}
