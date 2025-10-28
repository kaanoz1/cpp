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