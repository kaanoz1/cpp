## Compilation order

```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

Any issues?

Error: add.cpp(5) : error C3861: 'add': identifier not found

The reason this program doesn’t compile is because the compiler compiles the contents of code files sequentially. 

How can we fix it?

1. Reorder the declaration order.

2. Use **forward** declaration:

A forward declaration allows us to tell the compiler about the existence of an identifier before actually defining the identifier.

Result of forward declaration:

```cpp
#include <iostream>

int add(int x, int y); // forward declaration of add() (using a function declaration) int add(int, int); // valid function declaration

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // this works because we forward declared add() above
    return 0;
}

int add(int x, int y) // even though the body of add() isn't defined until here
{
    return x + y;
}
```

## What about forgetting the function body?

The answer is: it depends. If a forward declaration is made, but the function is never called, the program will compile and run fine. However, if a forward declaration is made and the function is called, but the program never defines the function, the program will compile okay, but the linker will complain that it can’t resolve the function call.

## Pure declarations ?

Declarations that aren’t definitions are called pure declarations.
