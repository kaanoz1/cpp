## Implicit Type Conversion Examples

```cpp
double d{ 3 }; // int value 3 implicitly converted to type double
d = 6; // int value 6 implicitly converted to type double
```

```cpp
float doSomething()
{
    return 3.0; // double value 3.0 implicitly converted to type float
}
```
```cpp
double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
```
```cpp
if (5) // int value 5 implicitly converted to type bool
{
}
```
```cpp
void doSomething(long l)
{
}

doSomething(3); // int value 3 implicitly converted to type long
```



## Standard Conversion Categories:

![Standard Conversion Category Table](conversion-category-table.png)


![Advanced Conversion Table](advanced-conversion-table.png)

## What happens If compiler cannot convert the type ?

Program is likely to fail in compilation phase. Via a compile error.


**Keywords of this file:**
- Implicit and Explicit Conversionn
- Conversion Categories