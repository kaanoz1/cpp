## What is Straight-Line Program:

Straight-line programs take the same path (execute the same statements in the same order) every time they are run.

## Branching?

When a control flow statement causes point of execution to change to a non-sequential statement, this is called branching.

Example:

```cpp
#include <iostream>

int main() {
    int x = 10;

    std::cout << "This line works everytime." << std::endl;

    // Branching
    if (x > 5) 
        std::cout << "x, is larger then 5" << std::endl;
     else 
        std::cout << "x, is less then 5" << std::endl;
    

    std::cout << "This line works everytime also." << std::endl;

    return 0;
}
```

Control Flow:


![Keyword Categorization](control-flow-categorization.png)