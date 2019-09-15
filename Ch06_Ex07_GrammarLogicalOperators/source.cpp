/* @brief Assignment from chapter 6 exercise 7.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a grammar for bitwise logical expressions. A bitwise logical
 * expression is much like an arithmetic expression except that the operators
 * are ! (not), ~ (complement), & (and), | (or), and ^ (exclusive or). Each
 * operator does its operation to each bit of its integer operands (see §25.5).
 * ! and ~ are prefix unary operators. A ^ binds tighter than a | (just as *
 * binds tighter than +) so that x|y^z means x|(y^z) rather than (x|y)^z. The
 * & operator binds tighter than ^ so that x^y&z means x^(y&z).
 */

#include "../std_lib_facilities.h"

int main()
{

	cout << "The solution to the assignment is a markdown file called 'GrammarLogicalOperator.md'!" << endl;
	keep_window_open();
	return 0;
}
