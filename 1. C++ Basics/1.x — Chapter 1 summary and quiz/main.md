Summary:

A **statement** is a type of instruction that causes the program to perform some action.

A function is a **collection of statements** that execute sequentially.

Copy assignment (via operator=) can be used to assign an already created variable a value.

The process of specifying an initial value for an object is called **initialization**, and the syntax used to initialize an object is called an initializer.

Default-initialization	int x;	In most cases, leaves variable with indeterminate value
Copy-initialization	int x = 5;
Direct-initialization	int x ( 5 );
Direct-list-initialization	int x { 5 };	Narrowing conversions disallowed
Copy-list-initialization	int x = { 5 };	Narrowing conversions disallowed
Value-initialization	int x {};	Usually performs zero-initialization

**Unary** operators take one operand. **Binary** operators take two operands, often called left and right. **Ternary** operators take three operands. **Nullary** operators take zero operands.

An **expression is a sequence of literals, variables, operators, and function calls that are evaluated to produce a single output value.** The calculation of this output value is called **evaluation**. The value produced is the result of the expression.

An expression statement is an expression that has been turned into a statement by placing a semicolon at the end of the expression.