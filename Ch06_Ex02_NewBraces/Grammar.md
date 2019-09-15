# Grammar
The original grammar for the basic mathematical operations can be found on page 189 in the book.
As stated in exercise 6.2, the factorial operator binds stronger than multiplication, division or modulo(%). This means that the factorial operator does not fall into one of the existing categories (Expression, Term, Primary, etc.).
Consequently, a new category needs to be created. The newly created category Factorial needs to be connected within the grammar to the "upper" and to the "lower" categories. Since the factorial operator is applied to a number, 
a Primary, followed by a "!"  is a Factorial. In the default case, it is a Primary, so the link to the lower category is performed. If the change of grammar would stop at this point, the consequence is that the factorial operator 
could NOT be used in the calculator, because there would be no call from an "upper" category. This is why Factorial has to become part of Term.
One consequence from this exercise is that the abstraction of a problem is the core of every solution.

- Expression:
-- Term
-- Expression "+" Term // addition
-- Expression "–" Term // subtraction
- Term:
-- Factorial
-- Term "*" Primary // multiplication
-- Term "/" Primary // division
-- Term "%" Primary // remainder (modulo)
- Factorial:
-- Primary
-- Primary "!"
- Primary:
-- Number
-- "(" Expression ")" // grouping
-Number:
-- floating-point-literal