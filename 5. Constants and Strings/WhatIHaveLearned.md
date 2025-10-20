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


## The constexpr keyword

Fortunately, we can enlist the compiler’s help to ensure we get a compile-time constant variable where we desire one. To do so, we use the constexpr keyword (which is shorthand for “constant expression”) instead of const in a variable’s declaration. A constexpr variable is always a compile-time constant. As a result, a constexpr variable must be initialized with a constant expression, otherwise a compilation error will result.

```cpp
#include <iostream>

// The return value of a non-constexpr function is not constexpr
int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr

    return 0;
}
```

## The meaning of const vs constexpr for variables

For variables:

    const means that the value of an object cannot be changed after initialization. The value of the initializer may be known at compile-time or runtime. The const object can be evaluated at runtime.
    constexpr means that the object can be used in a constant expression. The value of the initializer must be known at compile-time. The constexpr object can be evaluated at runtime or compile-time.

Constexpr variables are implicitly const. Const variables are not implicitly constexpr (except for const integral variables with a constant expression initializer). Although a variable can be defined as both constexpr and const, in most cases this is redundant, and we only need to use either const or constexpr.

Unlike const, constexpr is not part of an object’s type. Therefore a variable defined as constexpr int actually has type const int (due to the implicit const that constexpr provides for objects).

![Recap of constants](recap-of-consntat.png)

## A brief introduction to constexpr functions

A constexpr function is a function that can be called in a constant expression. A constexpr function must evaluate at compile-time when the constant expression it is part of must evaluate at compile time (e.g. in the initializer of a constexpr variable). Otherwise, a constexpr function may be evaluated at either compile-time (if eligible) or runtime. To be eligible for compile-time execution, all arguments must be constant expressions.

To make a constexpr function, the constexpr keyword is placed in the function declaration before the return type:

```cpp
#include <iostream>

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int m1 { max(5, 6) };            // ok
    const int m2 { max(5, 6) };      // ok
    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
    const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time

    return 0;
}
```
## std::string vs std::string_view

## Introducing std::string

The easiest way to work with strings and string objects in C++ is via the std::string type, which lives in the <string> header.

We can create objects of type std::string just like other objects:

```cpp
#include <string> // allows use of std::string

int main()
{
    std::string name {}; // empty string

    return 0;
}
```

Just like normal variables, you can initialize or assign values to std::string objects as you would expect:

```cpp
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    name = "John";               // change name to "John"

    return 0;
}
```

## String length:

Name is initialized with the string "Alex", which contains five characters (four explicit characters and a null-terminator). We then set name to a larger string, and then a smaller string. std::string has no problem handling this! You can even store really long strings in a std::string.

This is one of the reasons that std::string is so powerful.

## String input with std::cin

Using std::string with std::cin may yield some surprises! Consider the following example:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

Output:

```plaintext
Enter your full name: John Doe
Enter your favorite color: Your name is John and your favorite color is Doe
```

Hmmm, that isn’t right! What happened? It turns out that when using operator>> to extract a string from std::cin, operator>> only returns characters up to the first whitespace it encounters. Any other characters are left inside std::cin, waiting for the next extraction.

## Use std::getline() to input text

To read a full line of input into a string, you’re better off using the std::getline() function instead. std::getline() requires two arguments: the first is std::cin, and the second is your string variable.

```cpp
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

```plaintext
Enter your full name: John Doe
Enter your favorite color: blue
Your name is John Doe and your favorite color is blue
```

## What the heck is std::ws?

In lesson 4.8 -- Floating point numbers, we discussed output manipulators, which allow us to alter the way output is displayed. In that lesson, we used the output manipulator function std::setprecision() to change the number of digits of precision that std::cout displayed.

C++ also supports input manipulators, which alter the way that input is accepted. **The std::ws input manipulator tells std::cin to ignore any leading whitespace before extraction.** Leading whitespace is any whitespace character (spaces, tabs, newlines) that occur at the start of the string.


Consider the following:


```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

Output:

```plaintext
Pick 1 or 2: 2
Now enter your name: Hello, , you picked 2
```

