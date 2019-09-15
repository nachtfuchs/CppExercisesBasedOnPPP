/* @brief
 * Programming Principle and Practice using C++ p. 116
 * Implement square() without using the multiplication operator; that is, do the
x*x by repeated addition (start a variable result at 0 and add x to it x times).
Then run some version of “the first program” using that square().
 */

#include "../std_lib_facilities.h"

double mySquare(int inVar)
{
	/*
	 * @Brief Calculates the square number of the input value using a loop approach. WOrks only with integer values
	 */
	double res {0};
	for (int i = 0; i < inVar; i++)
	{
		res += inVar;
	}
	return res;
}

int main()
{
	double input1 {};
	cout << "Please type in a number and its square number will be calculated!" << endl;

	while(cin >> input1)
	{
		cout << "The squared number of " << input1 << " is: " << mySquare(input1) << endl;
		cout << "New try. Please type in a number and its square number will be calculated!" << endl;
	}
	keep_window_open();
	return 0;
}
