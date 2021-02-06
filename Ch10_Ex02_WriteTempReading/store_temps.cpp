/* @brief Assignment from chapter 10 exercinStreame 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program that creates a file of data in the form of the temperature
 * Reading type defined in §10.5. For testing, fill the file with at least 50
 * “temperature readings.” Call this program store_temps.cpp and the file it
 * creates raw_temps.txt.
 *
 * LESSONS LEARNED:
 * - It is hard to identify the valid values for temperatures, a terminator sign,
 * and failed input streams. Somehow, I can manage to check only a subset of them.
 */

#include "../std_lib_facilities.h"

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

void skipToInt( istream& inStream )
{
	if( inStream.fail() )	{
		inStream.clear();
		// Try to catch the invalid characters
		for( char ch; inStream >> ch;) {
			if( isdigit(ch) || ch == '-') {
				inStream.unget();
				return;
			}
		}
	}
	error("No input");
}

int getInt( istream& inStream )
{
	int n {0}; // The read value
	while( true ) {
		if( inStream >> n) return n;
		cout << "Sorry that was not a number." << endl;
		skipToInt( inStream );
	}
}

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

istream& operator>>( istream& inStream, Reading& inRead )
{
	cout << "Please provide the hour as an integer between 0 and 23: " << endl <<
			">";
	int tempHour {-1};	// Initialize with illogical hour
	double tempTemperature {-9999}; // initialize with unrealistic temperature
	inStream >> tempHour;
	if( inStream.fail() ) {
		inStream.clear();
		if( isTerminator( inStream ) ) {
			inStream.clear( ios_base::failbit );
			return inStream;
		}
		else error("ERROR: The provided hour could not be identified.");
	}

	cout << "Please provide the temperature in Fahrenheit (min: " << absoluteZeroF() << " [F])" << endl <<
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

	if( tempHour > -1 && tempTemperature > absoluteZeroF() ) {
		inRead.hour = tempHour;
		inRead.temperature = tempTemperature;
	}
	else error("Please provide an hour that is between [0;23], and a temperature that is above [F]:", absoluteZeroF() );
	return inStream;
}

ostream& operator<<( ostream& oStream, const Reading& inRead )
{
	return oStream << inRead.hour << " " << inRead.temperature;
}

int main()
{
	cout << "This application takes your temperature measurements [Fahrenheit] "
			"and saves them in a file!" << endl;
	vector<Reading> vMeasurement {}; // will contain all the temperature readings
	for( Reading measurement; cin >> measurement; )
	{
		vMeasurement.push_back( measurement );
//		cout << "DEBUG: measurement: " << measurement << endl;
	}
	if( cin.fail() ) cout << "Finished reading temperature reading." << endl;

	// Write out the saved data
	string fName { "raw_temps.txt" };
	ofstream ofs { fName };
	for( Reading x : vMeasurement) ofs << x << endl;

	keep_window_open();
	return 0;
}