This program first asks you to enter 1 or 2, and waits for you to do so. All good so far. Then it will ask you to enter your name. However, it won’t actually wait for you to enter your name! Instead, it prints the “Hello” string, and then exits.

When you enter a value using operator>>, std::cin not only captures the value, it also captures the newline character ('\n') that occurs when you hit the enter key. So when we type 2 and then hit enter, std::cin captures the string "2\n" as input. It then extracts the value 2 to variable choice, leaving the newline character behind for later. Then, when std::getline() goes to extract text to name, it sees "\n" is already waiting in std::cin, and figures we must have previously entered an empty string! Definitely not what was intended.

We can amend the above program to use the std::ws input manipulator, to tell std::getline() to ignore any leading whitespace characters:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

Output:
```plaintext
Pick 1 or 2: 2
Now enter your name: Alex
Hello, Alex, you picked 2
```

## Length of a string:

Use length() function.

```cpp
text.length(); //Excluding the null terminator.
```

Also note that std::string::length() returns an unsigned integral value (most likely of type size_t). If you want to assign the length to an int variable, you should static_cast it to avoid compiler warnings about signed/unsigned conversions:

```cpp
int length { static_cast<int>(name.length()) };
```

**Note**: Do not pass std::string by value, as it makes an expensive copy.

In most other cases, prefer to avoid returning a std::string by value, as doing so will make an expensive copy.



## Literals for std::string

Double-quoted string literals (like “Hello, world!”) are C-style strings by default (and thus, have a strange type).

We can create string literals with type std::string by using a s suffix after the double-quoted string literal. The s must be lower case.


```cpp
#include <iostream>
#include <string> // for std::string

int main()
{
    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;
}
```

**Reminder**: We need to be careful not to mix signed and unsigned values. std::string::length() returns an unsigned value. If you’re C++20 capable, use std::ssize() to get the length as a signed value. Otherwise, static_cast the return value of std::string::length() to an int.


## Initializing std::string is slow. (Since it does copy the variable)

```cpp
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    printString(s);

    return 0;
}
```
This example makes two copies of the C-style string “Hello, world!”: one when we initialize s in main(), and another when we initialize parameter str in printString(). **That’s a lot of needless copying just to print a string!**

## std::string_view

To address the issue with std::string being expensive to initialize (or copy), C++17 introduced std::string_view (which lives in the <string_view> header). std::string_view provides read-only access to an existing string (a C-style string, a std::string, or another std::string_view) without making a copy. Read-only means that we can access and use the value being viewed, but we can not modify it.

The following example is identical to the prior one, except we’ve replaced std::string with std::string_view.

```cpp
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```

When we initialize std::string_view s with C-style string literal "Hello, world!", s provides read-only access to “Hello, world!” without making a copy of the string. When we pass s to printSV(), parameter str is initialized from s. This allows us to access “Hello, world!” through str, again without making a copy of the string.


## std::string_view can be initialized with many different types of strings

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view s1 { "Hello, world!" }; // initialize with C-style string literal
    std::cout << s1 << '\n';

    std::string s{ "Hello, world!" };
    std::string_view s2 { s };  // initialize with std::string
    std::cout << s2 << '\n';

    std::string_view s3 { s2 }; // initialize with std::string_view
    std::cout << s3 << '\n';

    return 0;
}
```

## std::string_view parameters will accept many different types of string arguments

Function definitions:

```cpp
void printSV(std::string_view str)
```

Usage:

```cpp
printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view
```

## std::string_view will not implicitly convert to std::string

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printString(std::string str)
{
	std::cout << str << '\n';
}

int main()
{
	std::string_view sv{ "Hello, world!" };

	// printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string

	std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string

	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

	return 0;
}
```

## Assignment changes what the std::string_view is viewing

