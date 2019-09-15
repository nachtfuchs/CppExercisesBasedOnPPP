/* @brief Assignment from chapter 4 exercise 11.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Create a program to find all the prime numbers between 1 and 100. One
 * way to do this is to write a function that will check if a number is prime
 * (i.e., see if the number can be divided by a prime number smaller than
 * itself) using a vector of primes in order (so that if the vector is called
 * primes, primes[0]==2, primes[1]==3, primes[2]==5, etc.). Then write a
 * loop that goes from 1 to 100, checks each number to see if it is a prime,
 * and stores each prime found in a vector. Write another loop that lists the
 * primes you found. You might check your result by comparing your vector
 * of prime numbers with primes. Consider 2 the first prime.
 */

#include "../std_lib_facilities.h"

void sieveOfEratosthenes(int maxNumber)
{
	/* @brief calculates the first primes starting from the number '2' until the input number.
	*		The algorithm is based on the Sieve of Eratosthenes.
	* @input maxNumber A positive integer that represents the upper limit for prime numbers.
	*
	* @output Displays the requested amount of primes.
	* */
	if (maxNumber < 2) cerr << "The number you have entered '" << maxNumber << "' is less than two." << endl;

	vector<int> markedNumbers(maxNumber+1); // '0' means "no prime". '1' means prime number. '+1', because the index starts with '0'
	vector<int> primeNumbers = {2}; // saves all the primes
	int prime = 2; // The minimum prime number
	bool primeFound = false; // flag that shows if a prime was found

	// initialize all numbers as prime numbers
	for (int i = 0; i < markedNumbers.size(); i++)
	{
		markedNumbers[i] = 1;
	}
	markedNumbers[0] = false; // zero is not a prime
	markedNumbers[1] = false; // one is not a prime
	// the first prime number is "2"
	int lastCheckedNumber = 2; // The last number that was analyzed for being a prime. Is in the range of [2, maxNumber].
	while (lastCheckedNumber != maxNumber) // Abort the loop once the maxNumber was analyzed for being a prime number
	{
		// mark the multiples of the prime as non-primes
		for (int i = 1; (i * prime) <= maxNumber; i++)
		{
			markedNumbers[i * prime] = 0;
		}

		// check if there are more primes between the last identified prime and the maximum number
		for (int i = prime; (i <= maxNumber) && (primeFound == false); i++)
		{
			if (markedNumbers[i] == 1)
			{
				prime = i;
				primeFound = true; // exit loop
				primeNumbers.push_back(prime);
			}
			lastCheckedNumber = i; // 'flag' to exit the overall while-loop
		}
		primeFound = false; //reset for next prime
	}
	cout << "The primes until the number: " << maxNumber << " are: " << endl;
	for (int x : primeNumbers) cout << x << endl;
}
int main()
{
	int upperLimit = 20; //the upper threshold based on the exercise.
	cout << "This application calculates the primes from number one to 20." << endl;

	sieveOfEratosthenes(upperLimit);

	keep_window_open();
	return 0;
}
