## Numeric Conversions Examples:

1. int to any integral types:
```cpp
short s = 3; // convert int to short
long l = 3; // convert int to long
char ch = s; // convert short to char
unsigned int u = 3; // convert int to unsigned int
```

2. Converting a floating point type to any other floating point type (excluding floating point promotions):
```cpp
float f = 3.0; // convert double to float
long double ld = 3.0; // convert double to long double
```

3. Converting a floating point type to any integral type:
```cpp
int i = 3.5; // convert double to int Note: This couldn't be done by braces initializtions. e.g: int i { 3.5 }
```

4. Converting an integral type to any floating point type:
```cpp
double d = 3; // convert int to double
```

5. Converting an integral type or a floating point type to a bool:
```cpp
bool b1 = 3; // convert int to bool
bool b2 = 3.0; // convert double to bool
```

## Numeric Conversions:

1. Safe Conversions. "Value-preserving conversions are safe numeric conversions where the destination type can exactly represent all possible values in the source type."

So how can we decide a conversion from type x to type y is safe? Check the range of the x and y. If y contains the x, then it is safe.

Example:

int to long. int range: [-2,1 milion to 2.1 milion] long? [-9 trilion to 9 triliaon] does range of the long contains the range of int? Yes. Then int to long conversions are safe. So you can get back this conversion and you will get the value exatly same as you had.

How it works? When Safe conversions done, it only change the bits that requires. So if we are trying to convert int (32-bit) to long (64-bit) it only adds bits to the left. 

2. Reinterpretive conversions are unsafe numeric conversions where the converted value may be different than the source value, but no data is lost. Signed/unsigned conversions fall into this category.

How it works:
Bits does not change. Just the way compiler interpret the bits is changed.

For example, when converting a signed int to an unsigned int:

```cpp
int main()
{
    int n1 { 5 };
    unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

    int n2 { -5 };
    unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

    return 0;
}
```

In the case of u1, the signed int value 5 is converted to unsigned int value 5. Thus, the value is preserved in this case.

3. Lossy conversions are unsafe numeric conversions where data may be lost during the conversion.

For example, double to int is a conversion that may result in data loss:
```cpp
int i = 3.0; // okay: will be converted to int value 3 (value preserved)
int j = 3.5; // data lost: will be converted to int value 3 (fractional value 0.5 lost)
```
Conversion from double to float can also result in data loss:


```cpp
float f = 1.2;        // okay: will be converted to float value 1.2 (value preserved)
float g = 1.23456789; // data lost: will be converted to float 1.23457 (precision lost)
```


Note that Promotions is sub-action of Conversion. So every promotion is a conversion but vice versa is not true.
**Keywords of this file:**
- What is Numeric Conversion?
- What are numberic conversion categories?
    - What is the Safe Conversion and how does it work?
    - What is Reinterpretive conversion and how does it work?
    - What is Lossy Conversion and how does it work?