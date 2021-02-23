/* @brief Assignment from chapter 9 exercise 13.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Design and implement a rational number class, Rational. A rational
 * number has two parts: a numerator and a denominator, for example, 5/6
 * (five-sixths, also known as approximately .83333). Look up the definition
 * if you need to. Provide assignment, addition, subtraction, multiplication,
 * division, and equality operators. Also, provide a conversion to double.
 * Why would people want to use a Rational class?
 *
 * TODO: Assignment operator=. How to do that?
 *
 * ANSWER:
 * - Personally, I sometimes prefer the representation of a Rational instead of
 *   its irrational number, because of its "accuracy", and readability.
 * - Teaching and learning aspect with Rational numbers is appealing with this
 *   class.
 *
 * LESSONS LEARNED:
 * - One limit of the "arithmetic if" see in "operator==" overloading
 * - Method "toDouble()" requires at least one (double) for the operation
 * */

#include "Rational.h"

int main()
{
	Rational rValidA { 1, 2 };
	cout << "rValidA: " << rValidA << endl;

	Rational rMul { rValidA * rValidA };
	cout << "rMul: " << rMul << endl;

	Rational rDiv { rValidA / rValidA };
	cout << "rDiv: " << rDiv << endl;

	Rational rSum { rValidA + rValidA };
	cout << "rSum: " << rSum << endl;

	Rational rDiff { rValidA - rValidA };
	cout << "rDiff: " << rDiff << endl;

	cout << "equality ( rValidA == rValidA ): " << ( rValidA == rValidA ) << endl;
	cout << "equality ( rValidA == rMul ): " << ( rValidA == rMul ) << endl;

	cout << "larger ( rValidA > rValidA ): " << ( rValidA > rValidA ) << endl;
	cout << "larger ( rValidA > rMul ): " << ( rValidA > rMul ) << endl;
	cout << "larger ( rValidA > rSum ): " << ( rValidA > rSum ) << endl;

	cout << "smaller ( rValidA < rValidA ): " << ( rValidA < rValidA ) << endl;
	cout << "smaller ( rValidA < rMul ): " << ( rValidA < rMul ) << endl;
	cout << "smaller ( rValidA < rSum ): " << ( rValidA < rSum ) << endl;

	keep_window_open();
	return 0;
}
