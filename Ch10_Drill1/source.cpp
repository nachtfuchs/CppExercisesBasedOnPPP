/* @brief Assignment from chapter 10 drill 1.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * 1. Start a program to work with points, discussed in §10.4. Begin
 * by defining the data type Point that has two coordinate members x and y.
 *
 * 2. Using the code and discussion in §10.4, prompt the user to input seven
 * (x,y) pairs. As the data is entered, store it in a vector of Points called
 * original_points
 *
 * 3. Print the data in original_points to see what it looks like.
 *
 * 4. Open an ofstream and output each point to a file named mydata.txt. On
 * Windows, we suggest the .txt suffix to make it easier to look at the data
 * with an ordinary text editor (such as WordPad).
 *
 * 5.  Close the ofstream and then open an ifstream for mydata.txt. Read the
 * data from mydata.txt and store it in a new vector called processed_points.
 *
 * LESSONS LEARNED:
 * - overloading the operators "istream& operator>>" and "ostream& operator<<"
 *   works for "cout" and for file-streams!
 */

#include "../std_lib_facilities.h"

struct Points {
	int x; // x-coordinate
	int y; // y-coordinate
};

/* @brief Provide a convenient input for the class Points.
 * 		First the user needs to write the x-coordinate, followed by a space,
 * 		and the y-coordinate
 * */
istream& operator>>( istream& is, Points& inPoint)
{
	return is >> inPoint.x >> inPoint.y;
}

/* @brief Provide a convenient output for the class Points.
 * */
ostream& operator<<( ostream& os, const Points& inPoint)
{
	return os << "x: " << inPoint.x << ", y: " << inPoint.y << ';';
}

bool operator==( const Points& pA, const Points& pB)
{
	return pA.x == pB.x && pA.y == pB.y;
}

bool operator!=( const Points& pA, const Points& pB)
{
	return !(pA == pB);
}

int main()
{
	vector<Points> original_points {};
	int maxNumPoints {7}; // maximum number of points to store

	// Get user points data
	cout << "Please enter points by writing the x-coordinate, followed by a " <<
			"space, then followed by a y-coordinate." << endl;
	for(int i = 0; i < maxNumPoints; i++) {
		Points temp {};
		cout << '>';
		cin >> temp;
		original_points.push_back( temp );
	}

	// Write data to file
	string fName { "myData.txt" }; // The target file where data is written to.
	ofstream ofs {fName};
	if( !ofs ) throw("ERROR: Could not open file to write: ", fName);
	for( Points p : original_points) ofs << p.x << ' ' << p.y << endl;
	ofs.close();

	// get data from file
	ifstream ifs { fName };
	vector<Points> processed_points {};
	if( !ifs ) error("ERROR: Could not open file to read: ", fName);
	for( Points p; ifs >> p; ) processed_points.push_back( p );

	// Print the saved points:
	cout << "Original points:" << endl;
	for( Points p : original_points) cout << p << endl;
	cout << "Processed points:" << endl;
	for( Points p : processed_points) cout << p << endl;

	// compare the points:
	if( original_points.size() != processed_points.size() ) cout << "The vectors of points have different lengths." << endl;
	for( int idx = 0; idx < original_points.size(); idx++ ) {
		if( original_points[idx] != processed_points[idx]) cout << "Elements are different: " << original_points[idx] << " != " << processed_points[idx] << endl;
	}
	keep_window_open();
	return 0;
}


