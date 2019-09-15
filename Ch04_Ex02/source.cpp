/* @brief Assignment from chapter 4 exercise 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * If we define the median of a sequence as “a number so that exactly as
 * many elements come before it in the sequence as come after it,” fix the
 * program in §4.6.3 so that it always prints out a median. Hint: A median
 * need not be an element of the sequence.
 */

#include "../std_lib_facilities.h"

double medianAsSequence(vector<double> input)
{
	/*@brief Get the median if an input vector according to the definition of
	 * "The median of a sequence is “a number so that exactly as
 	* many elements come before it in the sequence as come after it,”
 	*
 	* NOTE: For an input with even amount of elements, average value of the
 	* two mid elements is used. {1, 2, 5, 9} -> (2+5)/2 */
	int len{};
	double median{};
	len = input.size(); // returns an integer!
	if ( (len % 2) == 0)
	{
		median = (input[len/2] + input[len/2 +1]) / 2; // calculate the median based on above note.
		return median;
	}
	else return input[len/2];
}

int main()
{
	vector<double> temps; // temperatures

	// compute mean temperature:
	double sum = 0;
	cout << "Please enter a sequence of temperature values as decimal numbers. In the end, the average temperature will be displayed. Your numbers, please:" << endl;
	for (double temp; cin>>temp; ) // read into temp
			temps.push_back(temp); // put temp into vector
	for (int x : temps) sum += x;
	cout << "Average temperature: " << sum/temps.size() << '\n';

	// compute median temperature:
	sort(temps); // sort temperatures
	cout << "Median temperature (as sequence): " << medianAsSequence(temps) << '\n';

	keep_window_open();
	return 0;
}
