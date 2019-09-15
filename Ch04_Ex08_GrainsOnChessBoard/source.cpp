/* @brief Assignment from chapter 4 exercise 8.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * There is an old story that the emperor wanted to thank the inventor of
 * the game of chess and asked the inventor to name his reward. The inventor asked
 * for one grain of rice for the first square, 2 for the second, 4 for
 * the third, and so on, doubling for each of the 64 squares. That may sound
 * modest, but there wasn’t that much rice in the empire! Write a program to
 * calculate how many squares are required to give the inventor at least 1000
 * grains of rice, at least 1,000,000 grains, and at least 1,000,000,000 grains.
 * You’ll need a loop, of course, and probably an int to keep track of which
 * square you are at, an int to keep the number of grains on the current
 * square, and an int to keep track of the grains on all previous squares. We
 * suggest that you write out the value of all your variables for each iteration
 * of the loop so that you can see what’s going on.
 */

#include "../std_lib_facilities.h"

int main()
{
	double grain {0}; // AMount of grain
	double sum {0};	// The summed up amount of grain
	int i {0}; //cnt
	bool milestone_1k {false}; // a flag that shows whether a milestone quantity was reached
	bool milestone_1m {false};
	bool milestone_1b {false};
	for (i = 0; sum < 1000000000; i++)
	{
		if (i == 0)
		{
			grain 	= 1;
			sum		= 1;
		}
		else
		{
			grain *= 2;
			sum += grain;
		}
		// check milestones
		if (sum > 1000 && milestone_1k == false)
		{
			milestone_1k = true;
			cout << "The amount of chess squares for 1000 grains is: " << i + 1 << endl; // '+1', because of the first grain that has the power '0'.
			cout << "The amount of grains on the " << i << "th square is: " << grain << endl;
			cout << "The sum of grains of all the grains so far at chess square " << i +1 << "is: " << sum << endl;
		}
		if (sum > 1000000 && milestone_1m == false)
		{
			milestone_1m = true;
			cout << "The amount of chess squares for 1,000,000 grains is: " << i + 1 << endl; // '+1', because of the first grain that has the power '0'.
			cout << "The amount of grains on the " << i << "th square is: " << grain << endl;
			cout << "The sum of grains of all the grains so far: " << sum << endl;
		}
		if (sum > 1000000000 && milestone_1b == false)
		{
			milestone_1b = true;
			cout << "The amount of chess squares for 1,000,000,000 grains is: " << i + 1 << endl; // '+1', because of the first grain that has the power '0'.
			cout << "The amount of grains on the " << i << "th square is: " << grain << endl;
			cout << "The sum of grains of all the grains so far: " << sum << endl;
		}
	}
	keep_window_open();
	return 0;
}
