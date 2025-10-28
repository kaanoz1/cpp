## for statement:

for (init-statement; condition; end-expression)
   statement;

Or:

{ // note the block here
    init-statement; // used to define variables used in the loop
    while (condition)
    {
        statement; 
        end-expression; // used to modify the loop variable prior to reassessment of the condition
    }
} // variables defined inside the loop go out of scope here

## For-loops with multiple counters

Although for-loops typically iterate over only one variable, sometimes for-loops need to work with multiple variables. To assist with this, the programmer can define multiple variables in the init-statement, and can make use of the comma operator to change the value of multiple variables in the end-expression:
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```
This loop defines and initializes two new variables: x and y. It iterates x over the range 0 to 9, and after each iteration x is incremented and y is decremented.

This program produces the result:
```plaintext
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0
```