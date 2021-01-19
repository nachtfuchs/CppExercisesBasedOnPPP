/* @brief Assignment from chapter 8 exercise 11.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a function that finds the smallest and the largest element of a vector
 * argument and also computes the mean and the median. Do not use global
 * variables. Either return a struct containing the results or pass them back
 * through reference arguments. Which of the two ways of returning several
 * result values do you prefer and why?
 *
 * NOTE: Technically, "struct" was not defined at this point of the book. So
 * it might make sense to read chapter 9 and get to know "struct", before
 * working on this assignment with the struct-approach.
 *
 * LESSONS LEARNED:
 * - the keyword "this" will make life much easier when dealing with classes in the future
 * - it depends on the context whether the functional- or class-approach should
 * 	 be used. In a small application, a functional approach is faster and
 * 	 easier to read. In a big application, it makes sense to structure code
 * 	 with classes. It will help to focus on the major ideas.
 */

#include "../std_lib_facilities.h"

void getVectorAttributesRef( const vector<double>& inVec, double& max, double& min, double& mean, double& median )
{
	vector<double> v = inVec;
	/* @brief Find the maximum value of an input vector.
	 * */
	if( inVec.size() > 0 ) // make sure that vector is not empty.
	{
		sort(v.begin(), v.end());
	}
	else error("ERROR <getVectorAttributesRef>. The input vector is empty.");

	max = v[ v.size() - 1 ]; // the largest element is at the end of the vector.

	min = v[ 0 ]; // the smallest element is at the beginning of the vector.

	mean = 0;
	for (double el : inVec) mean += el; // calculate the sum over all values

	median = v[ inVec.size() / 2];
}

// Create the necessary struct with its required members
struct VectorAttribute
{
	double max {0};
	double min {0};
	double mean {0};
	double median {0};

	// Use a copy of the input vector. This copy will be used for all calculations
	// of the struct attributes. This will help to call the struct easier, and
	// also its functions.
	vector<double> inVecSorted;
	VectorAttribute( const vector<double>& inVec );

	void calcMax();
	void calcMin();
	void calcMean();
	void calcMedian();
};

// @brief Use the constructor to make sure that input vector is valid
VectorAttribute::VectorAttribute( const vector<double>& inVec )
{
	// make sure that vector is not empty.
	if( inVec.size() == 0 ) error("ERROR <VectorAttribute>. The input vector is empty.");
	inVecSorted = inVec; // make it available for the public interface
	sort( inVecSorted.begin(), inVecSorted.end() );
}

/* @brief Find the maximum value of an input vector.
*/
void VectorAttribute::calcMax()
{
	max = inVecSorted[ inVecSorted.size() - 1 ]; // the largest element is at the end of the vector.
}

/* @brief Find the minimum value of an input vector.
*/
void VectorAttribute::calcMin()
{
	min = inVecSorted[ 0 ]; // the smallest element is at the beginning of the vector.
}

/* @brief Find the mean value of an input vector.
*/
void VectorAttribute::calcMean()
{
	mean = 0; // In case function will be called more than once.
	for ( double x : inVecSorted) mean += x;
}

/* @brief Find the median value of an input vector.
*/
void VectorAttribute::calcMedian()
{
	median = inVecSorted[ inVecSorted.size() / 2 ]; // the middle element is the median of the vector.
}

int main()
{
	vector<double> v {3, 0, 6, 7.9, -1, 2.5, -11};
	double max {0};
	double min {0};
	double mean {0};
	double median {0};

	getVectorAttributesRef(v, max, min, mean, median);
	cout << "Vector elements using a regular function:" << endl;
	cout << "Largest element in vector v: " << max << endl;
	cout << "Min element in vector v: " 	<< min << endl;
	cout << "Mean element in vector v: " 	<< mean << endl;
	cout << "Median element in vector v: " 	<< median << endl;

	// Now let's use a struct
	VectorAttribute myAttributeStruct { v };
	myAttributeStruct.calcMax();
	myAttributeStruct.calcMin();
	myAttributeStruct.calcMean();
	myAttributeStruct.calcMedian();
	cout << "Vector elements using a STRUCT:" << endl;
	cout << "Largest element in vector v: " << myAttributeStruct.max << endl;
	cout << "Min element in vector v: " 	<< myAttributeStruct.min << endl;
	cout << "Mean element in vector v: " 	<< myAttributeStruct.mean << endl;
	cout << "Median element in vector v: " 	<< myAttributeStruct.median << endl;

	keep_window_open();
	return 0;
}
