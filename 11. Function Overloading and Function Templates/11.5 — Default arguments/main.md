## Default parameters: 

```cpp
void print(int x, int y=10) // 10 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

Rule: If a parameter is given a default argument, all subsequent parameters (to the right) must also be given default arguments.

```cpp
void print(int x=10, int y); // not allowed
```

## Default arguments can not be redeclared, and must be declared before use

Once declared, a default argument can not be redeclared in the same **translation unit.** That means for a function with a forward declaration and a function definition, the default argument can be declared in either the forward declaration or the function definition, **but not both.**

```cpp
#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

The default argument must also be declared in the translation unit before it can be used:

```cpp
#include <iostream>

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

What should we do in this situation?

The **best practice** is to declare the default argument in the forward declaration and not in the function definition, as the forward declaration is more likely to be seen by other files and included before use (particularly if it’s in a header file).


in foo.h:
```cpp

#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```
in main.cpp:
```cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);

    return 0;
}
```

### Best practice

If the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise, put the default argument in the function definition.

## Default arguments can lead to ambiguous matches

Consider:

```cpp
void foo(int x = 0)
{
}

void foo(double d = 0.0)
{
}

int main()
{
    foo(); // ambiguous function call

    return 0;
}
```

```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)

int main()
{
    print(1, 2);   // will resolve to print(int, int)
    print(1, 2.5); // will resolve to print(int, double)
    print(1);      // ambiguous function call: Compilation error:

    return 0;
}
```

For the call print(1), the compiler is unable to tell whether this resolve to print(int), print(int, int), or print(int, double).

In the case where we mean to call print(int, int) or print(int, double) we can always explicitly specify the second parameter. But what if we want to call print(int)? It’s not obvious how we can do so.


**Key concepts of this file:**
- Default parameters
- In forward declaration, where should I put default parameter?
- Ambigious function call and what does happen whenever this type of situation occurs?

