/* @brief Assignment from chapter 7 the drill.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 */

/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.
*/

/*
Simple calculator
Revision history:
Originally written by Bjarne Stroustrup
copied by me :-)

This program implements a basic expression calculator.

Input from cin; output to cout.

The grammar for input is:
Calculation:
	Statement
	Print
	Quit
	Calculation Statement

Print:
	;

Quit:
	q

Statement:
	Declaration
	Expression


Declaration:
	"let" Name "=" Expression

Expression:
	Term
	Expression + Term
	Expression � Term
Term:
	Primary
	Term * Primary
	Term / Primary
	Term % Primary
Primary:
	Number
	( Expression )
	Keyword Function
	� Primary
	+ Primary
Number:
	floating-point-literal

Keyword Function:
	"sqrt" "(" Expression ")"
	"pow" "(" Expression "," integer Primary ")"

Input comes from cin through the Token_stream called ts.
*/

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------
class Token {
public:
	char kind;			// what kind of token
	double value;		// for numbers: a value
	string name;		// in case its a variable, or keyword function like sqrt()
	// constructors
	Token(char ch) 		// make a Token from a char
		:kind{ch} { }
	Token(char ch, double val)	// make a Token from a char and a double
		:kind{ch}, value{val} { }
	Token(char ch, string n) : kind{ch}, name{n} { } // initialize kind and name
};

//------------------------------------------------------------------------------
class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();
	void putback(Token t);
	void ignore(char);

private:
	bool full;
	Token buffer;
};

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream()
:full(false), buffer(0) {}

//------------------------------------------------------------------------------
// The putback() member function puts its argument back into the Token_stream's buffer:
void Token_stream::putback(Token t)
{
    if (full) error("putback() into a full buffer");
    buffer = t;       // copy t to buffer
    full = true;      // buffer is now full
}

//------------------------------------------------------------------------------
// Define symbolic constants
const char let	= '#';
const char quit = 'q';
const char name = 'a';
const char print	= ';';
const char number	= '8';
const char keyfunc	= 'k';

//------------------------------------------------------------------------------
Token Token_stream::get()
{
	// deal with Tokens in the buffer
	if (full) {
		full = false;
		return buffer;
	}

	char ch;	// ATTENTION: This calculator works with 'char' at this point only,
				// because "cin" uses chars. So it would NOT work with string!
	cin >> ch;	// note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case ',':	// An argument seperator for "pow(x, y)"
		case print: // for printing
		case quit:	// leave the application
		case '=':	// for user defined "Variable" type.
			return Token(ch);	// let each character represent itself
		case '#':
			return Token(let);
		case '.': // a floating-point-literal can start with a dot
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8':	case '9':
		{
			cin.putback(ch);
			double val;
			cin >> val;
			return Token(number,val);
		}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch; // allow variable names
			cin.putback(ch);	// The last character that does not fullfil the
								// previous conditions needs to be stored, or it
								// will get "lost".
//			if (s == "let") return Token(let);
			if (s == "quit") return Token(name);
			if (s == "sqrt") return Token(keyfunc, "sqrt");
			if (s == "pow") return Token(keyfunc, "pow");
			return Token(name, s);
		}
		error("Bad token");
	}
}

//------------------------------------------------------------------------------
/* @brief ignore particular input character strings to clean up code
 * */
void Token_stream::ignore(char c)
{
	// check if by any chance the buffer is holding the charater to ignore:
	if (full && c == buffer.kind) {
		full = false;
		return;
	}

	// read the next characters and ignore all that are no the input character c
	full = false;
	char ch;
	while (cin>>ch) // This is where the excessive characters are ignored
		if (ch == c) return;
}

//------------------------------------------------------------------------------
/* @brief A class that allows to use variables like 'x', 's' etc. in the
 * 		calculator. Values must (!) be assigned to the variables.
 * */
class Variable {
public:
	string name;
	double value;
	Variable(string n, double v) :name{n}, value{v} { }
};

//------------------------------------------------------------------------------
vector<Variable> varTable;

//------------------------------------------------------------------------------
/* @brief Get the value of a user defined Variable
 * */
double get_value(string s)
{
	for (const Variable& v : varTable)
		if (v.name == s) return v.value;
	error("get_value: undefined name ", s);
}

//------------------------------------------------------------------------------
/* @brief Set the value of a user defined Variable
 * */
void set_value(string s, double d)
{
	for (Variable v : varTable)
		if (v.name == s) {
			v.value = d;
			return;
		}
	error("set_value: undefined name ",s);
}

