## Initializing an lvalue reference to const with a modifiable lvalue

Lvalue references to const can also bind to modifiable lvalues. In such a case, the object being referenced is treated as const when accessed through the reference (even though the underlying object is non-const):
```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier
    std::cout << ref << '\n'; // okay: prints 6
    return 0;
}
```
In the above program, we bind const reference ref to modifiable lvalue x. We can then use ref to access x, but because ref is const, we can not modify the value of x through ref. However, we still can modify the value of x directly (using the identifier x).

## Initializing an lvalue reference to const with an rvalue

```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // okay: 5 is an rvalue

    std::cout << ref << '\n'; // prints 5

    return 0;
}
```

This is allowed whereas `int& ref { 5 }` is not.


## Initializing an lvalue reference to const with a value of a different type

Lvalue references to const can even bind to values of a different type, so long as those values can be implicitly converted to the reference type:
```cpp
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary. NEW OBJECT. r2 is reference for new, nameless value in memory.

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
```

## Where can be a problem?

Warning

We normally assume that a reference is identical to the object it is bound to -- but this assumption is broken when a reference is bound to a **TEMPRORAY COPY** of the object or a temporary resulting from the conversion of the object instead. Any modifications subsequently made to the original object will not be seen by the reference (as it is referencing a different object), and vice-versa.

Here’s a silly example showing this:
```cpp
#include <iostream>

int main()
{
    short bombs { 1 };         // I can has bomb! (note: type is short)

    const int& you { bombs };  // You can has bomb too (note: type is int&)
    --bombs;                   // Bomb all gone

    if (you)                   // You still has?
    {
        std::cout << "Bombs away!  Goodbye, cruel world.\n"; // Para bailar la bomba
    }

    return 0;
}
```
In the above example, **bombs** is a short and **you** is a const int&. Because **you** can only bind to an int object, when **you** is initialized with **bombs**, the compiler will implicitly convert **bombs** to an int, which results in the creation of a temporary int object (with value 1). **you** ends up bound to this temporary object rather than **bombs**.

When **bombs** is decremented, **you** is not affected because it is referencing a different object. So although we expect if (**you**) to evaluate to **false**, it actually evaluates to **true**.

If you would stop blowing up the world, that would be great.

## Const references bound to temporary objects extend the lifetime of the temporary object