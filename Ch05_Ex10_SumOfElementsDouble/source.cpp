/* @brief Assignment from chapter 5 exercise 10.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Modify the program from exercise 8 to use double instead of int. Also,
 * make a vector of doubles containing the N–1 differences between
 * adjacent values and write out that vector of differences.
 *
 * Assignment form exercise 8:
 * Write a program that reads and stores a series of integers and
 * then computes the sum of the first N integers. First ask for N,
 * then read the values
 * into a vector, then calculate the sum of the first N values.
 * For example:
 * “Please enter the number of values you want to sum:”
 * 3
 * “Please enter some integers (press '|' to stop):”
 * 12 23 13 24 15 |
 * “The sum of the first 3 numbers ( 12 23 13 ) is 48.”
 * Handle all inputs. For example, make sure to give an error message if the
 * user asks for a sum of more numbers than there are in the vector.
 */

#include "../std_lib_facilities.h"

void printAdjacentVal(vector<double> inVec, int n)
{
	/* @brief The function will print the adjacent values of the first n input values in the input vector.
	 *
	 * @input inVec Input vector
	 * @input n The number of n values that should be considered for adjacent values
	 * */
	if (n == 1)	cout << "There are not adjacent values, because only one element is considered for the sum of values." << endl;
	else
	{
		vector<double> diffValues;
		for (int i = 0; i < n-1; i++) diffValues.push_back( inVec[i+1] - inVec[i] );
		cout << "The difference between two adjacent values is: " << endl;
		for (int i = 0; i < n-1; i++) cout << diffValues[i] << "  ";
		cout << endl;
	}
}

int main()
{
	cout << "This application calculates the sum of elements for N user inputs." << endl;
	cout << "The user is allowed to define N." << endl;
	cout << "The user provides the elements." << endl;
	cout << "Please enter the number of values you want to sum:" << endl;
	int n;
	cin >> n; // n elements are taken into the sum
	if (!cin) throw runtime_error("ERROR: Only integers are allowed as N.");
	cout << "Please enter your values that have to be summed up. " << endl;
	cout << "To stop your entries, please type '|' followed by the enter button: " << endl;

	double userIn {};
	vector<double> values {}; // defined by the application user
	double sum {0}; // will contain the sum of n elements

	while(cin >> userIn)
	{
		values.push_back(userIn);
	}
	// make use that the user will enter '|' to stop its entries. This will result in a "false" in cin
	if (!cin)
	{
		if ( n > values.size() ) throw runtime_error("ERROR: There are less provided elements than N elements that should be taken into the sum.");
		for (int i=0; i < n; i++)
		{
			sum += values[i];
		}
//		checkIntLimits(sum);
		cout << "The sum for the first " << n << " numbers are: " << sum << endl;
	}
	printAdjacentVal(values, n);
	keep_window_open();
	return 0;
}