//------------------------------------------------------------------------------
/* @brief Check if the newly added variable already exists in the Variable table
 * */
bool is_declared(string s)
{
	for (const Variable& v : varTable)
		if (v.name == s) return true;
	return false;
}

/* @brief A short function to define quickly a Variable type AND add it to the
 * 		global Variable table "varTable".
 * */
double define_name(string var, double val)
// add (var, val) to var_table
{
	if ( is_declared(var) ) error( var, " declared twice" );
	varTable.push_back( Variable(var, val) );
	return val;
}

Token_stream ts;

double expression();
double primary();

//------------------------------------------------------------------------------
/* @brief Calculate the result of a keyword function like "sqrt()"
 * */
double keywordFunction()
{
	Token t = ts.get(); // Get the token from the buffer!
	double res {}; 	// The result of the keyword function
	double d {}; 	// the expression value is saved here
	double p {};	// the primary value is saved here
	if (t.name == "sqrt")
	{
		d = expression(); // an expression is followed after a keyword function
		if (d > 0) res = sqrt(d);
		else error("Cannot compute the square root of a negative number: ", d);
	}
	else if (t.name == "pow")
	{
		// The user typed in "pow( expression , power )"
		t = ts.get(); // expecting an '('
		if (t.kind != '(') error("'(' expected");
		d = expression(); // an expression is followed after a keyword function name
		t = ts.get(); // expecting an ','
		if (t.kind != ',')
			error("Missing argument separator ',' between two arguments in pow(x, y)");
		p = narrow_cast<int>( primary() );	// allow only integer number as the
											// "power" argument in pow()
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		res = pow(d, p);
	}
	else error("Unknown keyword function ", t.name);
	return res;
}

//------------------------------------------------------------------------------
double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':	// handle '(' expression ')'
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	};
	case '-': // deal with negative numbers
		return - primary();
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case '+':
		return primary();
	case keyfunc:
		ts.putback(t); 	// put back the Token information so that the correct
						// keyword function can be used
		return keywordFunction();
		break;
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------
// deal with *, /, and %
double term()
{
	double left = primary();
	Token t = ts.get();        // get the next token from token stream
	while(true) {	// The while-loop allows multiple terms
		switch(t.kind) {
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
		case '%':
		{
			double d = primary();
			if (d == 0) error("divide by zero (%-operator)");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------
// deal with + and -
double expression()
{
	double left = term();
	Token t = ts.get();	// get the next token from token stream

	while(true) {
		switch(t.kind) {
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;	// finally: no more + or -. Return the calculation
							// result.
		}
	}
}

//------------------------------------------------------------------------------
/* assume we have seen "let�
*  handle: name = expression
*  declare a variable called "name� with the initial value "expression"
*/
double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");
	string varName = t.name;
	if (is_declared(varName)) error(varName, " declared twice");
	Token t2 = ts.get();
	if (t2.kind != '=') error(" '=' missing in declaration of ", varName);
	double d = expression();
	varTable.push_back( Variable(varName, d) );
	return d;
}

//------------------------------------------------------------------------------
/* @brief Handles Declarations and Expressions of the grammar
 * */
double statement()
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration();
		break;
	default:
		ts.putback(t);
		return expression();
	}
}

//------------------------------------------------------------------------------
void clean_up_mess()
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------
void calculate()
{
	while(cin)
	try	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // first, discard all prints
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << '\n'; // write error message
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------
int main()
try {
	cout << "Welcome to our simple calculator. " << endl;
	cout << "Please enter expressions using floating point numbers." << endl;

	cout << "Currently, the '+', '-', '*', '/' and '%' operators are available." << endl;
	cout << "You can define your own variables using the '#' sign," << endl;
	cout << "followed by a '=' and a value, e.g.: '# bn = 1,000,000,000" <<
															print << "'." << endl;
	cout << "There are two functions available for the square root, and the power " << endl;
	cout << "of a number. The functions are: sqrt(number), and pow(x, y) with x " << endl;
	cout << "being the base number and y being the exponent." << endl;
	cout << "It is possible to use the circle number 'pi', and the Euler number 'e'." << endl;
	cout << "If you want to finish your expression, then please type '" <<
			print << "'. It will calculate the result." << endl;
	cout << "If you want to exit the calculator, please type '" << quit << "'." << endl;

	// predefine names:
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k", 1000);
	calculate();
	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c !=';') ;
	keep_window_open("~~");
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c !=';');
	keep_window_open("~~");
	return 2;
}
