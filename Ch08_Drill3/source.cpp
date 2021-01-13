/* @brief Assignment from chapter 8 drill 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Write a program using a single file containing three namespaces X, Y, and
 * Z so that the following main() works correctly:
 *
 * int main()
 * {
 * X::var = 7;
 * X::print(); // print X’s var
 * using namespace Y;
 * var = 9;
 * print(); // print Y’s var
 * {
 * 		using Z::var;
 * 		using Z::print;
 * 		var = 11;
 * 		print(); // print Z’s var
 * }
 * print(); // print Y’s var
 * X::print(); // print X’s var
 * }
 * Each namespace needs to define a variable called var and a function called
 * print() that outputs the appropriate var using cout.
}
 */

#include "../std_lib_facilities.h"

namespace X
{
	int var;
	void print()
	{
		cout << "X var:" << var << endl;
	}
}

namespace Y
{
	int var;
	void print()
	{
		cout << "Y var:" << var << endl;
	}
}

namespace Z
{
	int var;
	void print()
	{
		cout << "Z var:" << var << endl;
	}
}

int main()
{

//	cout << "Hello world!" << endl;
	X::var = 7;
	X::print(); // print X’s var
	using namespace Y;
	var = 9;
	print(); // print Y’s var

	{
		using Z::var;
		using Z::print;
		var = 11;
		print(); // print Z’s var
	}

	print(); // print Y’s var
	X::print(); // print X’s var

	keep_window_open();
	return 0;
}
