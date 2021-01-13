/* @brief Assignment from chapter 8 drill 1.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Create three files: my.h, my.cpp, and use.cpp. The header file my.h contains
 * extern int foo;
 * void print_foo();
 * void print(int);
 * The source code file my.cpp #includes my.h and std_lib_facilities.h, defines
 * print_foo() to print the value of foo using cout, and print(int i) to
 * print the value of i using cout.
 * The source code file use.cpp #includes my.h, defines main() to
 * set the value of foo to 7 and print it using print_foo(), and to print the
 * value of 99 using print(). Note that use.cpp does not #include std_lib_facilities.h
 * as it doesn’t directly use any of those facilities.
 * Get these files compiled and run. On Windows, you need to have both use.cpp
 * and my.cpp in a project and use { char cc; cin>>cc; } in use.cpp to be able
 * to see your output. Hint: You need to #include <iostream> to use cin.
 */

#include "my.h"
#include <iostream>

int foo = 7; // LESSON LEARNED: can be declared below "my.h", although "my.cpp"
			 //					uses "foo".
			 // LESSON LEARNED: "foo" needs to be "global" for other files to
			 //					access it.
			 // LESSON LEARNED: "extern" is a silly concept, but helps to make
			 // 				code readable when global variables are used.

int main()
{
	print_foo();

	print(99);
	// work around to keep the window open:
	char cc;
	std::cin >> cc;
	return 0;
}
