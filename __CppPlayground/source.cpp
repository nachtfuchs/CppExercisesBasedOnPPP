/* @brief Cpp playground
 */

#include "../std_lib_facilities.h"

int main()
{
	// WOrk with strings. Access elements of a string
	string myString {"abcd"};
	cout << "myString[0]: " << myString[0] << endl; // This works, because a char is used and given as output to cout.

	vector<char> vectorOfStrings = {};
	vectorOfStrings.push_back( myString[0] );
	keep_window_open();
	return 0;
}
