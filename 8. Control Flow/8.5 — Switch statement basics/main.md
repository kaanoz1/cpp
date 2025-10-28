## Swith-case syntax:


```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x)
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```
Then one of the following occurs:

    If the expression’s value is equal to the value after any of the case-labels, the statements after the matching case-label are executed.
    If no matching value can be found and a default label exists, the statements after the default label are executed.
    If no matching value can be found and there is no default label, the switch is skipped.


The condition in a switch must evaluate to an integral type (see lesson 4.1 -- Introduction to fundamental data types if you need a reminder which fundamental types are considered integral types) 


Note: Integral Types are: int, char, short, long, long long and unsigned variation of them.


or an enumerated type (covered in future lessons 13.2 -- Unscoped enumerations and 13.6 -- Scoped enumerations (enum classes)),

enum Status { WORKING, IDLE, STOP };

enum class Color { Red, Green, Blue };


or be convertible to one. Expressions that evaluate to floating point types, strings, and most other non-integral types may not be used here.


## Case keyword

Case keyword should get an constant expression.

## Taking a break

In the above examples, we used return-statements to stop execution of the statements after our labels. However, this also exits the entire function.

A break statement (declared using the break keyword) tells the compiler that we are done executing statements within the switch, and that execution should continue with the statement after the end of the switch block. This allows us to exit a switch-statement without exiting the entire function.

## Switch vs if-else

Switch statements are best used when there is a single expression (with a non-boolean integral type or an enumerated type) we want to evaluate for equality against a small number of values. If the number of case labels gets too large, the switch can be hard to read.

Compared to the equivalent if-else statements, a switch-statement can be more readable, makes it clearer that it is the same expression being tested for equality in each case, and has the advantage of only evaluating the expression once (making it more efficient).

However, if-else is significantly more flexible. Some cases where if or if-else is typically better:

    Testing an expression for comparisons other than equality (e.g. x > 5)
    Testing multiple conditions (e.g. x == 5 && y == 6)
    Determining whether a value is within a range (e.g. x >= 5 && x <= 10)
    The expression has a type that switch doesn’t support (e.g. d == 4.0).
    The expression evaluates to a bool.

    