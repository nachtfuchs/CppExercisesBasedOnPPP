/*
 * Date.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */
#include "../std_lib_facilities.h"

namespace Chrono {

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

enum class Day {
	sunday = 0, monday, tuesday, wednesday, thursday, friday, saturday
};

class Date {
public:
	class Invalid { }; // to throw as exception
	Date(int y, Month m, int d); // check for valid date and initialize
	Date(); // default constructor
	// the default copy operations are fine
	// nonmodifying operations:
	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }

	// modifying operations:
	void add_day(int n);
	void add_month(int n);
	void add_year(int n);
private:
	int y;
	Month m;
	int d;
}; // Date

bool is_date(int y, Month m, int d); // true for valid date
int getDayInMonth( const Month& );
bool leapyear(int y); // true if y is a leap year
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);
Month operator++( Month& ); // prefix ++
//Month operator+( Month&, Month& );
Month operator+( const Month&, int );

} // Chrono
