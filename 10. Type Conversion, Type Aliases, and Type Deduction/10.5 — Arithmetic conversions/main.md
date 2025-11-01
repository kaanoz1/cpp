## Arithmetic Operators

Binary operator+ is given two operands, both of type int. Because both operands are of the same type, that type will be used to perform the calculation, and the value returned will also be of this same type. Thus, 2 + 3 will evaluate to int value 5.

But what happens when the operands of a binary operator are of different types?

??? y { 2 + 3.5 };
In this case, operator+ is being given one operand of type int and another of type double. Should the result of the operator be returned as an int, a double, or possibly something else altogether?

In C++, certain operators require that their operands be of the same type. If one of these operators is invoked with operands of different types, one or both of the operands will be implicitly converted to matching types using a set of rules called the usual arithmetic conversions. The matching type produced as a result of the usual arithmetic conversion rules is called the common type of the operands.

## The operators that require operands of the same type

The following operators require their operands to be of the same type:

The binary arithmetic operators: +, -, *, /, %
The binary relational operators: <, >, <=, >=, ==, !=
The binary bitwise arithmetic operators: &, ^, |
The conditional operator ?: (excluding the condition, which is expected to be of type bool)

## The usual arithmetic conversion rules

The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list of types that looks something like this:

1. long double (highest rank)
2. double
3. float
4. long long
5. long
6. int (lowest rank)

The following rules are applied to find a matching type:

Step 1:

- If one operand is an integral type and the other a floating point type, the integral operand is converted to the type of the floating point operand (no integral promotion takes place). 
- Otherwise, any integral operands are numerically promoted (see 10.2 -- Floating-point and integral promotion).



Step 2:
- After promotion, if one operand is signed and the other unsigned, special rules apply (see below)
- Otherwise, the operand with lower rank is converted to the type of the operand with higher rank.

Lets take a senarios:
Scenario 1:
```cpp
    char + long;
``` 

For step 1 and subrule 1: is one of them in the type of floating point and the other one is integral? No.

For step 1 and subrule 2: Then promotion: `char + long` promoted to `int + long`

Then step 2 and subrule 1: if the signed statues are opposite, use special rules. which is not the case.
Then step 2 and subrule 2: then since the operand types are not the same turn lower to hight so `int + long` convert into int to long `long + long`.




**For advanced readers**

### The special matching rules for integral operands with different signs:

- If the rank of the unsigned operand is greater than or equal to the rank of the signed operand, the signed operand is converted to the type of the unsigned operand.

Example: We have `unsigned x` and `signed y`  if `x` >= `y` then turn `signed y` to `unsigned y`. e.g.
`unsigned int x + signed int y` = `unsigned int x + unsigned int y`
or
`unsigned long x + signed int y` = `unsigned long x + unsigned long y` (step 2, special rules)

- If the type of the signed operand can represent all the values of the type of the unsigned operand, the type of the unsigned operand is converted to the type of the signed operand.

Example: We have `unsigned x` and `signed y`  if `range of signed y` consist of `range of unsigned x` then turn `unsigned x` to `signed y`. e.g.

`long + unsigned int` Since [-9,1 trillion to 9,1 trillion] consist [0 to 4,2 million] then turn unsigned int to signed. So
`long + unsigned int` to `signed int` then convert the int to long. (Since the long has more priority)

- Otherwise both operands are converted to the corresponding unsigned type of the signed operand.

INSPECT FOR ALL USUAL ARITHMETIC CONVERSIONS BY [HERE](https://en.cppreference.com/w/cpp/language/usual_arithmetic_conversions.html)

- Otherwise turn signed to unsigned type.

## Examples:

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    int i{ 2 };
    std::cout << typeid(i).name() << '\n'; // show us the name of the type for i

    double d{ 3.5 };
    std::cout << typeid(d).name() << '\n'; // show us the name of the type for d

    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}
```

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```

## Signed and unsigned issues

```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer

    return 0;
}
```

```cpp
#include <iostream>

int main()
{
    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
```

## std::common_type and std::common_type_t

In future lessons, we’ll encounter cases where it is useful to know what the common type of two type is. `std::common_type` and the useful type alias `std::common_type_t` (both defined in the `<type_traits>` header) can be used for just this purpose.

For example, `std::common_type_t<int, double>` returns the common type of int and double, and `std::common_type_t<unsigned int, long>` returns the common type of unsigned int and long.

**Key concepts of this file:**
    - What is arithmetic conversion?
    - Arithmeic conversition priotiry order.
    - Arithemtic conversion rules:
        - Steps for arithmetic conversions:
        - Numerical promotion for arithmetic conversion
        - Signed and unsigned issues and **special rules**
        