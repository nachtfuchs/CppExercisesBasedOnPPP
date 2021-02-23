As stated in [Wikipedia](https://en.wikipedia.org/wiki/Roman_numerals#Description), there was and is no standard when calculating with Roman numbers.

So this solution has the interpretation, that there 
- is no number larger than 3999
- there is only the substractive notation with at most one literal before a larger literal
	- "IIX" is NOT 8
	- legal numbers (subtractive notation for a two-digit number)
		- IV
		- IX
		- XL
		- XC
		- CD
		- CM
	- illegal numbers
		- XD
		- LD
		- LM
		- ...
- at most, three characters of I, X, C, and M can be concatenated
	- VIII = 8
	- IIII is NOT 4;
- The left number is larger than the right number. Exception is the "subtractive notation" mentioned above.