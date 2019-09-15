/* @brief Assignment from chapter 6 exercise 10.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * A permutation is an ordered subset of a set. For example, say you wanted
 * to pick a combination to a vault. There are 60 possible numbers, and
 * you need three different numbers for the combination. There are P(60,3)
 * permutations for the combination, where P is defined by the formula
 * P(a, b) = (a!)/((a-b)!)
 * where ! is used as a suffix factorial operator. For example, 4! is 4*3*2*1.
 * Combinations are similar to permutations, except that the order of the
 * objects doesn’t matter. For example, if you were making a “banana split”
 * sundae and wished to use three different flavors of ice cream out of five
 * that you had, you wouldn’t care if you used a scoop of vanilla at the
 * beginning or the end; you would still have used vanilla. The formula for
 * combinations is
 * C(a, b) = P(a, b)/(b!)
 * Design a program that
 * asks users for two numbers,
 * asks them whether they want to calculate permutations or combinations,
 * and prints out the result.
 * This will have several parts. Do an analysis of the above
 * requirements. Write exactly what the program will have to do. Then, go into
 * the design phase. Write pseudo code for the program, and break it into
 * sub-components. This program should have error checking. Make sure
 * that all erroneous inputs will generate good error messages
 *
 * NOTE:
 * Check RequirementAnalysis.md for the requirement analysis.
 * Check PseudoCode.md for the pseudo code.
 */

#include "../std_lib_facilities.h"

int calcFactorial(int input)
{
	/* @brief calculate the factorial of the input number. E.g.: 4! = 4*3*2*1=24
	 *
	 * @input An integer (!) input number. The factorial is defined only for integer numbers!
	 * */
	int result {input};
	if (input < 0) error("The input to the factorial operator needs to be larger than zero.");
	if (input == 0 || input == 1) return 1;
	for (int i = input-1; i >= 2; i--)
	{
		result *= i;
	}
	return result;
}

unsigned int calcMaxFact(void)
{
	/* @brief Calculate the maximum number that the factorial operator can be applied upon.
	 *
	 * @input NONE
	 * @output i The maximum number that the factorial operator can be applied upon.
	 * */
	double factorial {1}; 	// contains the factorial
	bool overrun {false};	// identifies whether the double variable was overflown.
	unsigned int i {0};		// The factorial "step"
	for(i = 2; !overrun; i++) // i is the increasing factor
	{
//		cout << "DEBUG factorial: " << factorial << endl;
		if (isinf(factorial)) // it turns out, that double can save the value "inf" for infinity
		{
			overrun = true; 	// overrun occurs, if new factorial is larger than
								// valid positive double values. Then a negative
								// value is assigned
			break; // exit the for-loop. "i" will not be increased
		}
		factorial *= i; // calculate the factorial for step i
	}
	return i - 1; 	// "-1", because the overrun happened with "i". One step
					// prior is a number that can be factorialized.
}

char getRestart(void)
{
	/* @brief Check if the input is a 'y' or any other character. This function
	 * 		was created mainly out of readability purposes in main().
	 * */
	char restart {};
	cout << "If you want to restart the calculation, please enter 'y'. If you want to exit" << endl;
	cout << "please enter any other letter. Please enter your choice:" << endl;
	cin >> restart;
	if(!cin) error("The input for the restart could not be understood. Aborting the application.");
	return restart;
}

unsigned int getInputNumber(void)
{
	/* @brief Get input from user and return it, but check if the factorial operator can
	 * 		  be applied to it.
	 *
	 * @input NONE
	 * @output n The number that was entered by the user
	 * */
	unsigned int n {};
	unsigned int nMax = calcMaxFact();
	bool isValid {false};
	while(!isValid) // request a correct input until it is correct
	{
		cin >> n;
		if (!cin) cout << "The input number is invalid. Please use only positive integer values." << endl;
		else if (n > nMax) cout << "The input number " << n << "is larger than allowed (max = " << nMax << ")" << endl;
		else isValid = true; // input is accepted.
		if (!isValid) // allow the user to enter a new number
		{
			cout << "The number you have entered is invalid. Please enter a new number and hit the 'enter'-button: ";
		}
	}
	return n;
}

