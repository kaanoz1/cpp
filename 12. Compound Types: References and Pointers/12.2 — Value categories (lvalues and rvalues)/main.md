## lvalue?

Before we talk about our first compound type (lvalue references), we’re going to take a little detour and talk about what an lvalue is.

## The value category of an expression

Now consider the following program:

int main()
{
    int x{};

    x = 5; // valid: we can assign 5 to x
    5 = x; // error: can not assign value of x to literal value 5

    return 0;
}

One of these assignment statements is valid (assigning value 5 to variable x) and one is not (what would it mean to assign the value of x to the literal value 5?). So how does the compiler know which expressions can legally appear on either side of an assignment statement?

The answer lies in the second property of expressions: the value category. The value category of an expression (or subexpression) indicates whether an expression resolves to a value, a function, or an object of some kind.

Prior to C++11, there were only two possible value categories: lvalue and rvalue.

## Lvalues

An lvalue (pronounced “ell-value”, short for “left value” or “locator value”, and sometimes written as “l-value”) is an expression that evaluates to an identifiable object or function (or bit-field).

```cpp
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}

```
In the above program, the expression x is an lvalue expression as it evaluates to variable x (which has an identifier).

## What about a rvalue?


An rvalue (pronounced “arr-value”, short for “right value”, and sometimes written as r-value) is an expression that is not an lvalue. Rvalue expressions evaluate to a value.

Example:

```cpp
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```

### Key insight

Lvalue expressions evaluate to an identifiable object.
Rvalue expressions evaluate to a value.

So it meant that r values are evaluated value. What about this one?

```cpp
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```

In cases where an rvalue is expected but an lvalue is provided, the lvalue will undergo an lvalue-to-rvalue conversion so that it can be used in such contexts. This basically means the lvalue is evaluated to produce its value, which is an rvalue.


## How to differentiate lvalues and rvalues

You may still be confused about what kind of expressions qualify as an lvalue vs an rvalue. For example, is the result of operator++ an lvalue or an rvalue? We’ll cover various methods you can use to determine which is which here.



Tip to differ these value.

Tip

A rule of thumb to identify lvalue and rvalue expressions:

- Lvalue expressions are those that evaluate to functions or identifiable objects (including variables) that persist beyond the end of the expression.
- Rvalue expressions are those that evaluate to values, including literals and temporary objects that do not persist beyond the end of the expression.


Finally, we can write a program and have the compiler tell us what kind of expression something is. The following code demonstrates a method that determines whether an expression is an lvalue or an rvalue:


```cpp
#include <iostream>
#include <string>

// T& is an lvalue reference, so this overload will be preferred for lvalues
template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// A helper macro (#expr prints whatever is passed in for expr as text)
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }

int getint() { return 5; }

int main()
{
    PRINTVCAT(5);        // rvalue
    PRINTVCAT(getint()); // rvalue
    int x { 5 };
    PRINTVCAT(x);        // lvalue
    PRINTVCAT(std::string {"Hello"}); // rvalue
    PRINTVCAT("Hello");  // lvalue Why? Because C-Style strings lives across the application. But std::strings not.
    PRINTVCAT(++x);      // lvalue Why? Because it RETURNS the incremented value of x.
    PRINTVCAT(x++);      // rvalue Why? It stores the current x, increment the x and return the stored (old value, x-1) so x is a left value but x++ not.
}
```
Output:

```plaintext
5 is an rvalue
getint() is an rvalue
x is an lvalue
std::string {"Hello"} is an rvalue
"Hello" is an lvalue
++x is an lvalue
x++ is an rvalue
```

**Keyconcepts of this file:**
- What is lvalue and rvalue?
- How can you distinguish lvalue and rvalue?
- What are the features of lvalue and rvalue?

