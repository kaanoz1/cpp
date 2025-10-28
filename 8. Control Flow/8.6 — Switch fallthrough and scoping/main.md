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