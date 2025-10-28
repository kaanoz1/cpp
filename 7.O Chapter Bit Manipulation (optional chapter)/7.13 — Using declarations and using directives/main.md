## Qualified and unqualified name.


Qualified names are explicitly declaring that this object or functions coming from this object or namespace. Examples are:

```cpp
std::cout
object.x
this->myfunction();
```

Unqualified ares vice versa of them.

```cpp
cout
x
```

Or any other thing.

## Using-declarations

For instance: using std::cout means that everywhere that compiler encounter cout, it is coming from std namespace. 

If there’s a naming conflict between std::cout and some other use of cout that is visible from within main(), std::cout will be preferred. 

Example:

```cpp
#include <iostream>

int main()
{
   using std::cout; // this using declaration tells the compiler that cout should resolve to std::cout
   cout << "Hello world!\n"; // so no std:: prefix is needed here!

   return 0;
} // the using declaration expires at the end of the current scope
```

This doesn’t save much effort in this trivial example, but if you are using cout many times inside of a function, a using-declaration can make your code more readable. Note that you will need a separate using-declaration for each name (e.g. one for std::cout, one for std::cin, etc…).

The using-declaration is active from the point of declaration to the end of the scope in which it is declared.

## Using-directives

Another way to simplify things is to use a using-directive. A using directive allows **all** identifiers in a given namespace to be referenced without qualification from the scope of the using-directive.


```cpp
#include <iostream>

int main()
{
   using namespace std; // all names from std namespace now accessible without qualification
   cout << "Hello world!\n"; // so no std:: prefix is needed here

   return 0;
} // the using-directive ends at the end of the current scope
```

Check this situation:

There is a more insidious version of this problem that can occur as well. The updated library may introduce a function that not only has the same name, but is actually a better match for some function call. In such a case, the compiler may decide to prefer the new function instead, and the behavior of your program will change unexpectedly and silently.

Consider the following program:

Foolib.h (part of some third-party library):

```cpp
#ifndef FOOLIB_H
#define FOOLIB_H

namespace Foo
{
    int a { 20 };
}
#endif
```

```cpp
#include <iostream>
#include <Foolib.h> // a third-party library we installed outside our project directory, thus angled brackets used

int get(long)
{
    return 1;
}

int main()
{
    using namespace Foo; // Because we're lazy and want to access Foo:: qualified names without typing the Foo:: prefix
    std::cout << a << '\n'; // uses Foo::a

    std::cout << get(0) << '\n'; // calls ::get(long)

    return 0;
}
```

This program runs and prints 1.

Now, let’s say we update the Foolib library, which includes an updated Foolib.h that looks like this:

Foolib.h (updated):
```cpp
#ifndef FOOLIB_H
#define FOOLIB_H

namespace Foo
{
    int a { 20 };

    int get(int) { return 2; } // new function added
}
#endif
```

Once again, our main.cpp file hasn’t changed at all, but this program now compiles, runs, and prints 2!

When the compiler encounters a function call, it has to determine what function definition it should match the function call with. In selecting a function from a set of potentially matching functions, it will prefer a function that requires no argument conversions over a function that requires argument conversions. Because the literal 0 is an integer, C++ will prefer to match print(0) with the newly introduced print(int) (no conversions) over print(long) (which requires a conversion from int to long). That causes an unexpected change to our program behavior.