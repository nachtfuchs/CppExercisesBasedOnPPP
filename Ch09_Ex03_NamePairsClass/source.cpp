/* @brief Assignment from chapter 9 exercise 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 *  Replace Name_pair::print() with a (global) operator << and define ==
 *  and != for Name_pairs. (see exercise 2)
 *
 * LESSONS LEARNED:
 * - The operator overloading requires additional methods to get access to the
 *   private members.
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

		//getter methods
		vector<string> write_names( void ) const;
		vector<int> write_ages( void ) const;

	private:
		vector<string>	name {}; // initialized with empty vector.
		vector<int>		age {};
};

/* @brief Check if the input pairs have identical entries. Consider
 * 		the order of the pairs, too.
 * */
bool operator==(const Name_pairs& pairA, const Name_pairs& pairB)
{
	bool result {false};
	vector<string> nameA { pairA.write_names() };
	vector<string> nameB { pairB.write_names() };

	vector<int> ageA { pairA.write_ages() };
	vector<int> ageB { pairB.write_ages() };

	// Precondition: Both should be of same size:
	if ( nameA.size() != nameB.size() ) return false;
	if ( ageA.size() != ageB.size() ) return false;

	// compare each name and age in both input arguments
	for( int idx = 0; idx < nameA.size(); idx++)
	{
		if( nameA[ idx ] != nameB[ idx ]) return false;
		if( ageA[ idx ] != ageB[ idx ]) return false;
	}
	return true; // all checks failed, then the input pairs must be equal
}

/* @brief See overloaded "==".
 * */
bool operator!=(const Name_pairs& pairA, const Name_pairs& pairB)
{
	return !( pairA == pairB );
}

/* @brief Make the name-vector available.
 * */
vector<string> Name_pairs::write_names( void ) const
{
	return name;
}

/* @brief Make the age-vector available.
 * */
vector<int> Name_pairs::write_ages( void ) const
{
	return age;
}

/* @brief Display all the entries of the input Name_pairs variable.
 * */
ostream& operator<<(ostream& os, const Name_pairs& inPair)
{
	// Create a copy of the inPair-object to work on it.
	vector<string> objName { inPair.write_names() };
	vector<int> objAge { inPair.write_ages() };
	// Precondition: There should be at least one name saved
	if ( objName.size() < 1 ) os << "WARNING: There are is no name data saved for this object." << endl;
	else if ( objAge.size() < 1) os << "WARNING: There are is no age data saved for this object." << endl;
	else
	{
		for (int idx = 0; idx < objName.size(); idx++)
		{
			os << objName[ idx ] << ", " << objAge[ idx ] << endl;
		}
	}
	return os;
}

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
	cout << "Using the ostream-operator: " << myNamePair << endl;
	// Exercise: Try to use "read-only"-method on a
	const Name_pairs unsortedPair { myNamePair };
	const Name_pairs identicalPair { myNamePair };
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

	cout << "Testing the '=='-operator overload. (unsortedPair == identicalPair): " << (unsortedPair == identicalPair) << endl;
	cout << "Testing the '!='-operator overload. (unsortedPair != identicalPair): " << (unsortedPair != identicalPair) << endl;
	cout << "Testing the '=='-operator overload. (myNamePair == identicalPair): " << (myNamePair == identicalPair) << endl;
	cout << "Testing the '!='-operator overload. (myNamePair != identicalPair): " << (myNamePair != identicalPair) << endl;

	keep_window_open();
	return 0;
}
