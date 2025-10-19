## Defining unsigned numbers:

```cpp
unsigned short us;
unsigned int ui;
unsigned long ul;
unsigned long long ull;
```

## Unsigned integer range

![Unsigned integer bit ranges](size-of-each-unsignedbit-range.png)

## When to used unsigned numbers?

There are still a few cases in C++ where it’s okay / necessary to use unsigned numbers.

First, unsigned numbers are preferred when dealing with bit manipulation (covered in chapter O -- that’s a capital ‘o’, not a ‘0’). They are also useful when well-defined wrap-around behavior is required (useful in some algorithms like encryption and random number generation).

Second, use of unsigned numbers is still unavoidable in some cases, mainly those having to do with array indexing. We’ll talk more about this in the lessons on arrays and array indexing.

Also note that if you’re developing for an embedded system (e.g. an Arduino) or some other processor/memory limited context, use of unsigned numbers is more common and accepted (and in some cases, unavoidable) for performance reasons.
