## What is Straight-Line Program:

Straight-line programs take the same path (execute the same statements in the same order) every time they are run.

## Branching?

When a control flow statement causes point of execution to change to a non-sequential statement, this is called branching.

Example:

```cpp
#include <iostream>

int main() {
    int x = 10;

    std::cout << "This line works everytime." << std::endl;

    // Branching
    if (x > 5) 
        std::cout << "x, is larger then 5" << std::endl;
     else 
        std::cout << "x, is less then 5" << std::endl;
    

    std::cout << "This line works everytime also." << std::endl;

    return 0;
}
```

Control Flow:


![Keyword Categorization](control-flow-categorization.png)

## Nested if-statements and the dangling else problem

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if-statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if-statement
            std::cout << x << " is between 0 and 20\n";

    // which if statement does this else belong to?
    else
        std::cout << x << " is negative\n";

    return 0;
}
```

The above program introduces a source of potential ambiguity called a **dangling else** problem. Is the else-statement in the above program matched up with the outer or inner if-statement?

The answer is that an else-statement is paired up with the last unmatched if-statement in the same block. Thus, in the program above, the else-statement is matched up with the inner if-statement, as if the program had been written like this:

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if statement
    {
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";
        else // attached to inner if statement
            std::cout << x << " is negative\n";
    }

    return 0;
}
```

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

    ## Fallthrough of Switch

When a switch expression matches a case label or optional default label, execution begins at the first statement following the matching label. Execution will then continue sequentially until one of the following termination conditions happens:

    The end of the switch block is reached.
    Another control flow statement (typically a break or return) causes the switch block or function to exit.
    Something else interrupts the normal flow of the program (e.g. the OS shuts the program down, the universe implodes, etc…)

Note that the presence of another case label is not one of these terminating conditions -- thus, without a break or return, execution will overflow into subsequent cases.

Here is a program that exhibits this behavior:

```cpp

#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }

    return 0;
}
```

This program outputs the following:
```plaintext
2
3
4
5
```

## The [[fallthrough]] attribute

Commenting intentional fallthrough is a common convention to tell other developers that fallthrough is intended. While this works for other developers, the compiler and code analysis tools don’t know how to interpret comments, so it won’t get rid of the warnings.

To help address this, C++17 adds a new attribute called [[fallthrough]].

Attributes are a modern C++ feature that allows the programmer to provide the compiler with some additional data about the code. To specify an attribute, the attribute name is placed between double brackets. Attributes are not statements -- rather, they can be used almost anywhere where they are contextually relevant.

The [[fallthrough]] attribute modifies a null statement to indicate that fallthrough is intentional (and no warnings should be triggered):
```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }

    return 0;
}
```

## Sequential case labels

```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```

## Labels do not define a new scope

## Variable declaration and initialization inside case statements

Note switch force compiler to JUMP to corresponding case stament. Does not execute others.

```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```

Solution?

```cpp
switch (1)
{
case 1:
{ // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
}

default:
    std::cout << "default case\n";
    break;
}
```

## goto statement:

Example:
```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
    return 0;
}
```

## Illegal usage of goto:

There are two primary limitations to jumping: You can jump only within the bounds of a single function (you can’t jump out of one function and into another), and if you jump forward, you can’t jump forward over the initialization of any variable that is still in scope at the location being jumped to. For example:

```cpp
int main()
{
    goto skip;   // error: this jump is illegal because...
    int x { 5 }; // this initialized variable is still in scope at statement label 'skip'
skip:
    x += 3;      // what would this even evaluate to if x wasn't initialized?
    return 0;
}
```

## for statement:

for (init-statement; condition; end-expression)
   statement;

Or:

{ // note the block here
    init-statement; // used to define variables used in the loop
    while (condition)
    {
        statement; 
        end-expression; // used to modify the loop variable prior to reassessment of the condition
    }
} // variables defined inside the loop go out of scope here

## For-loops with multiple counters

Although for-loops typically iterate over only one variable, sometimes for-loops need to work with multiple variables. To assist with this, the programmer can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression:
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```
This loop defines and initializes two new variables: x and y. It iterates x over the range 0 to 9, and after each iteration x is incremented and y is decremented.

This program produces the result:
```plaintext
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0
```

## Halts:

The last category of flow control statement we’ll cover in this chapter is the halt. A halt is a flow control statement that terminates the program. In C++, halts are implemented as functions (rather than keywords), so our halt statements will be function calls.

Let’s take a brief detour, and recap what happens when a program exits normally. When the main() function returns (either by reaching the end of the function, or via a return statement), a number of different things happen.

First, because we’re leaving the function, all local variables and function parameters are destroyed (as per usual).

Next, a special function called std::exit() is called, with the return value from main() (the status code) passed in as an argument. So what is std::exit()?

## The std::exit() function

std::exit() is a function that causes the program to terminate normally. Normal termination means the program has exited in an expected way. Note that the term normal termination does not imply anything about whether the program was successful (that’s what the status code is for). For example, let’s say you were writing a program where you expected the user to type in a filename to process. If the user typed in an invalid filename, your program would probably return a non-zero status code to indicate the failure state, but it would still have a normal termination.

## std::exit() does not clean up local variables

One important note about calling std::exit() explicitly: std::exit() does not clean up any local variables (either in the current function, or in functions up the call stack). This means calling std::exit() can be dangerous if your program relies on any local variables cleaning themselves up.

## std::atexit

Because std::exit() terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

To assist with this, C++ offers the std::atexit() function, which allows you to specify a function that will automatically be called on program termination via std::exit().

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

A few notes here about std::atexit() and the cleanup function: First, because std::exit() is called implicitly when main() terminates, this will invoke any functions registered by std::atexit() if the program exits that way. Second, the function being registered must take no parameters and have no return value. Finally, you can register multiple cleanup functions using std::atexit() if you want, and they will be called in reverse order of registration (the last one registered will be called first).

## std::abort and std::terminate

C++ contains two other halt-related functions.

The std::abort() function causes your program to terminate abnormally. Abnormal termination means the program had some kind of unusual runtime error and the program couldn’t continue to run. For example, trying to divide by 0 will result in an abnormal termination. std::abort() does not do any cleanup.

```cpp
#include <cstdlib> // for std::abort()
#include <iostream>

int main()
{
    std::cout << 1 << '\n';
    std::abort();

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

The std::terminate() function is typically used in conjunction with exceptions (we’ll cover exceptions in a later chapter). Although std::terminate can be called explicitly, it is more often called implicitly when an exception isn’t handled (and in a few other exception-related cases). By default, std::terminate() calls std::abort().

## When should you use a halt?

The short answer is “almost never”. Destroying local objects is an important part of C++ (particularly when we get into classes), and none of the above-mentioned functions clean up local variables. Exceptions are a better and safer mechanism for handling error cases.

