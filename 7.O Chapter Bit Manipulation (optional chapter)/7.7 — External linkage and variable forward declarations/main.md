## External vs Internal:

An identifier with **external linkage** can be seen and used both from the file in which it is defined, and from other code files (via a forward declaration). In this sense, identifiers with external linkage are truly “global” in that they can be used anywhere in your program!

## Functions have external linkage by default

In lesson 2.8 -- Programs with multiple code files, you learned that you can call a function defined in one file from another file. This is because functions have external linkage by default.

In order to call a function defined in another file, you must place a forward declaration for the function in any other files wishing to use the function. The forward declaration tells the compiler about the existence of the function, and the linker connects the function calls to the actual function definition.


## Global variables with external linkage

Global variables with external linkage are sometimes called external variables. To make a global variable external (and thus accessible by other files), we can use the extern keyword to do so:

```cpp
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

**Non-const global variables are external by default, so we don’t need to mark them as extern.**


## Variable forward declarations via the extern keyword

To actually use an external global variable that has been defined in another file, you also must place a forward declaration for the global variable in any other files wishing to use the variable. For variables, creating a forward declaration is also done via the extern keyword (with no initialization value).

Here is an example of using variable forward declarations:

main.cpp:


```cpp
#include <iostream>

extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```


Here’s the definitions for those variables:

a.cpp:
```cpp
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```
In the above example, a.cpp and main.cpp both reference the same global variable named g_x. So even though g_x is defined and initialized in a.cpp, we are able to use its value in main.cpp via the forward declaration of g_x.

## Note:

Note that the extern keyword has different meanings in different contexts. In some contexts, extern means “give this variable external linkage”. In other contexts, extern means “this is a forward declaration for an external variable that is defined somewhere else”. Yes, this is confusing, so we summarize all of these usages in lesson 


Note that function forward declarations don’t need the extern keyword -- the compiler is able to tell whether you’re defining a new function or making a forward declaration based on whether you supply a function body or not. Variables forward declarations do need the extern keyword to help differentiate uninitialized variables definitions from variable forward declarations (they look otherwise identical):

```cpp
// non-constant
int g_x;        // variable definition (no initializer)
int g_x { 1 };  // variable definition (w/ initializer)
extern int g_x; // forward declaration (no initializer)

// constant
extern const int g_y { 1 }; // variable definition (const requires initializers)
extern const int g_y;       // forward declaration (no initializer)
```
## Avoid using extern on a non-const global variable with an initializer

The following two lines are semantically equivalent:
```cpp
int g_x { 1 };        // extern by default
extern int g_x { 1 }; // explicitly extern (may cause compiler warning)
```

However, your compiler may issue a warning about the latter statement, even though it is technically valid.

Remember when we said compilers have the leeway to issue a diagnostic for things they find suspicious? This is one of those cases. Conventionally, extern is applied to a non-const variable when we want a forward declaration. However, adding an initializer makes the statement a definition instead. The compiler is telling you that something seems amiss. To correct it, either remove the initializer (if you intended a forward declaration) or remove the extern (if you intended a definition).

Best practice

Only use extern for global variable forward declarations or const global variable definitions.
Do not use extern for non-const global variable definitions (they are implicitly extern).

## Quick summary
```cpp
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```

We provide a comprehensive summary in lesson 7.12 -- Scope, duration, and linkage summary.

