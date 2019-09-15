#Pseudo-Code
The following should represent a pseudo-code for chapter 6 Exercise 10,
based on the RequirementAnalysis.md-file.

## Overall program
```
Prompt application info.
Prompt boundary conditions for the inputs.

Read user input a
	save a
Read user input b
	save b
boundaryCondition(a, b)
	if boundaryCondition(a, b) == invalid
		Request inputs a and b again
Read requested calculation method: (c)ombination, (p)ermutation, e(x)it
	save requested calcMeth
checkReqMeth( userRequest)
	if checkReqMeth == invalid
		Request calculation method again
If (p)ermutation == true
	calculate (a!)/((a-b)!)
	return permutation result
If (c)ombination == true
	calculate permutation()
	calculate b!
	return combination result
Prompt the identified inputs a, b; 
	prompt the identified method; 
	prompt the method result
Ask user if new calculation should be started
if newCalc == true
	restart by reading user input a, b
if newCalc == false
	exit the application
```

## boundaryCondition(a, b)
This function checks if "a" and "b" fulfill the boundary conditions to calculate
permutation or combination

```
isInteger(a) == false or isInteger(b) == false
	prompt error(Only integer numbers are allowed)
if a < 0 or b < 0
	prompt error(Only positive numbers are allowed.)
if a > maxInput
	prompt error(Please enter a number, smaller than maxInput.)
if a < b
	prompt error(Input a is smaller than input b. Factorial operator cannot be performed on negative numbers)
```

## checkReqMeth(userRequest)
This function checks whether the requested calculation fits one of the offered options.

```
if userRequest != c or userRequest != p or userReqest != x
	prompt error(Requested method is unknown)
```