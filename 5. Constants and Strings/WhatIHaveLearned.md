## consts?

In programming, a constant is a value that may not be changed during the program’s execution.

    1. Named constants are constant values that are associated with an identifier. These are also sometimes called symbolic constants.
    2. Literal constants are constant values that are not associated with an identifier.


## Ways to declare a constant:

There are three ways to define a named constant in C++:

    Constant variables (covered in this lesson).
    Object-like macros with substitution text (introduced in lesson 2.10 -- Introduction to the preprocessor, with additional coverage in this lesson).
    Enumerated constants (covered in lesson 13.2 -- Unscoped enumerations).

```cpp
const double gravity { 9.8 };  // preferred use of const before type
int const sidesInSquare { 4 }; // "east const" style, okay but not preferred
```

Programmers who have transitioned from C often prefer underscored, upper-case names for const variables (e.g. EARTH_GRAVITY). More common in C++ is to use intercapped names with a ‘k’ prefix (e.g. kEarthGravity).

## Function can return const type of data.

```cpp
#include <iostream>

const int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue() << '\n';

    return 0;
}
```

Note: This is not important since primitive types will copied.

## Nomenclature: type qualifiers

A type qualifier (sometimes called a qualifier for short) is a keyword that is applied to a type that modifies how that type behaves. The const used to declare a constant variable is called a const type qualifier (or const qualifier for short).

As of C++23, C++ only has two type qualifiers: const and volatile.

Optional reading

The volatile qualifier is used to tell the compiler that an object may have its value changed **at any time**. This rarely-used qualifier disables certain types of optimizations.


## Literal types:

Literal type in compiler | value in real life
int | int
double | float

## String literals are they primitive?

Because strings are commonly used in programs, most modern programming languages include a fundamental string data type. For historical reasons, strings are not a fundamental type in C++.

All C-style string literals have an implicit null terminator. Consider a string such as "hello". While this C-style string appears to only have five characters, it actually has six: 'h', 'e', 'l‘, 'l', 'o', and '\0' (a character with ASCII code 0). This trailing ‘\0’ character is a special character called a null terminator, and it is used to indicate the end of the string.

For advanced readers

This is the reason the string "Hello, world!" has type const char[14] rather than const char[13] -- the hidden null terminator counts as a character.

## Octalls:

To use an octal literal, prefix your literal with a 0 (zero):

```cpp
#include <iostream>

int main()
{
    int x{ 012 }; // 0 before the number means this is octal
    std::cout << x << '\n';
    return 0;
}
```

## Hexadecimals:

To use a hexadecimal literal, prefix your literal with 0x:

```cpp
#include <iostream>

int main()
{
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    std::cout << x << '\n';
    return 0;
}
```

## Binaries: 

We can use binary literals by using the 0b prefix:

```cpp
#include <iostream>

int main()
{
    int bin{};        // assume 16-bit ints
    bin = 0b1;        // assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;     // assign binary 0000 0000 0000 1010 to the variable
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    return 0;
}
```

## Digit seperator:

Digit separators are ' in CPP:

```cpp
#include <iostream>

int main()
{
    int bin { 0b1011'0010 };  // assign binary 1011 0010 to the variable
    long value { 2'132'673'462 }; // much easier to read than 2132673462

    return 0;
}
```

## Outputting values in decimal, octal, or hexadecimal

```cpp
#include <iostream>

int main()
{
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal

    return 0;
}
```

```plaintext
12
c
c
14
12
12
```

## Outputting values in binary

Outputting values in binary is a little harder, as std::cout doesn’t come with this capability built-in. Fortunately, the C++ standard library includes a type called std::bitset that will do this for us (in the <bitset> header).


To use std::bitset, we can define a std::bitset variable and tell std::bitset how many bits we want to store. The number of bits must be a compile-time constant. std::bitset can be initialized with an integral value (in any format, including decimal, octal, hex, or binary).

```cpp
#include <bitset> // for std::bitset
#include <iostream>

int main()
{
	// std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

	return 0;
}
```

```plaintext
11000101
11000101
1010
```


## Outputting values in binary using the Format / Print Library Advanced

In C++20 and C++23, we have better options for printing binary via the new Format Library (C++20) and Print Library (C++23):

