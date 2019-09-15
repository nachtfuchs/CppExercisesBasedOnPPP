/* @brief Assignment from chapter 4 exercise 15.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Write a program that takes an input value n and then finds the first n
 * primes.
 */

#include "../std_lib_facilities.h"

void sieveOfEratosthenes(int maxNumber)
{
	/* @brief Calculates the requested amount of primes starting from number '2' .
	 * 		Maximum number is 65534.
	*		The algorithm is based on the Sieve of Eratosthenes.
	* @input maxNumber A positive integer that represents the first N primes that have to be displayed.
	*
	* @output Displays the requested amount of primes.
	* */
	if (maxNumber < 0) cerr << "The number you have entered '" << maxNumber << "' is less than zero." << endl;
	int limit = 65534;
	vector<int> markedNumbers(limit + 1); // '0' means "no prime". '1' means prime number. '+1', because the index starts with '0'
	vector<int> primeNumbers = {2}; // saves all the primes
	int prime = 2; // The minimum prime number
	bool primeFound = false; // flag that shows if a prime was found

	// initialize all numbers as prime numbers
	for (int i = 0; i < limit; i++)
	{
		markedNumbers[i] = 1;
	}
	markedNumbers[0] = false; // zero is not a prime
	markedNumbers[1] = false; // one is not a prime
	// the first prime number is "2"
	int primeCnt = 1;	// counts the amount of primes identified so far. Default of 1 because of prime number '2'.
	while (primeCnt != maxNumber) // Abort the loop once the maxNumber was analyzed for being a prime number
	{
		cout << "primeCnt = " << primeCnt << endl; //debug
		// mark the multiples of the prime as non-primes
		for (int i = 1; (i * prime) <= limit; i++)
		{
			markedNumbers[i * prime] = 0;
		}

		// check if there are more primes between the last identified prime and the maximum number
		for (int i = prime; (i <= limit) && (primeFound == false); i++)
		{
			if (markedNumbers[i] == 1)
			{
				prime = i;
				primeFound = true; // exit loop
				primeNumbers.push_back(prime);
				primeCnt += 1;
			}
		}
		primeFound = false; //reset for next prime
	}
	cout << "The first " << maxNumber << " primes are: " << endl;
	for (int x : primeNumbers) cout << x << endl;
}

int main()
{
	int userInput = 0; // Number of primes that will be found starting from the number 2
	cout << "Please type in the number of primes that you want to use." << endl;
	cout << "If you need the first five primes, then type '5'." << endl;
	cout << "The first prime is '2'. This application searches up to the number 65354." << endl;
	cout << "Your input: " << endl;

	cin >> userInput;

	sieveOfEratosthenes(userInput);

	keep_window_open();
	return 0;
}
