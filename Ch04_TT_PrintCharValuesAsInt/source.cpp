/* @brief Print char values as int values
 */

#include "../std_lib_facilities.h"

int main()
{

	char chVal = 'a';
	for (int i = 0; i <= 26; ++i)
	{
		cout << "char: " << char(chVal +i) << " \tInt: " << int(chVal + i) << endl;
	}

	keep_window_open();
	return 0;
}
