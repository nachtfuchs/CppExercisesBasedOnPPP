/* @brief Assignment from chapter 4 exercise 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Read a sequence of double values into a vector. Think of each value as
 * the distance between two cities along a given route. Compute and print
 * the total distance (the sum of all distances). Find and print the smallest
 * and greatest distance between two neighboring cities. Find and print the
 * mean distance between two neighboring cities.
 */

#include "../std_lib_facilities.h"

int main()
{

	cout << "Please enter a sequence of numbers." << endl;
	cout << "Think of the numbers a distances between cities." << endl;
	cout << "In the end, the total distance, the smallest and greatest " << endl;
	cout << "as well as the mean distance will be displayed" << endl;
	cout << "Finish your sequence with 'Ctrl + Z'" << endl;
	cout << "Your entries, please: " << endl;

	vector<double> dist_v {};
	for (double dist; cin >> dist;)
	{
		dist_v.push_back(dist);
	}
	// calculate total distance
	double total {0};
	for (double dist : dist_v)
	{
		total += dist;
	}
	// determine smallest, largest and mean value
	sort(dist_v);
	double min {};
	double max {};
	double mean {};
	min 	= dist_v[0];
	max		= dist_v[ dist_v.size() -1];
	mean 	= total / dist_v.size();
	cout << "Total distance: " << total << endl;
	cout << "Smallest: "<< min << endl;
	cout << "Largest: " << max 	<< endl;
	cout << "Mean: " 	<< mean << endl;

	keep_window_open();
	return 0;
}