char getCalcMethod(void)
{
	/* @brief Get calculation method from user
	 *
	 * @input NONE
	 * @output m Calculation method that was requested by the user. Either
	 * 			'p'ermutation or 'c'ombination
	 * */
	char m {}; // The requested method
	bool isValid {false};
	cout << "Please enter the calculation that you want to perform. Type 'p' for permutation," << endl;
	cout << "or 'c' for combination. Your request:" << endl;
	while(!isValid) // request a correct input until it is correct
	{
		cin >> m;
		if (!cin)
		{
			cout << "The input character is invalid. Please use either 'p' for permutation," << endl;
			cout << "or 'c' for combination. Your request:" << endl;
		}
		else if (m == 'p' or m == 'c') isValid = true;// input is accepted.
		if (!isValid) // allow the user to enter the calculation method again
		{
			cout << "The requested calculation method does not exist." << endl;
			cout << "Please use either 'p' for permutation, or 'c' for combination. Your request:" << endl;
		}
	}
	return m;
}

bool checkPermutationInput(unsigned int a, unsigned int b)
{
	/* @brief Check if the permutation formula
	 * 				P(a, b) = (a!)/((a-b)!)
	 * 		  can be calculated with the given inputs.
	 * @input a A positive integer number that should be larger or equal than b
	 * @input b A positive integer number that should be smaller or equal than a
	 *
	 * @output isValid 'true' if permutation can be calculated with given inputs.
	 * */
	if (a >= b)	return true;
	else return false;
}

double calcPermutation(unsigned int a, unsigned int b)
{
	/* @brief Calculate the permutation based on the input values 'a' and 'b'. Formula:
	 * 				P(a, b) = (a!)/((a-b)!)
	 * @input a A positive integer number larger than 0 and larger than b
	 * @input b A positive integer number larger than 0 and smaller than a
	 *
	 * @output p The permutations using a and b
	 * */
	double p {0};
	p = calcFactorial(a) / calcFactorial(a-b);
	return p;
}

double calcCombination(unsigned int a, unsigned int b)
{
	/* @brief Calculate the combination based on the input values 'a' and 'b'. Formula:
	 * 				C(a, b) = P(a, b)/(b!)
	 * @input a A positive integer number larger than 0 and larger than b
	 * @input b A positive integer number larger than 0 and smaller than a
	 *
	 * @output p The combinations using a and b
	 * */
	double c {0};
	c = calcPermutation(a, b) / calcFactorial(b);
	return c;
}

void printOutput(unsigned int a, unsigned int b, char rMethod, double res)
{
	/* @brief Write the output to the reader and repeat the users requests
	 * 		in order to make it more transparent to the user.
	 * @input a The a parameter for the calculation method
	 * @input b The b parameter for the calculation method
	 * @input rMethod A character 'p' for permutation, or 'c' for combination
	 * @input res The result of the requested calculation method.
	 *
	 * @output A prompt message
	 * */
	cout << "For the parameter a = " << a << " and b = " << b;
	if (rMethod == 'p') cout << " the number of permutations are: " << endl << res << endl;
	else if (rMethod == 'c') cout << " the number of combinations are: " << endl << res << endl;
	else error("Unknown error in printOutput(). Aborting the application.");
}
int main()
{
	cout << "This application is able to calculate the permutation and combination of two" << endl;
	cout << "positive integer numbers. A permutation is the following fomula:" << endl;
	cout << "   P(a, b) = (a!)/((a-b)!) " << endl;
	cout << "A combination is the following formula:" << endl;
	cout << "   C(a, b) = P(a, b)/(b!)" << endl;
	cout << "Please enter your two integer numbers 'a' and 'b', and then choose the" << endl;
	cout << "desired calculation method. The maximum number that can be entered for a or b is: " << endl;
	cout << "maximum = " << calcMaxFact() << endl;
	cout << "Number 'a' needs to be larger than 'b' or else, the permutation cannot be calculated." << endl;
	cout << "You can exit the application any time by entering 'Ctrl' + 'Z'." << endl;
	cout << "Let's begin!" << endl;

	unsigned int a {};	// parameter a for the permutation or combination
	unsigned int b {};	// parameter b for the permutation or combination
	double res {-1};	// save the permutation or combination of 'a' and 'b'
	char restart {'y'};	// save the parameter 'y'es, or 'n'o for continuing the application
	char rMethod {'x'}; // The requested calculation method by the user

	while(restart == 'y')
	{
		cout << "Please enter number 'a' and push the 'enter'-button:" << endl;
		a = getInputNumber();
		cout << "Please enter number 'b':" << endl;
		b = getInputNumber();
		if (checkPermutationInput(a, b)) {/*Do nothing*/}
		else error("Input number 'b' is larger than 'a'. Permutation cannot be calculated. Closing the application.");
		rMethod = getCalcMethod();
		if (rMethod == 'p')
			res = calcPermutation(a, b);
		else if (rMethod == 'c')
			res = calcCombination(a, b);
		else
			error("Unknown error. Calculation method is unknown. Aborting the application.");
		printOutput(a, b, rMethod, res);
		restart = getRestart();
	}
	keep_window_open();
	return 0;
}
