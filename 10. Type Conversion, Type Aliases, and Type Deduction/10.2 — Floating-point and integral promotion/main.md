## Natural Data Size of a CPU

In modern CPU's, they are designed in a way that they perform most and efficient with a data type called "natural data size" of value.

So in order to perform more, compiler will convert some narrower data types in "natural data" which is int or double.


This process is called **numeric promotion**.


## Numeric promotion

Because C++ is designed to be portable and performant across a wide range of architectures, the language designers did not want to assume a given CPU would be able to efficiently manipulate values that were narrower than the natural data size for that CPU.

To help address this challenge, C++ defines a category of type conversions informally called the numeric promotions. **A numeric promotion is the type conversion of certain narrower numeric types (such as a char) to certain wider numeric types (typically int or double) that can be processed efficiently.**

**All numeric promotions are value-preserving.** A value-preserving conversion (also called a safe conversion) is one where every possible source value can be converted into an equal value of the destination type.

Because promotions are safe, the compiler will freely use numeric promotion as needed, and will not issue a warning when doing so.

```cpp
#include <iostream>

int main() {
    char a = 50;  // char, bellekte 1 bayt (8 bit) yer kaplar
    char b = 60;

    // C++ bu satırda otomatik olarak sayısal yükseltme yapar:
    // 1. 'a' ve 'b' önce 'int'e yükseltilir (genellikle 4 bayt/32 bit).
    // 2. Toplama işlemi (50 + 60) 'int' olarak yapılır.
    // 3. Sonuç, bir 'int' değişkenine atanır.
    
    auto sonuc = a + b; 
    
    std::cout << "Sonuç: " << sonuc << std::endl;  // Çıktı: 110
    std::cout << "Sonucun tipi: " << typeid(sonuc).name() << std::endl; 
    // Çıktı (genellikle): i (yani int)

    return 0;
}
```

## Numeric promitions are also beneficial in reducing redundancy.

Numeric promotion solves another problem as well. Consider the case where you wanted to write a function to print a value of type int:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

While this is straightforward, what happens if we want to also be able to print a value of type short, or type char? If type conversions did not exist, we’d have to write a different print function for short and another one for char. And don’t forget another version for unsigned char, signed char, unsigned short, wchar_t, char8_t, char16_t, and char32_t! You can see how this quickly becomes unmanageable.

Numeric promotion comes to the rescue here: we can write functions that have int and/or double parameters (such as the printInt() function above). That same code can then be called with arguments of types that can be numerically promoted to match the types of the function parameters.

## Numeric promotion categories

Integral and floating point promotion.

Floating Promitions are straitghforward.

Check this out:

```cpp
Using the floating point promotion rules, a value of type float can be converted to a value of type double.

This means we can write a function that takes a double and then call it with either a double or a float value:

#include <iostream>

void printDouble(double d)
{
    std::cout << d << '\n';
}

int main()
{
    printDouble(5.0); // no conversion necessary
    printDouble(4.0f); // numeric promotion of float to double

    return 0;
}
```

## Integral promotions

The integral promotion rules are more complicated.



Using the integral promotion rules, the following conversions can be made:

Note: Dont forget, promotions are value-safe. So it should not erase any value while promoting.


- signed char or signed short can be converted to int.
- unsigned char, char8_t, and unsigned short can be converted to int if int can hold the entire range of the type, or unsigned int otherwise.


Example for it:

The above explanation states: If the unsigned type being converted does not exceed the signed range of the converted type, the conversion takes place. If it exceeds it, it is converted to the unsigned type.

Note: The range of int (32-bit) is -2,147,483,647 to 2,147,483,647

unsigned short range: 0 to 65535


If we are promoting unsigned short to int. We first of check that whether the range of unsigned short is subset of the range of signed int? if it is yes. Then convert it. 

But something strange here that all wider types has contains the unsigned range of types that narrow then them. For instance (unsigned char and signed short,  unsigned short and signed int, unsigned int and long.)

But in old systems it might not be the case so short and int can be has the same range in actual. So that is the shell to overcome this issue.



- If char is signed by default, it follows the signed char conversion rules above. If it is unsigned by default, it follows the unsigned char conversion rules above.

- bool can be converted to int, with false becoming 0 and true becoming 1.

Assuming an 8 bit byte and an int size of 4 bytes or larger (which is typical these days), the above basically means that **bool, char, signed char, unsigned char, signed short, and unsigned short all get promoted to int.**

There are a few other integral promotion rules that are used less often. These can be found at https://en.cppreference.com/w/cpp/language/implicit_conversion#Integral_promotion.

In most cases, this lets us write a function taking an int parameter, and then use it with a wide variety of other integral types. For example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}
```

There are two things worth noting here. First, on some architectures (e.g. with 2 byte ints) it is possible for some of the unsigned integral types to be promoted to unsigned int rather than int.

Second, some narrower unsigned types (such as unsigned char) may be promoted to larger signed types (such as int). So while integral promotion is value-preserving, it does not necessarily preserve the signedness (signed/unsigned) of the type.


## So the all cast and conversions for narrow to natural data (wider) is promotion? No.

Some widening type conversions (such as char to short, or int to long) are not considered to be numeric promotions in C++ (they are numeric conversions, which we’ll cover shortly in lesson 10.3 -- Numeric conversions). This is because such conversions do not assist in the goal of converting smaller types to larger types that can be processed more efficiently.

The distinction is mostly academic. However, in certain cases, the compiler will favor numeric promotions over numeric conversions. We’ll see examples where this makes a difference when we cover function overload resolution (in upcoming lesson 11.3 -- Function overload resolution and ambiguous matches).

**Keywords of the file:**
- Natural data size,
- why promotion is necessary? 
- Promotion (integral and floating point promotions), 
- unsigned and signed range rule for promotiong. 
- Not every conversion from narrower to wider is not promotion.