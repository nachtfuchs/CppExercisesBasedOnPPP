/* @brief Drill from chapter 6 exercise 3.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * Add a factorial operator: use a suffix ! operator to represent “factorial.”
 * For example, the expression 7! means 7 * 6 * 5 * 4 * 3 * 2 * 1. Make ! bind
 * tighter than * and /; that is, 7*8! means 7*(8!) rather than (7*8)!. Begin by
 * modifying the grammar to account for a higher-level operator. To agree
 * with the standard mathematical definition of factorial, let 0! evaluate to 1.
 * Hint: The calculator functions deal with doubles, but factorial is defined
 * only for ints, so just for x!, assign the x to an int and calculate the factorial
 * of that int.
 */


#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------
class Token {
public:
    char kind;        // what kind of token
    double value;     // for numbers: a value
    Token(char ch)    // make a Token from a char
        :kind(ch), value(0) { }
    Token(char ch, double val)     // make a Token from a char and a double
        :kind(ch), value(val) { }
};

//------------------------------------------------------------------------------
class Token_stream {
public:
    Token_stream();   // make a Token_stream that reads from cin
    Token get();      // get a Token (get() is defined elsewhere)
    void putback(Token t);    // put a Token back
private:
    bool full;        // is there a Token in the buffer?
    Token buffer;     // here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0)    // no Token in buffer
{
}

//------------------------------------------------------------------------------

// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------

Token Token_stream::get() // definition is taking place outside of the class definition itself, so the class has to be mentioned that the method belongs to (p.212).
{
    if (full) {       // do we already have a Token ready?
        // remove token from buffer
    	full=false;
        return buffer;
    }

    char ch; // ATTENTION: This calculator works with 'char' at this point only, because "cin" uses chars. So it would NOT work with string!
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
		case '=':    // for "print"
		case 'x':    // for "quit"
		case '(': case ')': case '+': case '-': case '*': case '/': case '{': case '}': case '!':
			return Token(ch);        // let each character represent itself
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
        {
            cin.putback(ch);         // put digit back into the input stream
            double val;
            cin >> val;              // read a floating-point number
//            cout << "DEBUG - Token_stream::get - val: " << val << endl;
            return Token('8',val);   // let '8' represent "a number"
        }
    default:
        error("Bad token");
    }
}

//------------------------------------------------------------------------------

double expression();    // declaration so that primary() can call expression()

//------------------------------------------------------------------------------

Token_stream ts;        // provides get() and putback()

//------------------------------------------------------------------------------

// deal with numbers and parentheses
double primary()
{
    Token t = ts.get();
    switch (t.kind) {
    case '{':
    {
    	double d = expression();
    	t = ts.get();
    	if (t.kind != '}') error ("'}' expected");
    	return d;
    };
    case '(':    // handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
//            cout << "DEBUG - primary '(' - d: " << d << endl;
		return d;
	};
    case '8':            // we use '8' to represent a number
//    	cout << "DEBUG - primary '8' - t.value: " << t.value << endl;
        return t.value;  // return the number's value
    default:
        error("primary expected");
    }
}

//------------------------------------------------------------------------------
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

/* @brief factorial() allows to deal with the mathematical factorial operator "!".
 *
 * @NOTE: Currently, only one factorial operator is allowed. Example: "3!" returns "6".
 * 		But "3!!" does not return "6!" -> Add a while loop as in "term()" or "expression"
 * 		to allow multiple factorial operators.
 * */
int factorial()
{
	double left = primary();
	Token t = ts.get();
	switch (t.kind) {
		case '!':
		{
			// calculate the factorial
			int factorialNumber = calcFactorial( (int) left);
			return factorialNumber; // break is not necessary anymore, because 'return' exits the function
		}
		default:
			ts.putback(t);
			return left;
	}
}

//------------------------------------------------------------------------------

// deal with *, /, and %
double term()
{
//    double left = primary();
	double left = factorial();
//    cout << "DEBUG - term - left: " << left << endl;
    Token t = ts.get();        // get the next token from token stream

    while(true) { // The while-loop allows multiple terms
        switch (t.kind) {
        case '*':
            left *= primary();
            t = ts.get();
            break;
        case '/':
            {
                double d = primary();
                if (d == 0) error("divide by zero");
                left /= d;
                t = ts.get();
                break;
            }
        default:
            ts.putback(t);     // put t back into the token stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

// deal with + and -
double expression()
{
    double left = term();      // read and evaluate a Term
    Token t = ts.get();        // get the next token from token stream

    while(true) {	// The while-loop allows multiple expressions
        switch(t.kind) {
        case '+':
            left += term();    // evaluate Term and add
//            cout << "DEBUG - expression '+' - left: " << left << endl;
            t = ts.get();
            break;
        case '-':
            left -= term();    // evaluate Term and subtract
            t = ts.get();
            break;
        default:
            ts.putback(t);     // put t back into the token stream
            return left;       // finally: no more + or -: return the answer
        }
    }
}

//------------------------------------------------------------------------------

int main()
try
{
	cout << "Welcome to our simple calculator. " << endl;
	cout << "Please enter expressions using floating point numbers." << endl;

	cout << "Currently, the '+', '-', '*', and '/' operators are available." << endl;
	cout << "If you want to finish your expression, then please type '='. It will calculate the result." << endl;
	cout << "If you want to exit the calculator, please type 'x'." << endl;
	double result{0}; // contains the final result of the calculation

    while (cin) {
//    	cout << "DEBUG - main - while-loop" << endl;
        Token t = ts.get();


        if (t.kind == 'x') break; // 'x' for quit
        if (t.kind == '=')        // '=' for "print now"
            cout << "=" << result << '\n';
        else
        {
            ts.putback(t);
//            cout << "DEBUG - main - t.value: " << t.value << endl;
        }
        result = expression();
    }
	keep_window_open();
}
catch (exception& e) {
    cerr << "error: " << e.what() << '\n';
	keep_window_open();
    return 1;
}
catch (...) {
    cerr << "Oops: unknown exception!\n";
	keep_window_open();
    return 2;
}

//------------------------------------------------------------------------------
