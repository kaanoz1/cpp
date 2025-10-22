## The initialization order problem of global variables

Initialization of static variables (which includes global variables) happens as part of program startup, before execution of the main function. This proceeds in two phases.

The first phase is called static initialization. Static initialization proceeds in two phases:

    Global variables with constexpr initializers (including literals) are initialized to those values. This is called constant initialization.
    Global variables without initializers are zero-initialized. Zero-initialization is considered to be a form of static-initialization since 0 is a constexpr value.

The second phase is called dynamic initialization. This phase is more complex and nuanced, but the gist of it is that global variables with non-constexpr initializers are initialized.

Here’s an example of a non-constexpr initializer:

int init()
{
    return 5;
}

int g_something{ init() }; // non-constexpr initialization

Within a single file, for each phase, global variables are generally initialized in order of definition (there are a few exceptions to this rule for the dynamic initialization phase). Given this, you need to be careful not to have variables dependent on the initialization value of other variables that won’t be initialized until later. For example:

```cpp
#include <iostream>

int initX();  // forward declaration
int initY();  // forward declaration

int g_x{ initX() }; // g_x is initialized first
int g_y{ initY() };

int initX()
{
    return g_y; // g_y isn't initialized when this is called
}

int initY()
{
    return 5;
}

int main()
{
    std::cout << g_x << ' ' << g_y << '\n';
}
```
```plaintext
0 5
```

Much more of a problem, the order in which static objects are initialized across different translation units is ambiguous.

Given two files, a.cpp and b.cpp, either could have its global variables initialized first. If some variable with static duration in a.cpp is initialized with a static duration variable defined in b.cpp, there’s a 50% chance that the variable in b.cpp won’t be initialized yet.