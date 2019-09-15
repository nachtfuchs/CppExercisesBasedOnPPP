/* @brief Assignment from chapter 05 exercise 14.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Read (day-of-the-week,value) pairs from standard input. For example:
 * Tuesday 23 Friday 56 Tuesday –3 Thursday 99
 * Collect all the values for each day of the week in a vector<int>. Write out
 * the values of the seven day-of-the-week vectors. Print out the sum of the
 * values in each vector. Ignore illegal days of the week, such as Funday,
 * but accept common synonyms such as Mon and monday. Write out the
 * number of rejected values
 *
 * NOTE: This means that an average of a weekday is determined. The sum is
 * created over all "Tuesdays" etc. It is NOT the weekly average.
 */
#include "../std_lib_facilities.h"

bool validDayInput(string i_day)
{
	/* @brief Check if the input string can be interpreted as a weekday name.
	 *
	 * @input i_day A valid string for a weekday like monday, Monday, mon, Mon, etc.
	 *
	 * @output valid A flag that signalizes that the input can be interpreted as a valid weekday name.
	 * */
	if (i_day == "Monday" or i_day == "monday" or i_day == "Mon" or i_day == "mon" or i_day == "M" or i_day == "m")
		return true;
	if (i_day == "Tuesday" or i_day == "tuesday" or i_day == "Tue" or i_day == "tue" or i_day == "Tu" or i_day == "tu")
		return true;
	if (i_day == "Wednesday" or i_day == "wednesday" or i_day == "Wed" or i_day == "wed" or i_day == "W" or i_day == "w")
		return true;
	if (i_day == "Thursday" or i_day == "thursday" or i_day == "Thur"  or i_day == "thur"  or i_day == "Thu"  or i_day == "thu" or i_day == "Th"  or i_day == "th")
		return true;
	if (i_day == "Friday" or i_day == "friday" or i_day == "Fri" or i_day == "fri" or i_day == "Fr" or i_day == "fr" or i_day == "F" or i_day == "F")
		return true;
	if (i_day == "Saturday" or i_day == "saturday" or i_day == "Sat" or i_day == "sat" or i_day == "Sa" or i_day == "sa")
		return true;
	if (i_day == "Sunday" or i_day == "sunday" or i_day == "Sun" or i_day == "sun" or i_day == "Su" or i_day == "su")
		return true;
	return false; // all other cases
}

string handleDayInput(string i_day)
{
	/* @brief Convert the input string i_day into a standard weekday name like Monday, Tuesday, etc.
	 *
	 * @input i_day A valid string for a weekday like monday, Monday, mon, Mon, etc.
	 *
	 * @output day A standardized output name like Monday, Tuesday, etc.
	 * */
	if (i_day == "Monday" or i_day == "monday" or i_day == "Mon" or i_day == "mon" or i_day == "M" or i_day == "m")
		return "Monday";
	if (i_day == "Tuesday" or i_day == "tuesday" or i_day == "Tue" or i_day == "tue" or i_day == "Tu" or i_day == "tu")
		return "Tuesday";
	if (i_day == "Wednesday" or i_day == "wednesday" or i_day == "Wed" or i_day == "wed" or i_day == "W" or i_day == "w")
		return "Wednesday";
	if (i_day == "Thursday" or i_day == "thursday" or i_day == "Thur"  or i_day == "thur"  or i_day == "Thu"  or i_day == "thu" or i_day == "Th"  or i_day == "th")
		return "Thursday";
	if (i_day == "Friday" or i_day == "friday" or i_day == "Fri" or i_day == "fri" or i_day == "Fr" or i_day == "fr" or i_day == "F" or i_day == "F")
		return "Friday";
	if (i_day == "Saturday" or i_day == "saturday" or i_day == "Sat" or i_day == "sat" or i_day == "Sa" or i_day == "sa")
		return "Saturday";
	if (i_day == "Sunday" or i_day == "sunday" or i_day == "Sun" or i_day == "sun" or i_day == "Su" or i_day == "su")
		return "Sunday";
}

