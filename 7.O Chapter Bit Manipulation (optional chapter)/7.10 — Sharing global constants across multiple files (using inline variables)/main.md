## Global constants as external variables

Consider the program:

constants.h: 
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace constants
{
    // Since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
    // We can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
    extern const double pi;
    extern const double avogadro;
    extern const double myGravity;
}

#endif
```

constants.cpp:

```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

```cpp
main.cpp:

#include "constants.h" // include all the forward declarations

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

Now the symbolic constants will get instantiated only once (in constants.cpp) instead of in each code file where constants.h is #included, and all uses of these constants will be linked to the version instantiated in constants.cpp. Any changes made to constants.cpp will require recompiling only constants.cpp.

However, there are a couple of downsides to this method. First, because only the variable definitions are constexpr (the forward declarations aren’t, and can’t be), these constants are constant expressions only within the file they are actually defined in (constants.cpp). In other files, the compiler will only see the forward declaration, which doesn’t define a constexpr value (and must be resolved by the linker). This means outside of the file where they are defined, these variables can’t be used in a constant expression. Second, because constant expressions can typically be optimized more than runtime expressions, the compiler may not be able to optimize these as much.

## Global constants as inline variables C++17

In lesson 7.9 -- Inline functions and variables, we covered inline variables, which are variables that can have more than one definition, so long as those definitions are identical. By making our constexpr variables inline, we can define them in a header file and then #include them into any .cpp file that requires them. This avoids both ODR violations and the downside of duplicated variables.

A reminder

Constexpr functions are implicitly inline, but constexpr variables are not implicitly inline. If you want an inline constexpr variable, you must explicitly mark it as inline.

Key insight

Inline variables have external linkage by default, so that they are visible to the linker. This is necessary so the linker can de-duplicate the definitions.

Non-inline constexpr variables have internal linkage. If included into multiple translation units, each translation unit will get its own copy of the variable. This is not an ODR violation because they are not exposed to the linker.

constants.h:
```cpp

#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif

main.cpp:

#include "constants.h"

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```
We can include constants.h into as many code files as we want, but these variables will only be instantiated once and shared across all code files.

This method does retain the downside of requiring every file that includes the constants header be recompiled if any constant value is changed.

Advantages:

    Can be used in constant expressions in any translation unit that includes them.
    Only one copy of each variable is required.
