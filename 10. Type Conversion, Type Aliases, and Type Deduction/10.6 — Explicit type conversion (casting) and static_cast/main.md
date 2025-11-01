## Casting types:

C++ supports 5 different types of casts: **static_cast**, **dynamic_cast**, **const_cast**, **reinterpret_cast**, and **C-style casts**. The first four are sometimes referred to as named casts.

### Casting table:

![Casting Table](casting-types.png)

## C-style cast

casting that we know in popular languages: `double x = (double)5`

C++ also provides an alternative form of C-style cast known as a **function-style cast**, which resembles a function call:

`double x = double(5);` or `cout << double(x) / y << endl` **function-cast**.

There are a couple of significant reasons that C-style casts are generally avoided in modern C++.

## static_cast example:

```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a

    return 0;
}
```

static_cast provides compile-time type checking. 


```cpp
// a C-style string literal can't be converted to an int, so the following is an invalid conversion
int x { static_cast<int>("Hello") }; // invalid: will produce compilation error
```

## Casting vs initializing a temporary object

Let’s say we have some variable x that we need to convert to an int. There are two conventional ways we can do this:

    static_cast<int>(x), which returns a temporary int object direct-initialized with x.
    int { x }, which creates a temporary int object direct-list-initialized with x.

We should avoid int ( x ), which is a C-style cast. This will return a temporary int direct-initialized with the value of x (like we’d expect from the syntax), but it also has the other downsides mentioned in the C-style cast section (like allowing the possibility of performing a dangerous conversion).

There are (at least) three notable differences between the static_cast and the direct-list-initialized temporary:

    1. int { x } uses list initialization, which disallows narrowing conversions. This is great when initializing a variable, because we rarely intend to lose data in such cases. But when using a cast, it is presumed we know what we’re doing, and if we want to do a cast that might lose some data, we should be able to do that. The narrowing conversion restriction can be an impediment in this case.


```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    // We want to do floating point division, so one of the operands needs to be a floating point type
    std::cout << double{x} / y << '\n'; // okay if int is 32-bit, narrowing if x is 64-bit
}
```

In this example, we have decided to convert x to a double so we can do floating-point division rather than integer division. On a 32-bit architecture, this will work fine (because a double can represent all the values that can be stored in a 32-bit int, so it isn’t a narrowing conversion). But on a 64-bit architecture, this is not the case, so converting a 64-bit int to a double is a narrowing conversion. And since list initialization disallows narrowing conversions, this won’t compile on architectures where int is 64-bits.

2. static_cast makes it clearer that we are intending to perform a conversion. Although the static_cast is more verbose than the direct-list-initialized alternative, in this case, that’s a good thing, as it makes the conversion easier to spot and search for. That ultimately makes your code safer and easier to understand.
3. Direct-list-initializion of a temporary only allows single-word type names. Due to a weird syntax quirk, there are several places within C++ where only single-word type names are allowed (the C++ standard calls these names “simple type specifiers”). So while int { x } is a valid conversion syntax, unsigned int { x } is not.


You can see this for yourself in the following example, which produces a compile error:
```cpp
#include <iostream>

int main()
{
    unsigned char c { 'a' };
    std::cout << unsigned int { c } << '\n'; //Not single word initialization.

    return 0;
}
```

**Key concepts of this file:**
    - Casting types
    - C style casting and function style casting.
    - Casting vs initiazling temproray object. What is the difference? (Read the paragraph)
    - Brace initialization and single word initialization.