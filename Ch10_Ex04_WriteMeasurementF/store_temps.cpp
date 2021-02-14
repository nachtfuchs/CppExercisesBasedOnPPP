 /* @brief Assignment from chapter 10 exercinStreame 2.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Modify the store_temps.cpp program from exercise 2 to include a
 * temperature suffix c for Celsius or f for Fahrenheit temperatures.
 * Then modify the temp_stats.cpp program to test each temperature,
 * converting the Celsius readings to Fahrenheit before putting them
 * into the vector.
 *
 * LESSONS LEARNED:
 */

#include "../std_lib_facilities.h"

/* @brief The default terminator. Exercise to use functions as global
 * 		variables.
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
	char unit {};			// Unit. Either 'c' for Celsius or 'f' for Fahrenheit.
};

/* @brief The Celsius identifier
 * */
const char& defaultCelsiusId( void )
{
	static const char defaultId {'c'};
	return defaultId;
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

/* @brief Get the temperature unit [°F] or [°C] by the character 'f' or 'c',
 * 	respectively.
 * */
char getUnit(istream& inStream)
{
	char unit {'f'};
	inStream >> unit;
	if( inStream.fail() ) {
		error("There was an issue reading the temperature unit.");
	}
	if( unit != defaultCelsiusId() && unit != 'f') {
		error("The identified unit is illegal. Please use either 'c' or 'f' as a suffix for Celsius or Fahrenheit.");
	}
	return unit;
}

/* @brief Convert Celsius to Fahrenheit.
 * */
double celsiusToFahrenheit( double inCelsius )
{
	return (inCelsius * 9 / 5) + 32;
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
			inStream.clear( ios_base::failbit ); // "failbit" used as an exit criteria for the caller
												// to highlight that reading is finished.
			return inStream;
		}
		else error("ERROR: The provided hour could not be identified.");
	}

	cout << "Please provide a temperature. Use a suffix 'c' for Celsius or "
			"'f' for Fahrenheit (min: " << absoluteZeroF() << " [F])" << endl <<
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
	char tempUnit{' '}; // temperature unit
	tempUnit = getUnit( inStream );

	if( tempHour > -1 && tempTemperature > absoluteZeroF() ) {
		if( tempUnit == defaultCelsiusId() ) {
			if( celsiusToFahrenheit( tempTemperature ) < absoluteZeroF() ) error("The provided temperature is below absolute zero.");
		}
		inRead.hour = tempHour;
		inRead.temperature = tempTemperature;
		inRead.unit = tempUnit;
	}
	else error("Please provide an hour that is between [0;23], and a temperature that is above [F]:", absoluteZeroF() );
	return inStream;
}

ostream& operator<<( ostream& oStream, const Reading& inRead )
{
	return oStream << inRead.hour << " " << inRead.temperature << inRead.unit;
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
	if( cin.fail() ) {
		cin.clear();
		cout << "Finished reading temperature measurements." << endl;
	}
	// Write out the saved data
	string fName { "raw_temps.txt" };
	ofstream ofs { fName };
	for( Reading x : vMeasurement) ofs << x << endl;

	keep_window_open();
	return 0;
}
