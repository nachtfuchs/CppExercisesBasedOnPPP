## Questions: 
1. What is a "prefix unary operator?
2. What does the complement operator do?

# Logical Operator Grammar
The first idea is to create the grammar from the tightest binding to the most loose binding.
Simple thing: we need numbers., because they can exist as themselves and "bind the tightest":
The next simple thing are the unary operators which bind tight.
The 'and' operator binds the tightest in between the binary logical operators.
Remember to make a connection between the different levels of grammar. If not, the "state machine of 
logical operations" will have a dead lock.
 
## Grammar for logical operations
- Expression:
-- HigherTerm 
-- Expression "|" HigherTerm // Or
- HigherTerm:
-- Term "^" Term	// Exclusive or
-- Term
- Term:
-- Unary "&" Unary	// And
-- Unary
- Unary:
-- !Primary	// Not
-- ~Primary	// complement
-- Primary
- Primary:
-- Number
-- '(' Expression ')'
- Number:
-- integer literal