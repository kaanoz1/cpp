## auto keyword can be used in return type of functions.

```cpp
auto add(int x, int y)
{
    return x + y;
}
```

What about the returning types different? Consider:
```cpp
auto someFcn(bool b)
{
    if (b)
        return 5; // return type int
    else
        return 6.7; // return type double
}
```

In the above function, the two return statements return values of different types, so the compiler will give an error.

If such a case is desired for some reason, you can either explicitly specify a return type for your function (in which case the compiler will try to implicitly convert any non-matching return expressions to the explicit return type), or you can explicitly convert all of your return statements to the same type. In the example above, the latter could be done by changing 5 to 5.0, but static_cast can also be used for non-literal types.

In other cases, the return type of a function may either be long and complex, or not be that obvious. In such cases, auto can be used to simplify:

```cpp
// let compiler determine the return type of unsigned short + char
auto add(unsigned short x, char y)
{
    return x + y;
}
```

What it will return? Discussed in 11.8 -- Function templates with multiple template types.

## Downsides of return type deduction
```cpp
#include <iostream>

auto foo();

int main()
{
    std::cout << foo() << '\n'; // the compiler has only seen a forward declaration at this point

    return 0;
}

auto foo()
{
    return 5;
}
```

Some machines might give the error declared: `error C3779: 'foo': a function that returns 'auto' cannot be used before it is defined.`

## Trailing return type syntax

The auto keyword can also be used to declare functions using a trailing return syntax, where the return type is specified after the rest of the function prototype.

Consider the following function:
```cpp
int add(int x, int y)
{
  return (x + y);
}
```

Using the trailing return syntax, this could be equivalently written as:

```cpp

auto add(int x, int y) -> int
{
  return (x + y);
}
```

In this case, auto does not perform type deduction -- it is just part of the syntax to use a trailing return type.

### Why would you want to use this? Here are some reasons:

1. For functions with complex return types, a trailing return type can make the function easier to read:
```cpp

#include <type_traits> // for std::common_type

std::common_type_t<int, double> compare(int, double);         // harder to read (where is the name of the function in this mess?)
auto compare(int, double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)
```
2. The trailing return type syntax can be used to align the names of your functions, which makes consecutive function declarations easier to read:
```cpp

auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
auto printSomething() -> void;
auto generateSubstring(const std::string &s, int start, int len) -> std::string;
```
### For advanced readers

3. If we have a function whose return type must be deduced based on the type of the function parameters, a normal return type will not suffice, because the compiler has not yet seen the parameters at that point.

```cpp

#include <type_traits>
// note: decltype(x) evaluates to the type of x

std::common_type_t<decltype(x), decltype(y)> add(int x, double y);         // Compile error: compiler hasn't seen definitions of x and y yet
auto add(int x, double y) -> std::common_type_t<decltype(x), decltype(y)>; // ok
```
4. The trailing return syntax is also required for some advanced features of C++, such as lambdas (which we cover in lesson 20.6 -- Introduction to lambdas (anonymous functions)).

For now, we recommend the continued use of the traditional function return syntax except in situations that require the trailing return syntax.

## Type deduction can’t be used for function parameter types

```cpp
#include <iostream>

void addAndPrint(auto x, auto y)
{
    std::cout << x + y << '\n';
}

int main()
{
    addAndPrint(2, 3); // case 1: call addAndPrint with int parameters
    addAndPrint(4.5, 6.7); // case 2: call addAndPrint with double parameters

    return 0;
}
```

**Key concepts of this file:**
    - Type deduction (auto keyword) via functions
    - Trailing return types
    - Trailing return type syntax and when and how to use.
    - auto keyword and forward declarations.

Keyword learned: auto
