## What is the order for passing a variable which to be casted?

Inspect the code:

```cpp
#include <iostream>

void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5); // what happens when we pass an int value?

	return 0;
}
```

int argument ->casted to double argument -> copied -> assigned to x in print function.

When the compiler does type conversion on our behalf without us explicitly asking, we call this **implicit type conversion.**

## Type conversion of a value produces a new value

The type conversion process does not modify the value (or object) supplying the data to be converted. Instead, the conversion process uses that data as input, and produces the converted result.


## Key insight about conversion

The type conversion of a value to another type of value behaves much like a call to a function whose return type matches the target type of the conversion. The data to be converted is passed in as an argument, and the converted result is returned (in a temporary object) to be used by the caller.


## Explicit Conversion 

```cpp
static_cast<new_type>(expression)

//Example:


double d = 5.0;
int x = static_cast<int>(d);

```

Check this program below:
```cpp
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int

	return 0;
}
```


## Sign conversions using static_cast

```cpp
#include <iostream>

int main()
{
    unsigned int u1 { 5 };
    // Convert value of u1 to a signed int
    int s1 { static_cast<int>(u1) };
    std::cout << s1 << '\n'; // prints 5

    int s2 { 5 };
    // Convert value of s2 to an unsigned int
    unsigned int u2 { static_cast<unsigned int>(s2) };
    std::cout << u2 << '\n'; // prints 5

    return 0;
}
```

```plaintext
5
5
```

Check this also:

```cpp
#include <iostream>

int main()
{
    int s { -1 };
    std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

    unsigned int u { 4294967295 }; // largest 32-bit unsigned int
    std::cout << static_cast<int>(u) << '\n'; // implementation-defined prior to C++20, -1 as of C++20

    return 0;
}
```
Output would be:

```plaintext
4294967295
-1
```