/* @brief Assignment from chapter 10 the Exercise 7.
 * Book: Programming Principle and Practice using C++ - Stroustrup
 *
 * ASSINGMENT:
 * Make a version of the calculator from Chapter 7 that accepts Roman
 * numerals rather than the usual Arabic ones, for example, XXI + CIV ==
 * CXXV.
 *
 * LESSONS LEARNED:
 * - It is challenging to create the Roman_int-library in a way to use it "as is"
 *   for the calculator. E.g. "I+V;" fails, because the input operator>> for
 *   Roman_int interprets the whole thing as a string and displays a warning.
 * - In order to run Roman numerals easily, the calculator-code needs to be
 *   adapted using the interface in "Roman_int". And it can happen that the interface
 *   is not enough to run the calculator smoothly.
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
	"const" Name "=" Expression

Expression:
	Term
	Expression + Term
	Expression – Term
Term:
	Primary
	Term * Primary
	Term / Primary
	Term % Primary
Primary:
	Number
	Roman number
	( Expression )
	Keyword Function
	– Primary
	+ Primary
Number:
	floating-point-literal

Keyword Function:
	"sqrt" "(" Expression ")"
	"pow" "(" Expression "," integer Primary ")"

Input comes from cin through the Token_stream called ts.
*/

#include "Roman_int.h"

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
	Token(char ch, Roman_int rVal)	// make a Token from a char and a Roman_int
			:kind{ch}, value{rVal.as_int()} { }
	Token(char ch, string n) : kind{ch}, name{n} { } // initialize kind and name
};

//------------------------------------------------------------------------------
class Token_stream {
public:
	Token_stream( istream& );   // make a Token_stream that reads from cin
	Token get();
	void putback(Token t);
	void ignore(char);

private:
	bool full;
	Token buffer;
};

// The constructor just sets full to indicate that the buffer is empty:
Token_stream::Token_stream( istream& )
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
// Define symbolic constants to make use of the switch-case statement when dealing
// with the calculation.
const char let	= '#';
const char quit = 'q';
const char name = 'a';
const char print	= ';';
const char number	= '8';
const char romanNumber	= 'r';
const char keyfunc	= 'k';
const char constVar	= 'c';

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
		case 'I': case 'V': case 'X': case 'L': case 'C':
		case 'D': case 'M':
		{
			//roman numbers
			cin.putback(ch);
			Roman_int rVal;
			cin >> rVal;
			return Token(romanNumber, rVal);
		}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while(cin.get(ch) && (isalpha(ch) || isdigit(ch) || (ch == '_') )) s += ch; // allow variable names
			cin.putback(ch);	// The last character that does not fulfill the
								// previous conditions, and needs to be put back,
								// or it will get "lost".
			if (s == "quit") return Token(name);
			if (s == "sqrt") return Token(keyfunc, "sqrt");
			if (s == "pow") return Token(keyfunc, "pow");
			if (s == "const") return Token(constVar, "const");
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
	// check if by any chance the buffer is holding the character to ignore:
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
 * 		Allows "const" variables.
 * */
class Variable {
public:
	string name;
	double value;
	bool isConst;	// Flag that shows whether the variable can be overwritten
					// by the user
	Variable(string n, double v) :name{n}, value{v}, isConst(false) { }
	Variable(string n, double v, bool c) :name{n}, value{v}, isConst(c) { }
};

//------------------------------------------------------------------------------
vector<Variable> varTable;

//------------------------------------------------------------------------------
/* @brief A class that allows to use variables like 'x', 's' etc. in the
 * 		calculator. Values must (!) be assigned to the variables.
 * 		Allows "const" variables.
 * */
class SymbolTable {
public:
	vector<Variable> m_varTable;

	SymbolTable() {};

	double get(string s);
	void set(string s, double d);
	bool isDeclared(string s);
	double declare(string s, double v, bool isConst);
};

SymbolTable symTable;

//------------------------------------------------------------------------------
/* @brief Get the value of a user defined Variable
 * */
double SymbolTable::get(string s)
{
	for (const Variable& v : m_varTable)
		if (v.name == s) return v.value;
	error("SymbolTable::get: undefined name: ", s);
}

//------------------------------------------------------------------------------
/* @brief Set the value of a user defined Variable
 * */
void SymbolTable::set(string s, double d)
{
	for (int i = 0; i < m_varTable.size(); i++)
	{
		if (m_varTable[i].name == s && m_varTable[i].isConst == false) {
			m_varTable[i].value = d;
			return;
		}
		else if ( m_varTable[i].name == s && m_varTable[i].isConst == true )
		{
			error("SymbolTable::set - The variable is a 'constant' variable and its value cannot be changed. Variable name: ", s);
		}
	}
	error("SymbolTable::set - undefined name: ", s);
}

//------------------------------------------------------------------------------
/* @brief Check if the newly added variable already exists in the Variable table
 * */
bool SymbolTable::isDeclared(string s)
{
	for (const Variable& v : m_varTable)
		if (v.name == s) return true;
	return false;
}

/* @brief A short function to define quickly a Variable type AND add it to the
 * 		global SymbolTable table "m_varTable".
 * */
double SymbolTable::declare(string var, double val, bool isConst = false)
// add (var, val) to m_varTable
{
	if ( isDeclared(var) ) set(var, val); // overwrite the old value
	else m_varTable.push_back( Variable(var, val, isConst) );
	return val;
}

double expression( Token_stream& );
double primary( Token_stream& );

