## If statements

```cpp
if (condition_statements) 
    true statements;
```

## Non-Boolean conditionals

```cpp
#include <iostream>

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```

if (x) means “if x is non-zero/non-empty”.