void printDayInfo(string day, vector<int> dayVal)
{
	/* @brief Print day information which is the day, the individual values in the dayVal input vector
	 * 		and the sum of all day values.
	 *
	 * @input day E.g. "Wednesday"
	 * @input dayVal A vector that contains numeric values. Can be empty.
	 * */
	double sum {0}; // contains a sum
	cout << day << " :" << endl;
	for (int x:dayVal)
	{
		cout << x;
		sum	+= x; //sum up
	}
	cout << endl <<  "Sum of " << day << ": " << sum << endl;
}

int main()
{
	string i_day {"NONE"}; // The user input value for the day of the week.
	string day {"NONE"}; // The converted user input to a weekday string like Monday, Tuesday, Wednesday, etc.
	int i_val {};	// The user input for the value of a day.
	vector<int> monday{}, tuesday{}, wednesday{}, thursday{}, friday{}, saturday{}, sunday{}; // vectors will contain values for the specific day.
	vector<string> invalidDays {}; // contains the invalid days, like "Funday"
	vector<int> invalidVal {}; // The values that come with the invalid days
//	vector<int> newVal{}; // This will save the new values that are a result of the newly entered user input

	cout << "This application saves your daily values in a 'day-value'-pair." << endl;
	cout << "E.g.: Tuesday 23 Friday 56 Tuesday –3 Thursday 99" << endl;
	cout << "Please type in your set of day-value-pairs and finish your set by pushing the enter button." << endl;
	cout << "Remember to use only valid day names or known abbreviations like Mon and monday." << endl;
	cout << "You can abort the entries by pressing 'Enter', and then 'Ctrl+z' on your keyboard." << endl;
	cout << "Please type in in your set of day-value pairs: " << endl;

	cin >> i_day;
	if (!cin) throw runtime_error("The input you have entered is invalid! Please enter only a known weekday (English) or its known abbreviation. Please restart the application.");

	while(cin) // collect all the weekday-value pairs until aborted by wron input
	{
		cin >> i_val;
		if (!cin) throw runtime_error("The input you have entered is invalid! Please enter only a valid integer number. Please restart the application.");

		if (validDayInput(i_day))
		{
			// add the input value to its according vector.
			day = handleDayInput(i_day);
			//		newVal = createPair(i_day, i_val, monday, tuesday, wednesday, thursday, friday, sunday);
			if (day == "Monday")
			{
				monday.push_back(i_val);
			}
			else if (day == "Tuesday")
			{
				tuesday.push_back(i_val);
			}
			else if (day == "Wednesday")
			{
				wednesday.push_back(i_val);
			}
			else if (day == "Thursday")
			{
				thursday.push_back(i_val);
			}
			else if (day == "Friday")
			{
				friday.push_back(i_val);
			}
			else if (day == "Saturday")
			{
				saturday.push_back(i_val);
			}
			else if (day == "Sunday")
			{
				sunday.push_back(i_val);
			}
		}
		else
		{
			invalidDays.push_back(i_day);
			invalidVal.push_back(i_val);
		}
		cin >> i_day; // New run by day input.
	}

	// Write out the saved information:
	cout << "I collected the following information: " << endl;
	printDayInfo("Monday", 		monday);
	printDayInfo("Tuesday", 	tuesday);
	printDayInfo("Wednesday", 	wednesday);
	printDayInfo("Thursday", 	thursday);
	printDayInfo("Friday", 		friday);
	printDayInfo("Saturday",	saturday);
	printDayInfo("Sunday", 		sunday);

	// inform the user about wrong input:
	cout << "I could not identify the following information and discarded it: " << endl;
	for (int i = 0; i < invalidDays.size(); i++)
	{
		try
		{
			// invalidVal could be shorter than invalidDays -> "out_of_range" exception.
			cout << invalidDays[i] << " : " << invalidVal[i] << endl;
		}
		catch (out_of_range)
		{
			cout << "Range error in invalid values." << endl;
		}
	}

	keep_window_open();
	return 0;
}
