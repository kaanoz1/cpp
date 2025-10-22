## Remainder with negative numbers

The remainder operator can also work with negative operands. x % y always returns results with the sign of x.

## Where’s the exponent operator?

You’ll note that the ^ operator (commonly used to denote exponentiation in mathematics) is a Bitwise XOR operation in C++ (covered in lesson O.3 -- Bit manipulation with bitwise operators and bit masks). C++ does not include an exponent operator.

To do exponents in C++, #include the <cmath> header, and use the pow() function:
```cpp
#include <cmath>

double x{ std::pow(3.0, 4.0) }; // 3 to the 4th power
``` 
Note that the parameters (and return value) of function pow() are of type double. Due to rounding errors in floating point numbers, the results of pow() may not be precise (even if you pass it integers or whole numbers).
