/* @brief Assignment from chapter 9 exercise 4.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSIGNMENT:
 * Look at the headache-inducing last example of §8.4. Indent it properly and
 * explain the meaning of each construct. Note that the example doesn’t do
 * anything meaningful; it is pure obfuscation.
 *
 * LESSONS LEARNED:
 */

// dangerously ugly code
struct X { // The overall struct X
	void f(int x) // a simple member function
	{
		struct Y { // a "nested" class
			int f() { return 1; } // function f() of struct Y
			int m; // dead code
		};
		int m;
		m=x; // copies the input argument of f() (in struct X)
		Y m2;

		return f( m2.f() ); // return to a void-function -> result is useless! Also: Recursive.
	}
	int m; // member variable of X
	void g(int m) { // inline function definition. Too large to be efficient
		// "if" on an "int" is not so smart.
		if (m) f(m+2); // order of evaluation might be in confilct between function argument "m" and member variable "m".
		else {
			g(m+2); // recursive function -> Is likely to crash, because function was not declared.
		}
	}
	X() { } // constructor; missing ";"
	void m3() {}
	void main() { // Unclear if this "main" should be a member-function
		X a;	// Unclear if this declaration works, since main is nested in struct X.
		a.f(2); // calling the member function f().
	}
};
