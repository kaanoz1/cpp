## REFERENCES, FINALLY YOU MF:

In C++, a reference is an alias for an existing object. Once a reference has been defined, any operation on the reference is applied to the object being referenced. This means we can use a reference to read or modify the object being referenced.

## Reference types:

lvalue references and rvalue references.

## Lvalue references types

Examples:

```cpp
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```

There are two kinds of lvalue references:

- for non consts: “lvalue reference”, **lvalue reference to non-const** or a **non-const lvalue reference** (since it isn’t defined using the const keyword).
- An lvalue reference to a const is commonly called either an **lvalue reference to const** or a **const lvalue reference**.

## Lvalue reference variables

One of the things we can do with an lvalue reference type is create an lvalue reference variable. An lvalue reference variable is a variable that acts as a reference to an lvalue (usually another variable).

To create an lvalue reference variable, we simply define a variable with an lvalue reference type:

```cpp
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    x = 6;

    std::cout << x << '\n';  // 6
    std::cout << ref << '\n'; // 6

    // Because ref and x are the same thing. It points out same box in memory.
    return 0;
}
```

In the above example, the type int& defines ref as an lvalue reference to an int, which we then initialize with lvalue expression x. Thereafter, ref and x can be used synonymously. This program thus prints:
```plaintext
5
5
```


## Modifying values through a non-const lvalue reference

```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```

This code prints:
```plaintext
55
66
77
```

## Reference initialization
```cpp
int main()
{
    int& invalidRef;   // error: references must be initialized

    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    return 0;
}
```

When a reference is initialized with an object (or function), we say it is **bound** to that object (or function). The process by which such a reference is bound is called **reference binding.** The object (or function) **being referenced** is sometimes called the **referent**.

Non-const lvalue references can only be bound to a modifiable lvalue.

```cpp
int main()
{
    int x { 5 };
    int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue

    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    return 0;
}
```


I dont know why but: Lvalue references to void are disallowed (what would be the point?).

## Dangling references

When an object being referenced is destroyed before a reference to it, the reference is left referencing an object that no longer exists. Such a reference is called a dangling reference. Accessing a dangling reference leads to undefined behavior.

Dangling references are fairly easy to avoid, but we’ll show a case where this can happen in practice in lesson 12.12 -- Return by reference and return by address.

Example:

```cpp
#include <iostream>

int& getInvalidReference()
{
    int number = 10; 
    return number;   // returning referance of number.
    
} // Undefined Behaviour: number is destroyed here.

int main()
{
    // 'danglingRef', takes a reference of a variable which IS DESTROYED.
    int& danglingRef = getInvalidReference();

    std::cout << "Dangling Referans: ";

    // UNDEFINED BEHAVIOR
    // Trying to read garbade value.
   
    std::cout << danglingRef << std::endl; 
    
    return 0;
}
```

Note: References does not contain any storage in memory.
They are just alises for objets.

**Key concepts of this file:**
- What are references?
- Dangling reference problem.
- Reference constraints.
- Non-const references.