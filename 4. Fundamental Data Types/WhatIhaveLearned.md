## Memory Addresses:

Each memory address refers to a 1 byte. A byte is a group of bits that are operated on as a unit. The modern standard is that a byte is comprised of 8 sequential bits. But byte do not have to consist of 8 bits.

## Fundamental data types

![Fundamental Data Types](fundamental-data-types.png)

## Other set of types:

C++ contains three sets of types.

The first two are built-in to the language itself (and do not require the inclusion of a header to use):

    1. The “fundamental data types” provide the most the basic and essential data types.
    2. The “compound data types” provide more complex data types and allow for the creation of custom (user-defined) types. We cover these in lesson 12.1 -- Introduction to compound data types.

    3. The third (and largest) set of types is provided by the C++ standard library. Because the standard library is included in all C++ distributions, these types are broadly available and have been standardized for compatibility. Use of the types in the standard library requires the inclusion of the appropriate header and linking in the standard library.


## The _t suffix

Many of the types defined in newer versions of C++ (e.g. std::nullptr_t) use a _t suffix. This suffix means “type”, and it’s a common nomenclature applied to modern types.

If you see something with a _t suffix, it’s probably a type. But many types don’t have a _t suffix, so this isn’t consistently applied.


## Void type

Void is the easiest of the data types to explain. Basically, void means “no type”!

Void is our first example of an incomplete type. An incomplete type is a type that has been declared but not yet defined.

## Data storage size of fundemental types:

    An object must occupy at least 1 byte (so that each object has a distinct memory address).
    A byte must be at least 8 bits.
    The integral types char, short, int, long, and long long have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
    char and char8_t are exactly 1 byte (at least 8 bits).

![Size table](size-of-each-fundemental-data-type.png)

## The sizeof operator


In order to determine the size of data types on a particular machine, C++ provides an operator named sizeof. The sizeof operator is a unary operator that takes either a type or a variable, and returns the size of an object of that type (in bytes). You can compile and run the following program to find out how large some of your data types are:

```cpp
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT

int main()
{
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

    std::cout << std::left; // left justify output

    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
    std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
    std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
    std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
    std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
    std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
    std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

    return 0;
}
```

Output on my machine is:

```plaintext
A byte is 8 bits

bool:           1 bytes
char:           1 bytes
short:          2 bytes
int:            4 bytes
long:           8 bytes
long long:      8 bytes
float:          4 bytes
double:         8 bytes
long double:    16 bytes
```

Note: sizeof does not include dynamically allocated memory used by an object. We discuss dynamic memory allocation in a future lesson.

## Signed integer ranges:

Signed integer ranges

As you learned in the last section, a variable with n bits can hold 2n possible values. But which specific values? We call the set of specific values that a data type can hold its range. The range of an integer variable is determined by two factors: its size (in bits), and whether it is signed or not.

For example, an 8-bit signed integer has a range of -128 to 127. This means an 8-bit signed integer can store any integer value between -128 and 127 (inclusive) safely.

Here’s a table containing the range of signed integers of different sizes:

![Range table](size-of-each-bit-range.png)

## Division In C++

When doing division with two integers (called integer division), C++ always produces an integer result. Since integers can’t hold fractional values, any fractional portion is simply dropped (not rounded!).

```cpp
#include <iostream>

int main()
{
    std::cout << 8 / 5 << '\n';
    return 0;
}
```