## Narrowing conversions

In C++, a **narrowing conversion** is a potentially unsafe numeric conversion where the destination type may not be able to hold all the values of the source type.

The following conversions are defined to be narrowing:

- From a floating point type to an integral type.
- From a floating point type to a narrower or lesser ranked floating point type, unless the value being converted is constexpr and is in range of the destination type (even if the destination type doesn’t have the precision to store all the significant digits of the number).
- From an integral to a floating point type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type.
- From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type. This covers both wider to narrower integral conversions, as well as integral sign conversions (signed to unsigned, or vice-versa).

In most cases, implicit narrowing conversions will result in compiler warnings, with the exception of signed/unsigned conversions (which may or may not produce warnings, depending on how your compiler is configured).

Narrowing conversions should be avoided as much as possible, because they are potentially unsafe, and thus a source of potential errors.

## What should be done about narrowing conversion?

Do it explictily.

```cpp
void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated

    return 0;
}
```

## Brace initialization disallows narrowing conversions

```cpp
int main()
{
    int i { 3.5 }; // won't compile
    int x = 3.5; // Valid.

    return 0;
}
```

## Some constexpr conversions aren’t considered narrowing

```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is NOT narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```

Let’s apply the rule “From an integral type to another integral type that cannot represent all values of the original type, unless the value being converted is constexpr and whose value can be stored exactly in the destination type” to both of the conversions above.

In the case of n1 and u1, n1 is an int and u1 is an unsigned int, so this is a conversion from an integral type to another integral type that cannot represent all values of the original type. However, n1 is constexpr, and its value 5 can be represented exactly in the destination type (as unsigned value 5). Therefore, this is not considered to be a narrowing conversion, and we are allowed to list initialize u1 using n1.

In the case of n2 and u2, things are similar. Although n2 is constexpr, its value -5 cannot be represented exactly in the destination type, so this is considered to be a narrowing conversion, and because we are doing list initialization, the compiler will error and halt the compilation.
Ezoic

Strangely, conversions from a floating point type to an integral type do not have a constexpr exclusion clause, so these are always considered narrowing conversions even when the value to be converted is constexpr and fits in the range of the destination type:
```cpp
int n { 5.0 }; // compile error: narrowing conversion
```
Even more strangely, conversions from a constexpr floating point type to a narrower floating point type are not considered narrowing even when there is a loss of precision!

```cpp
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results
```
Example for not narrowing conversion:
```cpp
int main()
{
    float f { 1.23456789 }; // not a narrowing conversion, even though precision lost!

    return 0;
}
```

**Key concepts of this chapter:**
- What is narrowing conversion?
- constexpr and narrowing conversion.

