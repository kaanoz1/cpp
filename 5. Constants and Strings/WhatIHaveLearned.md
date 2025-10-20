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