Assigning a new string to a std::string_view causes the std::string_view to view the new string. It does not modify the prior string being viewed in any way.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string name { "Alex" };
    std::string_view sv { name }; // sv is now viewing name
    std::cout << sv << '\n'; // prints Alex

    sv = "John"; // sv is now viewing "John" (does not change name)
    std::cout << sv << '\n'; // prints John

    std::cout << name << '\n'; // prints Alex

    return 0;
}
```
But da fuq? I just said string_view is readonly. Yes they are, you cannot change the string_view's content. by sv[0] = "A". Impossible.

Check this example:

string name = "Alex"

Now name is looking for Alex; name -> Alex.
then:

string_view sv = name;

Then string_view is also looking for Alex. Which is the same string.

name -> & sv -> Alex.

But when ever you do sv = "Kaan"
Now, it looks seperate data.

sv -> "Kaan"
whereas 
name -> "Alex"

## Literals for std::string_view

Double-quoted string literals are C-style string literals by default. We can create string literals with type std::string_view by using a sv suffix after the double-quoted string literal. The sv must be lower case.


```cpp
#include <iostream>
#include <string>      // for std::string
#include <string_view> // for std::string_view

int main()
{
    using namespace std::string_literals;      // access the s suffix
    using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    return 0;
}
```


## Destruction of viewer while owner is destroyed or moved. ??

## Warning:

It is important to note that a std::string_view remains dependent on the initializer through its lifetime. If the string being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.

Whenever we use a view, it is up to us to ensure these possibilities do not occur.

Example:
```cpp

std::string dangerousFunction(){
    std::string x = "....'.. ........."
    return x;
}

int main(){
    std::string_view sv = dangerousFunction();

    std::cout << sv << std::endl;
    return 0;
}
```

## std::string_view is best used as a read-only function parameter

The best use for std::string_view is as a read-only function parameter. This allows us to pass in a C-style string, std::string, or std::string_view argument without making a copy, as the std::string_view will create a view to the argument.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str) // now a std::string_view, creates a view of the argument
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```

## Should I prefer std::string_view or const std::string& function parameters? Advanced

Prefer std::string_view in most cases. We cover this topic further in lesson 12.6 -- Pass by const lvalue reference.


## Do not initialize a std::string_view with a std::string literal, as this will leave the std::string_view dangling.

It is okay to initialize a std::string_view with a C-style string literal or a std::string_view literal. It’s also okay to initialize a std::string_view with a C-style string object, a std::string object, or a std::string_view object, as long as that string object outlives the view.

We can also get undefined behavior when the underlying string is modified:

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, a!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    return 0;
}
```

## Revalidating an invalid std::string_view



```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, universe!"

    return 0;
}
```


## Be careful returning a std::string_view


std::string_view can be used as the return value of a function. However, this is often dangerous.

Because local variables are destroyed at the end of the function, returning a std::string_view that is viewing a local variable will result in the returned std::string_view being invalid, and further use of that std::string_view will result in undefined behavior. For example:

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view getBoolName(bool b)
{
    std::string t { "true" };  // local variable
    std::string f { "false" }; // local variable

    if (b)
        return t;  // return a std::string_view viewing t

    return f; // return a std::string_view viewing f
} // t and f are destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    return 0;
}
```

In the above example, when getBoolName(true) is called, the function returns a std::string_view that is viewing t. However, t is destroyed at the end of the function. This means the returned std::string_view is viewing an object that has been destroyed. So when the returned std::string_view is printed, undefined behavior results.

Your compiler may or may not warn you about such cases.

There are two main cases where a std::string_view can be returned safely. First, because C-style string literals exist for the entire program, it’s fine (and useful) to return C-style string literals from a function that has a return type of std::string_view.

```cpp
#include <iostream>
#include <string_view>

std::string_view getBoolName(bool b)
{
    if (b)
        return "true";  // return a std::string_view viewing "true"

    return "false"; // return a std::string_view viewing "false"
} // "true" and "false" are not destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // ok

    return 0;
}
```

When getBoolName(true) is called, the function will return a std::string_view viewing the C-style string "true". Because "true" exists for the entire program, there’s no problem when we use the returned std::string_view to print "true" within main().

Second, it is generally okay to return a function parameter of type std::string_view:


```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
{
    if (s1 < s2)
        return s1;
    return s2;
}

int main()
{
    std::string a { "World" };
    std::string b { "Hello" };

    std::cout << firstAlphabetical(a, b) << '\n'; // prints "Hello"

    return 0;
}
```

## View modification functions


