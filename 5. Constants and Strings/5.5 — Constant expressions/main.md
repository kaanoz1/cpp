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
