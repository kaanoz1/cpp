## Overload resolution:

Overload resolution is a process when a function is specified which has multiple definitions with same name but has been overloaded by some sort of reasons. (might be different parameter numbers or different parameter types)

But what happens when we have two definitions and provided not exact data type?

Consider this:

```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print('a'); // char does not match int or double, so what happens?
     print(5L); // long does not match int or double, so what happens?

     return 0;
}
```
Just because there is no exact match here doesn’t mean a match can’t be found -- after all, a char or long can be implicitly type converted to an int or a double. But **which is the best conversion to make** in each case?

In this lesson, we’ll explore how the compiler matches a given function call to a specific overloaded function.

RELOOK THIS CONCEPT.

