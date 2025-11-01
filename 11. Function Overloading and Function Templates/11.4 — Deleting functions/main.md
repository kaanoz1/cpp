## Deleting functions?

Consider the issue?

```cpp
printInt(5);    // okay: prints 5
printInt('a');  // prints 97 -- does this make sense?
printInt(true); // print 1 -- does this make sense?
```

## Deleting a function using the = delete specifier

In cases where we have a function that we explicitly do not want to be callable, we can define that function as deleted by using the = delete specifier. If the compiler matches a function call to a deleted function, compilation will be halted with a compile error.

```cpp
void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation
```

Note: = delete means “I forbid this”, not “this doesn’t exist”.

What about deleting all non-matchin overloads?

Deleting a bunch of individual function overloads works fine, but can be verbose. There may be times when we want a certain function to be called only with arguments whose types exactly match the function parameters. We can do this by using a function template (introduced in upcoming lesson 11.6 -- Function templates) as follows:


```cpp
#include <iostream>

// This function will take precedence for arguments of type int
void printInt(int x)
{
    std::cout << x << '\n';
}

// This function template will take precedence for arguments of other types
// Since this function template is deleted, calls to it will halt compilation
template <typename T>
void printInt(T x) = delete;

int main()
{
    printInt(97);   // okay
    printInt('a');  // compile error
    printInt(true); // compile error

    return 0;
}
```

**Key concepts of this file:**
- Deleting a function via = operator
- Deletion all non-matching funcitons



