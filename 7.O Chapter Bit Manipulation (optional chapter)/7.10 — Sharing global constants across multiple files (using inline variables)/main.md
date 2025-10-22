Global constants as inline variables C++17

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