//------------------------------------------------------------------------------
/* @brief Calculate the result of a keyword function like "sqrt()"
 * */
double keywordFunction( Token_stream& ts )
{
	Token t = ts.get(); // Get the token from the buffer!
	double res {}; 	// The result of the keyword function
	double d {}; 	// the expression value is saved here
	double p {};	// the primary value is saved here
	if (t.name == "sqrt")
	{
		d = expression( ts ); // an expression is followed after a keyword function
		if (d > 0) res = sqrt(d);
		else error("Cannot compute the square root of a negative number: ", d);
	}
	else if (t.name == "pow")
	{
		// The user typed in "pow( expression , power )"
		t = ts.get(); // expecting an '('
		if (t.kind != '(') error("'(' expected");
		d = expression( ts ); // an expression is followed after a keyword function name
		t = ts.get(); // expecting an ','
		if (t.kind != ',')
			error("Missing argument separator ',' between two arguments in pow(x, y)");
		p = narrow_cast<int>( primary( ts ) );	// allow only integer number as the
											// "power" argument in pow()
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		res = pow(d, p);
	}
	else error("Unknown keyword function ", t.name);
	return res;
}

//------------------------------------------------------------------------------
double primary( Token_stream& ts )
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':	// handle '(' expression ')'
	{
		double d = expression( ts );
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	};
	case '-': // deal with negative numbers
		return - primary( ts );
	case number:
		return t.value;
	case romanNumber:
		return t.value;
	case name:
		return symTable.get(t.name);
	case '+':
		return primary( ts );
	case keyfunc:
		ts.putback(t); 	// put back the Token information so that the correct
						// keyword function can be used
		return keywordFunction( ts );
		break;
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------
// deal with *, /, and %
double term( Token_stream& ts )
{
	double left = primary( ts );
	Token t = ts.get();        // get the next token from token stream
	while(true) {	// The while-loop allows multiple terms
		switch(t.kind) {
		case '*':
			left *= primary( ts );
			t = ts.get();
			break;
		case '/':
		{
			double d = primary( ts );
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary( ts );
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
double expression( Token_stream& ts )
{
	double left = term( ts );
	Token t = ts.get();	// get the next token from token stream

	while(true) {
		switch(t.kind) {
		case '+':
			left += term( ts );
			t = ts.get();
			break;
		case '-':
			left -= term( ts );
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
/* assume we have seen "let”
*  handle: name = expression
*  declare a variable called "name” with the initial value "expression"
*  @input isConst A flag that symbolized whether this variable should be a
*  				  'constant'
*/
double declaration( Token_stream& ts, bool isConst = false)
{
	Token t = ts.get();
	if (t.kind != name) error ("name expected in declaration");
	string varName = t.name;
	Token t2 = ts.get();
	if (t2.kind != '=') error(" '=' missing in declaration of ", varName);
	double d = expression( ts );
	if (symTable.isDeclared(varName))
		symTable.set(varName, d); // overwrite old variable value
	else
		symTable.declare( varName, d, isConst ); // add new variable
	return d;
}

//------------------------------------------------------------------------------
/* @brief Handles Declarations and Expressions of the grammar
 * */
double statement( Token_stream& ts )
{
	Token t = ts.get();
	switch(t.kind) {
	case let:
		return declaration( ts );
		break;
	case constVar:
		return declaration( ts, true);
		break;
	default:
		ts.putback(t);
		return expression( ts );
	}
}

//------------------------------------------------------------------------------
void clean_up_mess( Token_stream& ts )
{
	ts.ignore(print);
}

const string prompt = "> ";
const string result = "= ";

//------------------------------------------------------------------------------
void calculate()
{
	Token_stream ts( cin );
	while(cin)
	try	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // first, discard all prints
		if (t.kind == quit) return;
		ts.putback(t);
		if( t.kind == romanNumber )
			cout << result << to_roman( statement( ts ) ) << endl;
		else
			cout << result << statement( ts ) << endl;
	}
	catch (exception& e) {
		cerr << e.what() << '\n'; // write error message
		clean_up_mess( ts );
	}
}

//------------------------------------------------------------------------------
int main()
try {
	cout << "Welcome to our simple calculator. " << endl;
	cout << "Please enter expressions using floating point numbers." << endl;

	cout << "Currently, the '+', '-', '*', '/' and '%' operators are available." << endl;
	cout << "You can define your own variables using the '" << let << "' sign," << endl;
	cout << "followed by a '=' and a value, e.g.: '# bn = 1,000,000,000" <<
															print << "'." << endl;
	cout << "Variable can be made 'constant' by using the '" << constVar << "' keyword," << endl;
	cout << "e.g. 'const g = 9.81'." << endl;
	cout << "There are two functions available for the square root, and the power " << endl;
	cout << "of a number. The functions are: sqrt(number), and pow(x, y) with x " << endl;
	cout << "being the base number and y being the exponent." << endl;
	cout << "It is possible to use the circle number 'pi', and the Euler number 'e'," << endl;
	cout << "as well as k for '1000'." << endl;
	cout << "It is also possible to use Roman numbers like: I, V, X, L, C, D, M." << endl;
	cout << "If you want to finish your expression, then please type '" <<
			print << "'. It will calculate the result." << endl;
	cout << "If you want to exit the calculator, please type '" << quit << "'." << endl;

	// predefine names:
	symTable.declare("pi", 3.1415926535);
	symTable.declare("e", 2.7182818284);
	symTable.declare("k", 1000);
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
