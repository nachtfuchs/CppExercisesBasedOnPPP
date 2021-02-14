/* @brief Assignment from chapter 10 exercinStreame 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program that reads the data from raw_temps.txt created in exercise 2
 *  into a vector and then calculates the mean and median temperatures in
 * your data set. Call this program temp_stats.cpp.
 *
 * LESSONS LEARNED:
 * - A very good example of how istream are treated identically for reading from
 *   user input (std::cin) and reading from a file (std::ifstream).
 *
 * - A good example on how functions "blabber". The last temperature reading contains
 *   a request for an entry, but then exits the application by itself.
 */

#include "../std_lib_facilities.h"

/* @brief The default terminator in this application is saved here.
 * 		Target: Exercise to use "global variables" as functions.
 * */
const char& defaultTerminator( void )
{
	static const char term {';'};
	return term;
}

/* @brief The absolute zero temperature in Fahrenheit
 * */
const double& absoluteZeroF( void)
{
	static const double absoluteZero { -459.67 };
	return absoluteZero;
}

struct Reading {	// A temperature reading
	int hour {};			// hour after midnight [0; 23]
	double temperature {};	// in Fahrenheit
};

/* @brief Returns true if an input character is the defaultTerminator()
 * */
bool isTerminator( istream& inStream )
{
	char ch {' '};
	inStream >> ch;
	if( ch != defaultTerminator() ){
		inStream.unget();
		inStream.clear( ios_base::failbit );
		return false;
	}
	else if ( ch == defaultTerminator() )
	{
		inStream.unget(); // so that the caller can use the info about identified terminator
		return true;
	}
	error("Bad terminator analysis.");
}

/* @brief Facilitates to get temperature readings. Contains a basic range check.
 * */
istream& operator>>( istream& inStream, Reading& inRead )
{
	cout << "Please provide the hour as an integer between 0 and 23: " << endl <<
			">";
	int tempHour {-1};	// Initialize with illogical hour
	double tempTemperature {-9999}; // initialize with unrealistic temperature
	inStream >> tempHour;
	if( inStream.eof() ) return inStream;
	if( inStream.fail() ) {
		inStream.clear();
		if( isTerminator( inStream ) ) {
			inStream.clear( ios_base::failbit );
			return inStream;
		}
		else error("ERROR: The provided hour could not be identified.");
	}

	cout << "Please provide the temperature in Fahrenheit (min: " << absoluteZeroF() << " [°F])" << endl <<
			">";
	inStream >> tempTemperature;
	if( inStream.fail() ) {
		inStream.clear();
		if( isTerminator( inStream ) )
		{
			inStream.clear( ios_base::failbit );
			return inStream;
		}
		else error("ERROR: The provided temperature could not be identified.");
	}

	// Precondition: Values must "make sense" before storing them.
	if( tempHour > -1 && tempTemperature > absoluteZeroF() ) {
		inRead.hour = tempHour;
		inRead.temperature = tempTemperature;
	}
	else error("Please provide an hour that is between [0;23], and a temperature that is above [°F]:", absoluteZeroF() );
	return inStream;
}

ostream& operator<<( ostream& oStream, const Reading& inRead )
{
	return oStream << inRead.hour << " " << inRead.temperature;
}

int main()
{
	cout << "This application retrieves your temperature measurements [° Fahrenheit] "
			"from a file! Then, it calculates the mean and median value." << endl;
	vector<Reading> vMeasurement {}; // will contain all the temperature readings
	string fName { "raw_temps.txt" }; // data source
	ifstream ifs { fName };
	for( Reading measurement; ifs >> measurement; )
	{
		if( ifs.eof() ) break;
		vMeasurement.push_back( measurement );
		cout << "DEBUG: measurement: " << measurement << endl;
	}
	if( ifs.eof() ) cout << "Finished reading temperature measurements." << endl;

	// calculate the median and mean temperatures
	// Note: This can be interpreted differently, like "mean temperature per day".
	// Here, the interpretation for the whole data set is used.
	// Step 1: Store the temperatures.
	vector<double> vTemp; // vector of all temperatures from the reading
	for( Reading x : vMeasurement ) vTemp.push_back( x.temperature );
	// Step 2: Calculate the mean temperature
	double meanT { 0 }; // Mean temperature
	for( double x : vTemp) meanT += x;
	meanT = meanT / vTemp.size();
	cout << "The mean temperature is: " << meanT << " [°F]" << endl;
	// median
	double medianT { absoluteZeroF() }; // Median temperature
	sort( vTemp );
	medianT = vTemp[ vTemp.size() / 2 ];
	cout << "The median temperature is: " << medianT << " [°F]" << endl;
	keep_window_open();
	return 0;
}