```cpp
#include <format> // C++20
#include <iostream>
#include <print> // C++23

int main()
{
    std::cout << std::format("{:b}\n", 0b1010);  // C++20, {:b} formats the argument as binary digits
    std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

    std::println("{:b} {:#b}", 0b1010, 0b1010);  // C++23, format/print two arguments (same as above) and a newline

    return 0;
}
```

```plaintext
1010
0b1010
1010 0b1010
```


## Constant folding

One of the original forms of compile-time evaluation is called “constant folding”. Constant folding is an optimization technique where the compiler replaces expressions that have literal operands with the result of the expression. Using constant folding, the compiler would recognize that the expression 3 + 4 has constant operands, and then replace the expression with the result 7.

The result would be equivalent to the following:
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```
This program produces the same output (7) as the prior version, but the resulting executable no longer needs to spend CPU cycles calculating 3 + 4 at runtime!

Constant folding can also be applied to subexpressions, even when the full expression must execute at runtime.

## Constant propagation
The following program contains another optimization opportunity:


```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```

When x is initialized, the value 7 will be stored in the memory allocated for x. Then on the next line, the program will go out to memory again to fetch the value 7 so it can be printed. This requires two memory access operations (one to store the value, and one to fetch it).

Constant propagation is an optimization technique where the compiler replaces variables known to have constant values with their values. Using constant propagation, the compiler would realize that x always has the constant value 7, and replace any use of variable x with the value 7.

The result would be equivalent to the following:

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << 7 << '\n';

	return 0;
}
```

## Dead code elimination

Name implies what it is.

## Const variables are easier to optimize

```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
``` 

X should be const.
```cpp
const int x {7};
```


## Optimization can make programs harder to debug

When the compiler optimizes a program, the result is that variables, expressions, statements, and function calls may be rearranged, modified, replaced, or removed entirely. Such changes can make it hard to debug a program effectively.


## Nomenclature: Compile-time constants vs runtime constants

Constants in C++ are sometimes divided into two informal categories.

A compile-time constant is a constant whose value is known at compile-time. Examples include:

    Literals.
    Constant objects whose initializers are compile-time constants.

A runtime constant is a constant whose value is determined in a runtime context. Examples include:

    Constant function parameters.
    Constant objects whose initializers are non-constants or runtime constants.

For example:

```cpp
#include <iostream>

int five()
{
    return 5;
}

int pass(const int x) // x is a runtime constant
{
    return x;
}

int main()
{
    // The following are non-constants:
    [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value isn't known until runtime

    return 0;
}
```

## Keyword constexpr


```cpp
const double x { 1.2 };
const double y { 3.4 };
const double z { x + y }; // x + y may evaluate at runtime or compile-time
```

The expression x + y would normally evaluate at runtime, but since the value of x and y are known at compile-time, the compiler may opt to perform compile-time evaluation instead and initialize z with the compile-time calculated value 4.6.

Indicate that an expression that must be evaluatable at compile-time.

The key difference is that in a constant expression, each part of the expression must be evaluatable at compile-time.

In a few other cases, the C++ language requires an expression that can be evaluated at compile-time. For example, constexpr variables require an initializer that can be evaluated at compile-time:


```cpp
int main()
{
    constexpr int x { expr }; // Because variable x is constexpr, expr must be evaluatable at compile-time
}
```

In cases where a constant expression is required but one is not provided, the compiler will error and halt compilation.

We’ll discuss constexpr variables in the next lesson (5.6 -- Constexpr variables), when we cover constexpr variables.

## Compile time benefits:

o improve upon this situation, the C++ language provides ways for us to be explicit about what parts of code we want to execute at compile-time. The use of language features that result in compile-time evaluation is called compile-time programming.

These features can help improve software in a number of areas:

    Performance: Compile-time evaluation makes our programs smaller and faster. The more code we can ensure is capable of evaluating at compile-time, the more performance benefit we’ll see.
    Versatility: We can always use such code in places that require a compile-time value. Code that relies on the as-if rule to evaluate at compile-time can’t be used in such places (even if the compiler opts to evaluate that code at compile-time) -- this decision was made so that code that compiles today won’t stop compiling tomorrow, when the compiler decides to optimize differently.
    Predictability: We can have the compiler halt compilation if it determines that code cannot be executed at compile-time (rather than silently opting to have that code evaluate at runtime instead). This allows us to ensure a section of code we really want to execute at compile-time will.
    Quality: We can have the compiler reliably detect certain kinds of programming errors at compile-time, and halt the build if it encounters them. This is much more effective than trying to detect and gracefully handle those same errors at runtime.
    Quality: Perhaps most importantly, undefined behavior is not allowed at compile-time. If we do something that causes undefined behavior at compile-time, the compiler should halt the build and ask us to fix it. Note that this is a hard problem for compilers, and they may not catch all cases.


