/* @brief Assignment from chapter 8 exercise 13.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a function that takes a vector<string> argument and returns a
 * vector<int> containing the number of characters in each string. Also
 * find the longest and the shortest string and the lexicographically first and
 * last string. How many separate functions would you use for these tasks?
 * Why?
 *
 * LESSONS LEARNED:
 * - lexicographically is not ASCIIbetically.
 * - I used one function for each task, because it allows to structure the code
 *   and make the functions reusable. Also, it makes sense to cluster logical
 *   units in functions. And I consider each task as a logical unit.
 */

#include "../std_lib_facilities.h"

/* @brief Returns the number of characters in each input vector elemend
 * */
vector<int> numOfChar( const vector<string>& inVec)
{
	// Check precondition
	if ( inVec.size() == 0 ) error("ERROR <numOfChar>: Input argument inVec is empty.");

	vector<int> vNumOfChar; // create an empty vector to make use of "push_back"

	for ( string x : inVec ) vNumOfChar.push_back(  (int) x.length() ); // note the conversion to "int" from length()-type "size_t".

	return vNumOfChar;
}

/* @brief Return the longest string in an input vector of strings.
 * */
int longestEl( const vector<string>& inVec)
{
	int longest {-1};

	// Check precondition
	if ( inVec.size() == 0 ) error("ERROR <longestEl>: Input argument inVec is empty.");

	for ( int idx = 0; idx < inVec.size(); idx++ )
	{
		// The challenge here is that the string.length() function returns the
		// "size_t"-type. With my compiler it cannot compare to an "int", and
		// therefore, the if-condition would always fail. This is why it needs
		// to be casted into an "int".
		if ( (int) inVec[ idx ].length() > longest) longest = (int) inVec[ idx ].length();
	}
	return longest;
}

/* @brief Return the shortest string in an input vector of strings.
 * */
int shortestEl( const vector<string>& inVec)
{
	// Check precondition
	if ( inVec.size() == 0 ) error("ERROR <shortestEl>: Input argument inVec is empty.");

	int nBytes { sizeof( int ) };
	double shortest { pow(2, nBytes / 2 * 8) }; // "/2" to account positive and negative numbers

	for ( int idx = 0; idx < inVec.size(); idx++ )
	{
		if ( inVec[ idx ].length() < shortest) shortest = inVec[ idx ].length();
	}
	return shortest;
}

/* @brief Convert the input string to all lower case letters
 * */
string lowerCase( const string& inString )
{
	// Calculate the difference between the lower case and upper case letters.
	// Then add this difference to every upper case letter to transform
	// the letter to lower case.
	int diff { char {'a'} - char{'A'} }; // in ASCII, 'a' has a larger numerical
										// value than 'A'.
	string lString {""};

	// Go through each character in the string and check if it is a lower case
	// letter.
	for ( char c : inString )
	{
		if ( c < 'a') // Then it is an upper case letter. Alternatively,
				// "islower( char c )" could be used, but it was not yet
				// introduced in the book.
			lString += char( c + diff );
		else lString += c;
	}
//	cout << "DEBUG lString: " << lString << endl;
	return lString;
}
/* @brief Return the lexicographically first string in an input vector of strings.
 * */
string lexiFirst( const vector<string>& inVec)
{
	// Check precondition
	if ( inVec.size() == 0 ) error("ERROR <lexiFirst>: Input argument inVec is empty.");

	string first { "zz" }; // assuming natural words, there is can be no word after zz

	// The challenge is to transform "asciibetical" to "lexicographical"
	// interpretation of words. In ASCII, capital letters have a smaller
	// numerical representation and will be ordered prior to lower case
	// letters. This means that "Zorro" will be prior to "apple", although
	// in a lexicographical order it does not make sense. So all upper case
	// letter in the input vector need to be transformed to lower case.
	for( string x : inVec)
	{
		if ( lowerCase( x ) < first ) first = x;
	}

	return first;
}

/* @brief Return the lexicographically last string in an input vector of strings.
 * */
string lexiLast( const vector<string>& inVec)
{
	// Check precondition
	if ( inVec.size() == 0 ) error("ERROR <lexiLast>: Input argument inVec is empty.");

	string last {"aa"}; // assuming natural words, there is can be no word prior to aa
	for( string x : inVec)
	{
		if ( lowerCase( x ) > last ) last = x;
	}
	return last;
}

int main()
{
	vector<string> v {"zero", "alpha", "Tim", "boing", "Zorro" };
	cout << "Number of characters in each vector element:" << endl;
	for ( int x : numOfChar( v ) ) cout << x << endl;
	cout << "Longest element has the following number of characters: " 	<< longestEl( v ) << endl;
	cout << "shortest element has the following number of characters: " << shortestEl( v ) << endl;
	cout << "The lexicographically first element is: " 	<< lexiFirst( v ) << endl;
	cout << "The lexicographically last element is: " 	<< lexiLast( v ) << endl;
	keep_window_open();
	return 0;
}
