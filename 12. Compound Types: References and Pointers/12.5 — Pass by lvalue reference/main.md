## Pass by reference

Here’s the same example as above, using pass by reference instead of pass by value:

```cpp
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
```

This program is identical to the prior one, except the type of parameter y has been changed from std::string to std::string& (an lvalue reference). Now, when printValue(x) is called, lvalue reference parameter y is bound to argument x. Binding a reference is always inexpensive, and no copy of x needs to be made. Because a reference acts as an alias for the object being referenced, when printValue() uses reference y, it’s accessing the actual argument x (rather than a copy of x).

### Key insight

Pass by reference allows us to pass arguments to a function without making copies of those arguments each time the function is called.

The following program demonstrates that a value parameter is a separate object from the argument, while a reference parameter is treated as if it were the argument:

```cpp
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
```
One run of this program produced the following output:

```plaintext
The address of x is: 0x7ffd16574de0
The address of the value parameter is: 0x7ffd16574de4
The address of the reference parameter is: 0x7ffd16574de0
```

We can see that the argument has a different address than the value parameter, meaning the value parameter is a different object. Since they have separate memory addresses, in order for the value parameter to have the same value as the argument, the argument’s value must be copied into memory held by the value parameter.

On the other hand, we can see that taking the address of the reference parameter yields an address identical to that of the argument. This means that the reference parameter is being treated as if it were the same object as the argument.