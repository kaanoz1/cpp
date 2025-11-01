## Check the following program.

That does not work correctly.

main.cpp:
```cpp
#include <iostream>

template <typename T>
T addOne(T x); // function template forward declaration

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
add.cpp:

```cpp

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}
```

If addOne were a non-template function, this program would work fine: In main.cpp, the compiler would be satisfied with the forward declaration of addOne, and the linker would connect the call to addOne() in main.cpp to the function definition in add.cpp.

The **linker** error we got here:

```plaintext
1>Project6.obj : error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main
1>Project6.obj : error LNK2019: unresolved external symbol "double __cdecl addOne<double>(double)" (??$addOne@N@@YANN@Z) referenced in function _main
```

What happens here?

In main.cpp, we call addOne<int> and addOne<double>. However, since the compiler can’t see the definition for function template addOne, it can’t instantiate those functions inside main.cpp. It does see the forward declaration for addOne though, and will assume those functions exist elsewhere and will be linked in later.

To solve this issue we might do:

add.h:
```cpp
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif
```
main.cpp:
```cpp

#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```

That way, any files that need access to the template can #include the relevant header, and the template definition will be copied by the preprocessor into the source file. The compiler will then be able to instantiate any functions that are needed.

You may be wondering why this doesn’t cause a violation of the one-definition rule (ODR). The ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files. So there is no problem if the template definition is copied into multiple files (as long as each definition is identical).

But what about the instantiated functions themselves? If a function is instantiated in multiple files, how does that not cause a violation of the ODR? The answer is that functions implicitly instantiated from templates are implicitly **inline**. And as you know, **inline functions** can be defined in multiple files, so long as the definition is identical in each.
