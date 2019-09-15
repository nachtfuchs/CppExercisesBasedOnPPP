/* @brief Chapter 04 drill from Programming Principle and Practice using C++.
 */

#include "../std_lib_facilities.h"

void compareTwoNumbers(double a, double b)
{
	// @brief compares the two input numbers and displays information
	if (a > b)
	{
		cout << "The smaller value is: " << b << endl;
		cout << "The larger value is: " << a << endl;
	}
	else if (b > a)
	{
		cout << "The smaller value is: " << a << endl;
		cout << "The larger values is: " << b << endl;
	}
	else
	{
		cout << "The numbers are equal" << endl;
	}

	if ( abs(a - b) < 0.01)
	{
		cout << "The numbers are almost equal" << endl;
	}
}

double trackNumberLargest(double input, double oldLargest)
{
	//@ Brief Determine if new input number is larger than all the numbers before
	double newLargest {};
	if (input > oldLargest)
	{
		cout << input << "[m] is the largest number so far," << endl;
		newLargest = input;
	}
	else
	{
		newLargest = oldLargest;
	}
	return newLargest;
}

double trackNumberSmallest(double input, double oldSmallest)
{
	// @ Brief Determine if new input number is smaller than the smallest reference
	double newSmallest {};
	if (input < oldSmallest)
	{
		cout << input << "[m] is the smallest number so far." << endl;
		newSmallest = input;
	}
	else
	{
		newSmallest = oldSmallest;
	}
	return newSmallest;
}

double convertToMeter(double inputA, string unit)
{
	/* @brief Convert input number to a number in [m] using the input unit.
	@input unit Valid units are cm, m, in(ch), ft(foot) */
	double retVal;
	if (unit == "cm")
	{
		retVal = inputA * 0.01;
	}
	else if (unit == "m")
	{
		retVal = inputA;
	}
	else if(unit == "in")
	{
		retVal = inputA * 0.0254;
	}
	else if (unit == "ft")
	{
		retVal = inputA * 12 * 0.0254;
	}
	else
	{
		cerr << "Unknown unit in convertToMeter. Unit: "  << unit << endl;
	}
	return retVal;
}

void checkInputUnit(string inputUnit)
{
	/*@brief check if input is valid*/
	vector<string> validInputs = {"m", "in", "cm", "ft"};
	bool isValid = 0; // '0' means "invalid"
	for (string s : validInputs)
	{
		if(inputUnit == s)	isValid = 1;
	}
	if (isValid) { } else cerr << "The input unit is invalid: " << inputUnit << endl;
}

int main()
{
	/*@brief The goal of this function is to play with numbers and functions as well as
	 	 	 user input*/
	double inputA {};
	double inputB {};
	double inputMeterA {}; // The input in [m]
	double inputMeterB {};
	double largest { -pow(2, 4*8-1) };
	double smallest { pow(2, 4*8-1) };
	int cnt {0};
	double sumOfValues {0};
	string unitA{};
	string unitB{};
	vector<double> values;

	cout << "Please enter your first number with a unit behind it and press enter." << endl;
	cout << "Example: 12 cm. Your input: " << endl;

	while (cin >> inputA)
	{
		/*Todo: This is buggy when an unequal amount of numbers is entered.*/
		cin >> unitA;
		checkInputUnit(unitA);
		inputMeterA= convertToMeter(inputA, unitA);
		sumOfValues	+= inputMeterA;
		cnt	+= 1;
		values.push_back(inputMeterA);
		largest		= trackNumberLargest(inputMeterA, largest);
		smallest 	= trackNumberSmallest(inputMeterA, smallest);
		cout << "Please enter your second number and unit, and press enter: " << endl;
		cin >> inputB >> unitB;
		checkInputUnit(unitB);
		inputMeterB	= convertToMeter(inputB, unitB);
		sumOfValues	+= inputMeterB;
		cnt	+= 1;
		values.push_back(inputMeterB);
		largest		= trackNumberLargest(inputMeterB, largest);
		smallest 	= trackNumberSmallest(inputMeterB, smallest);

		cout << "The numbers you have entered are: " << inputA << unitA << " and " << inputB << unitB << endl;

		compareTwoNumbers(inputMeterA, inputMeterB);

		cout << "New run. Please enter your first number and press enter: " << endl;
	}

	cout << "The game finished! Here are your stats:" << endl;
	cout << "The largest number entered [m]: " << largest << endl;
	cout << "The smallest number entered [m]: " << smallest << endl;
	cout << "The sum of numbers is [m]: " << sumOfValues << endl;
	cout << "The amount of numbers entered: " << cnt << endl;
	cout << "The values you have entered are: " << endl;
	sort(values);
	for (double v : values) cout << v << endl;

	keep_window_open();
	return 0;
}