Consider a window in your house, looking at an electric car sitting on the street. You can look through the window and see the car, but you can’t touch or move the car. Your window just provides a view to the car, which is a completely separate object.

Many windows have curtains, which allow us to modify our view. We can close either the left or right curtain to reduce what we can see. We don’t change what’s outside, we just reduce the visible area.

Because std::string_view is a view, it contains functions that let us modify our view by “closing the curtains”. This does not modify the string being viewed in any way, just the view itself.

    The remove_prefix() member function removes characters from the left side of the view.
    The remove_suffix() member function removes characters from the right side of the view.



```cpp
#include <iostream>
#include <string_view>

int main()
{
	std::string_view str{ "Peach" };
	std::cout << str << '\n';

	// Remove 1 character from the left side of the view
	str.remove_prefix(1);
	std::cout << str << '\n';

	// Remove 2 characters from the right side of the view
	str.remove_suffix(2);
	std::cout << str << '\n';

	str = "Peach"; // reset the view
	std::cout << str << '\n';

	return 0;
}
```

Output:

```plaintext
Peach
each
ea
Peach
```

Note that: A C-style string literal and a std::string are always null-terminated.
A std::string_view may or may not be null-terminated.

In almost all cases, this doesn’t matter -- a std::string_view keeps track of the length of the string or substring it is viewing, so it doesn’t need the null-terminator. Converting a std::string_view to a std::string will work regardless of whether or not the std::string_view is null-terminated.


## A quick guide on when to use std::string vs std::string_view

This guide is not meant to be comprehensive, but is intended to highlight the most common cases:


Variables

Use a std::string variable when:

    You need a string that you can modify.
    You need to store user-inputted text.
    You need to store the return value of a function that returns a std::string.

Use a std::string_view variable when:

    You need read-only access to part or all of a string that already exists elsewhere and will not be modified or destroyed before use of the std::string_view is complete.
    You need a symbolic constant for a C-style string.
    You need to continue viewing the return value of a function that returns a C-style string or a non-dangling std::string_view.

Function parameters

Use a std::string function parameter when:

    The function needs to modify the string passed in as an argument without affecting the caller. This is rare.
    You are using language standard C++14 or older and aren’t comfortable using references yet.

For advanced readers

Also see 12.6 -- Pass by const lvalue reference.

Use a const std::string& function parameter when:

    You are using language standard C++14 or older, and the function needs a read-only string to work with (as std::string_view is not available until C++17).
    You are calling other functions that require a const std::string, const std::string&, or const C-style string (as std::string_view may not be null-terminated).

Use a std::string& function parameter when:

    You are using a std::string as an out-parameter (see 12.13 -- In and out parameters).
    You are calling other functions that require a std::string&, or non-const C-style string.

Return types

Use a std::string return type when:

    The return value is a std::string local variable or function parameter.
    The return value is a function call or operator that returns a std::string by value.

Use a std::string_view return type when:

    The function returns a C-style string literal or local std::string_view that has been initialized with a C-style string literal.
    The function returns a std::string_view parameter.

For advanced readers

See lesson 12.12 -- Return by reference and return by address for more information on returning reference types.

Use a std::string_view return type when:

    Writing an accessor for a std::string_view member.

Use a std::string& return type when:

    The function returns a std::string& parameter.

Use a const std::string& return type when:

    The function returns a const std::string& parameter.
    Writing an accessor for a std::string or const std::string member.
    The function returns a static (local or global) const std::string.

Insights

Things to remember about std::string:

    Initializing and copying std::string is expensive, so avoid this as much as possible.
    Avoid passing std::string by value, as this makes a copy.
    If possible, avoid creating short-lived std::string objects.
    Modifying a std::string will invalidate any views to that string.
    It is okay to return a local std::string by value.

Things to remember about std::string_view:

    std::string_view is typically used for passing string function parameters and returning string literals.
    Because C-style string literals exist for the entire program, it is always okay to set a std::string_view to a C-style string literal.
    When a string is destroyed, all views to that string are invalidated.
    Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
    A std::string_view may or may not be null-terminated.

TODO: REVIEW STRING_VIEWERS. C-STYLE STRINGS AND STRING LITERALS.