/* ASSIGNMENT
 * Write a program that prompts the user to enter some number of pennies (1-cent coins), nickels (5-cent coins), dimes (10-cent coins), quarters (25-cent coins), half dollars (50-cent coins), and one-dollar coins
(100-cent coins). Query the user separately for the number of each size coin, e.g., “How many pennies do you have?” Then your program should
print out something like this:
You have 23 pennies.
You have 17 nickels.
You have 14 dimes.
You have 7 quarters.
You have 3 half dollars.
The value of all of your coins is 573 cents.
Make some improvements: if only one of a coin is reported, make the
output grammatically correct, e.g., 14 dimes and 1 dime (not 1 dimes).
Also, report the sum in dollars and cents, i.e., $5.73 instead of 573 cents.
 *
 *  Created on: 29.12.2017
 *      Author: Nachtfuchs
 */

#include "../std_lib_facilities.h"

int main()
{

	cout << "This program converts your coins into dollars and pennies." << endl;
	cout << "Please answer the following questions:" << endl;

	cout << "How many pennies do you have?" << endl;
	int penny {-1}, nickel{1}, dime{-1}, quarter{-1}, halfDollar{-1}, dollar{-1}; // amount of coins
	int sum{-1}; // total amount of coins in cents
	while (cin >> penny)
	{
		// Ask for user information
		cout << "How many nickels do you have? " << endl;
		cin >> nickel;
		cout << "How many dimes do you have?" << endl;
		cin >> dime;
		cout << "How many quarters do you have?" << endl;
		cin >> quarter;
		cout << "How many half dollars do you have?" << endl;
		cin >> halfDollar;
		cout << "How many dollars do you have?" << endl;
		cin >> dollar;

		// Check PRE-CONDITION.
		if (penny < 0)
		{
			cerr << "The value for pennies is invalid: pennies = " << penny << endl;// do nothing
		}
		else if (nickel < 0)
		{
			cerr << "The value for nickels is invalid: nickels = " << nickel << endl;// do nothing
		}
		else if ( dime < 0)
		{
			cerr << "The value for dimes is invalid: dimes = " << dime << endl;// do nothing
		}
		else if (quarter < 0)
		{
			cerr << "The value for quarters is invalid: quarters = " << quarter << endl;// do nothing
		}
		else if (halfDollar < 0)
		{
			cerr << "The value for half dollars is invalid: half dollars = " << halfDollar << endl;// do nothing
		}
		else if (dollar < 0)
		{
			cerr << "The value for dollars is invalid: dollars = " << dollar << endl;// do nothing
		}
		sum = penny +  nickel *5 + dime *10 + quarter *25 + halfDollar *50 + dollar *100;
		cout << "The value of all your coins is: " << sum << endl;
		cout << "You have: " << int(sum/100) << " dollars and " << sum%100 << " cents" << " which equals " << float(sum/100.0) << "$" << endl;

		// restart
		cout << "It is time for a new run! How many pennies do you have?" << endl;
		cout << "This game never gets old" << endl;
	}
	keep_window_open();
	return 0;
}
