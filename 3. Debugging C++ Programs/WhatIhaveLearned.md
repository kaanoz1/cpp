## Semantic Errors:

Semantic error is an error in meaning. These occur when a statement is syntactically valid, but either violates other rules of the language, or does not do what the programmer intended.

```cpp

int main()
{
    5 = x; // x not declared, cannot assign a value to 5
    return "hello"; // "hello" cannot be converted to an int
}
```

or

```cpp
#include <iostream>

int main()
{
    int a { 10 };
    int b { 0 };
    std::cout << a << " / " << b << " = " << a / b << '\n'; // division by 0 is undefined in mathematics
    return 0;
}

```

or even unexpected behaviours:

```cpp

#include <iostream>

int add(int x, int y) // this function is supposed to perform addition
{
    return x - y; // but it doesn't due to the wrong operator being used
}

int main()
{
    std::cout << "5 + 3 = " << add(5, 3) << '\n'; // should produce 8, but produces 2

    return 0;
}

```

or

```cpp

## Semantic Errors:

Semantic error is an error in meaning. These occur when a statement is syntactically valid, but either violates other rules of the language, or does not do what the programmer intended.

```cpp

int main()
{
    5 = x; // x not declared, cannot assign a value to 5
    return "hello"; // "hello" cannot be converted to an int
}
```

or

```cpp
#include <iostream>

int main()
{
    int a { 10 };
    int b { 0 };
    std::cout << a << " / " << b << " = " << a / b << '\n'; // division by 0 is undefined in mathematics
    return 0;
}

```

or even unexpected behaviours:

```cpp

#include <iostream>

int add(int x, int y) // this function is supposed to perform addition
{
    return x - y; // but it doesn't due to the wrong operator being used
}

int main()
{
    std::cout << "5 + 3 = " << add(5, 3) << '\n'; // should produce 8, but produces 2

    return 0;
}

```

## How to approach a problem?

Once a problem has been identified, debugging the problem generally consists of six steps:

    Find the root cause of the problem (usually the line of code that’s not working). We’ll discuss some strategies on how to do this in the next lesson.
    Ensure you understand why the issue is occurring.
    Determine how you’ll fix the issue.
    Repair the issue causing the problem.
    Retest to ensure the problem has been fixed.
    Retest to ensure no new problems have emerged.