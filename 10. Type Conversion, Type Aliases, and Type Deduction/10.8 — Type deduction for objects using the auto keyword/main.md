## Type deduction for initialized variables


Type deduction (also sometimes called type inference) is a feature that allows the compiler to deduce the type of an object from the object’s initializer. When defining a variable, type deduction can be invoked by using the auto keyword can be used in place of the variable’s type:

```cpp
int main()
{
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto i { 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
    auto x { i }; // i is an int, so x will be deduced as an int

    auto y { 10.0f } //since 10.9 is parsed as float by suffix f, it is deduced that y has a typeid().name() float.

    return 0;
}
```

## Keyword auto via const and constexpr

```cpp
int main()
{
    int a { 5 };            // a is an int

    const auto b { 5 };     // b is a const int
    constexpr auto c { 5 }; // c is a constexpr int

    return 0;
}
```

## Type deduction must have something to deduce from

```cpp
#include <iostream>

void foo()
{
}

int main()
{
    auto a;           // The compiler is unable to deduce the type of a
    auto b { };       // The compiler is unable to deduce the type of b
    auto c { foo() }; // Invalid: c can't have type incomplete type void

    return 0;
}
```

## Type deduction drops const from the deduced type !!!

```cpp
int main()
{
    const int a { 5 }; // a has type const int
    auto b { a };      // b has type int (const dropped)

    return 0;
}
```

## Type deduction for string literals

For historical reasons, string literals in C++ have a strange type. Therefore, the following probably won’t work as expected:
```cpp
auto s { "Hello, world" }; // s will be type const char*, not std::string
```

f you want the type deduced from a string literal to be std::string or std::string_view, you’ll need to use the s or sv literal suffixes (introduced in lessons 5.7 -- 


```cpp
#include <string>
#include <string_view>

int main()
{
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    return 0;
}
```

## Type deduction and constexpr

```cpp
int main()
{
    constexpr double a { 3.4 };  // a has type const double (constexpr not part of type, const is implicit)

    auto b { a };                // b has type double (const dropped)
    const auto c { a };          // c has type const double (const dropped but reapplied)
    constexpr auto d { a };      // d has type const double (const dropped but implicitly reapplied by constexpr)

    return 0;
}
```

**Key concepts of this file:**
    - auto keyword
    - initialization and suffixes matters using auto keyword.
    - auto keyword has some clue to initialize.
    - meaningless for auto keyword initializations.
    - string suffixes using std:literals;
    - auto keywords drop const and constexpr