The following C++ features are the most foundational to compile-time programming:

    Constexpr variables (discussed in upcoming lesson 5.6 -- Constexpr variables).
    Constexpr functions (discussed in upcoming lesson F.1 -- Constexpr functions).
    Templates (introduced in lesson 11.6 -- Function templates).
    static_assert (discussed in lesson 9.6 -- Assert and static_assert).

All of these features have one thing in common: they make use of constant expressions.

## What can be in a constant expression?

In technical terms, constant expressions are quite complex. In this section, we’ll go into a little bit deeper into what they can and can’t contain. You do not need to remember most of this. If a constant expression is required somewhere and you do not provide one, the compiler will happily point out your mistake, and you can fix it at that point.

Most commonly, constant expressions contain the following:

    Literals (e.g. ‘5’, ‘1.2’)
    Most operators with constant expression operands (e.g. 3 + 4, 2 * sizeof(int)).
    Const integral variables with a constant expression initializer (e.g. const int x { 5 };). This is a historical exception -- in modern C++, constexpr variables are preferred.
    Constexpr variables (discussed in upcoming lesson 5.6 -- Constexpr variables).
    Constexpr function calls with constant expression arguments (see F.1 -- Constexpr functions).


Constant expressions can also contain:

    Non-type template parameters (see 11.9 -- Non-type template parameters).
    Enumerators (see 13.2 -- Unscoped enumerations).
    Type traits (see the cppreference page for type traits).
    Constexpr lambda expressions (see 20.6 -- Introduction to lambdas (anonymous functions)).


Notably, the following cannot be used in a constant expression:

    Non-const variables.
    Const non-integral variables, even when they have a constant expression initializer (e.g. const double d { 1.2 };). To use such variables in a constant expression, define them as constexpr variables instead (see lesson 5.6 -- Constexpr variables).
    The return values of non-constexpr functions (even when the return expression is a constant expression).
    Function parameters (even when the function is constexpr).
    Operators with operands that are not constant expressions (e.g. x + y when x or y is not a constant expression, or std::cout << "hello\n" as std::cout is not a constant expression).
    Operators new, delete, throw, typeid, and operator, (comma).

An expression containing any of the above is a runtime expression.

## Examples of constant and non-constant expressions
```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```

## When constant expressions are evaluated at compile-time

Since constant expressions are always capable of being evaluated at compile-time, you may have assumed that constant expressions will always be evaluated at compile-time. Counterintuitively, this is not the case.

The compiler is only required to evaluate constant expressions at compile-time in contexts that **require** a constant expression.


The technical name for an expression that must be evaluated at compile-time is a manifestly constant-evaluated expression. You will likely only encounter this term in technical documentation.

## The likelihood that an expression is fully evaluated at compile-time can be categorized as follows:

    Never: A non-constant expression where the compiler is not able to determine all values at compile-time.
    Possibly: A non-constant expression where the compiler is able to determine all values at compile-time (optimized under the as-if rule).
    Likely: A constant expression used in a context that does not require a constant expression.
    Always: A constant expression used in a context that requires a constant expression.

## So why doesn’t C++ require all constant expressions to be evaluated at compile-time? There are at least two good reasons:

    1.Compile-time evaluation makes debugging harder. If our code has a buggy calculation that is evaluated at compile-time, we have limited tools to diagnose the issue. Allowing non-required constant expressions to be evaluated at runtime (typically when optimizations are turned off) enables runtime debugging of our code. Being able to step through and inspect the state of our programs while they are running can make finding bugs easier.
    
    2. To provide the compiler with the flexibility to optimize as it sees fit (or as influenced by compiler options). For example, a compiler might want to offer an option that defers all non-required constant expression evaluation to runtime, in order to improve compile times for developers.
