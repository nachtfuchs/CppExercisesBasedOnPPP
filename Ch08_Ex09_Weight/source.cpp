/* @brief Assignment from chapter 8 exercise 9.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a function that given two vector<double>s price and weight computes
 * a value (an “index”) that is the sum of all price[i]*weight[i]. Make
 * sure to have weight.size()==price.size().
 */

#include "../std_lib_facilities.h"

double calcIdx(const vector<double>& price, const vector<double>& weight)
{
	double idx {0};
	if( price.size() != weight.size()) error("ERROR: The input vectors have different sizes." );
	// calculate the sum of the multiplied entries in the input vectors.
	for( int i = 0; i < price.size(); i++) idx += price[ i ] * weight[ i ];
	return idx;
}

int main()
{
	vector<double> price 	{11, 1};
	vector<double> weight	{1, 51};

	cout << "The calculated index is: " << calcIdx( price, weight ) << endl;
	keep_window_open();
	return 0;
}
