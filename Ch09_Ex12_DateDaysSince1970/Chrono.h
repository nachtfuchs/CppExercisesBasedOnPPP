/*
 * Date.h
 *
 *  Created on: 29.01.2021
 *      Author: Nachtfuchs
 */
#include "../std_lib_facilities.h"

namespace Chrono {

class Date {
public:
	class Invalid { }; // to throw as exception
	Date( int d ); // check for valid date and initialize
	Date(); // default constructor
	// the default copy operations are fine
	// nonmodifying operations:
	int day() const { return d; }

	// modifying operations:
	void add_day(int n);
private:
	int d;
}; // Date

bool is_date( int d ); // true for valid date
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);
bool operator<(const Date& a, const Date& b);
bool operator>(const Date& a, const Date& b);
ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);
} // Chrono
