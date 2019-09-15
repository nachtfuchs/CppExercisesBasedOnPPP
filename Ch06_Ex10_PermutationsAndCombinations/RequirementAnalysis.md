## Requirements
The requirement that I identified in the assignment are:

_Design a program that_
_1. asks users for two numbers,_
_2. asks them whether they want to calculate permutations or combinations,_
_3. and prints out the result._

## Requirement Analysis

### 1. asks users for two numbers
The factorial operator is mathematically defined only for positive integer numbers.
-> The user should be informed that only positive integer numbers are allowed.
Factorials grow quickly, so that certain numbers cannot be calculated because of the data type sizes. 
-> Therefore, a limit needs to be set for the imput numbers (e.g. less than 1000)
The user will be asked specifically to enter "a" or "b", to increase user friendliness.

### 2. asks them whether they want to calculate permutations or combinations
The user should be informed about what permutations and combinations are.
-> The user should have an option to abort the process and exit the application at this step.
-> The user will be given a choice of two characters to decide what should be calculated.

### 3. and prints out the result.
The input should be printed.
The choice of permutation or combination should be printed.
The calculated result should be printed. 

## Exact steps of the program
The program should inform well the user, and most importantly calculate the correct results.
In order to do so, a first draft is: 
1. Prompt and info to the user about the program and its purposes/calculations.
1.1. Prompt the limitations of the program, too.
2. Request the input parameters "a", and "b" from the user.
2.1. First, request the "a" parameter 
2.2. Second, request the "b" parameter
2.3. Return an error if "a" or "b" violate the boundary conditions.
3. Request the calculation that should be performed - permutation or combination?
3.1. Allow to enter "c" for combination, or "p" for permutation, or abort with "x"
3.2. Return to 3.1. if requested calculation does not fit the accepted options.
4. Calculate the requested function
5. Prompt the output of the functions
5.1. For a better usability, also prompt the numbers "a", and "b", and the requested method.
5.2. Prompt the actual result.
6. Ask if a new calculation is desired.
6.1. If "no", then close the application
6.2. If "yes", then restart the input parameter reading.