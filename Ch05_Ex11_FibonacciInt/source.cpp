/* @brief Assignment from chapter 5 exercise 11.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that writes out the first so many values of the Fibonacci
 * series, that is, the series that starts with 1 1 2 3 5 8 13 21 34. The next
 * number of the series is the sum of the two previous ones. Find the largest
 * Fibonacci number that fits in an int.
 */

#include "../std_lib_facilities.h"

vector<double> getIntLimits()
{
	/* @brief Determine the lowest and largest value that an int can hold.
	 *
	 * 	@output minMax A vector with two values. Element 0 is the min value, and element 1
	 * 					is the max value.
	 * */
	int nBytes {sizeof(int)}; // the function sizeof() determines number of bytes in a particular data type. Here it is "int"
	double threshold {2};
	for (int i = 1; i < nBytes*8/2; i++) threshold *= 2;
	double min {-threshold};
	double max {threshold -1 }; // '-1', because "zero" also has to be regarded
	vector<double> minMax {min, max};
	cout << "DEBUG - The largest number that can fit in an int on this machine: " << max << endl;
	return minMax;
}

void calcFibo(int N, double max)
{
	/*@brief Calculate the first N fibonacci numbers.
	 *
	 * @input N The amount of fibonacci numbers that should be calculated.
	 * @input max The maximum number that is considered for the calculation.
	 * @output res A vector that holds the first N fibonacci numbers.*/
	vector<double> res{};
	double previous{0}, current{1}; // the provided definition values are crucial for this function to work correctly!
	if (N < 1) cout << "ERROR: You have to enter at least a number larger than 0." << endl;
	else
	{
		// This is the default case, where Fiboncacci numbers are calculated
		for (int i = 0; i < N; i++)
		{
//			cout << "DEBUG - i = " << i << endl;
			res.push_back(current);
			current += previous;
//			cout << "DEBUG - current = " << current << endl;
			previous = res[i]; // important: previous is NOT "current"
			if ( (current > max) && (i != N-1) )
			{
				cout << "The largest Fibonacci number that can be stored in an int on this machine is: " << previous << endl;
				cout << "This means, that " << i + 1 << " Fibonacci numbers can be calculated with int." << endl;
				cout << "This also means, that your requested " << N << " Fibonacci numbers cannot be calculated with this application." << endl;
				N = i + 1; // rewrite the amount of fibonacci numbers that are being displayed.
				break; // exit the for-loop
			}
		}
		cout << "The first " << N << " Fibonacci numbers are: " << endl;
		for (double x : res) cout << x << "   ";
		cout << endl;
	}
}

int main()
{
	vector<double> fibo;
	int N; // the amount of fibonacci numbers that should be calculated.
	vector<double> intLimits = getIntLimits();
	double max = intLimits[1]; // the maximum number that fits in an integer
	cout << "This application determines the first N Fibonacci numbers depending on the user input for N." << endl;
	cout << "Please enter N: ";
	cin >> N;
	calcFibo(N, max);

	keep_window_open();
	return 0;
}
