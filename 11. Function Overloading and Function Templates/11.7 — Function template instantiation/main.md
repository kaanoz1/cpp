## Template function creation:

Function templates are not actually functions -- **their code isn’t compiled or executed directly**. Instead, **function templates have one job: to generate functions** (that are compiled and executed).

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

When the compiler encounters the function call max<int>(1, 2), it will determine that a function definition for max<int>(int, int) **does not already exist.** Consequently, the compiler will implicitly use our max<T> **function template to create one.**

The process of creating functions (with specific types) from function templates (with template types) is called **function template instantiation** (or instantiation for short). 

When a function is instantiated due to a function call, it’s called **implicit instantiation.** A function that is instantiated from a template is technically called a **specialization**, but in common language is often called a **function instance.** The template from which a specialization is produced is called a **primary template.** Function instances are normal functions in all regards.

Conversely, if no function call is made to a function template, the function template won’t be instantiated in that translation unit.

Check the example:

```cpp
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```

## Deduction in templates:

Since `max<T>(T, T)` has T in three places. We do not need to do `max<int>(3,5);` We can do  `max(3, 5)` or `max<>(1, 9);`


What about we omit the angle braces?

```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
```

## Beware function templates with modifiable static local variables

```cpp
#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}
```


```plaintext
1) 12
2) 13
1) 14.5
```

You may have been expecting the last line to print 3) 14.5. However, this is what the compiler actually compiles and executes:

```cpp
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
```
