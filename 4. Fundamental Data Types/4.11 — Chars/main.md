## Extracting whitespace characters

Because extracting input ignores leading whitespace, this can lead to unexpected results when trying to extract whitespace characters to a char variable:

```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

Output:

```plaintext

Input a keyboard character: a b
You entered: a
You entered: b
```

In the above example, we may have expected to extract the space, but because leading whitespace is skipped, we extracted the b character instead.

One simple way to address this is to use the std::cin.get() function to perform the extraction instead, as this function does not ignore leading whitespace:


```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin.get(ch); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```

## Char size, range, and default sign

Char is defined by C++ to always be 1 byte in size. By default, a char may be signed or unsigned (though it’s usually signed). If you’re using chars to hold ASCII characters, you don’t need to specify a sign (since both signed and unsigned chars can hold values between 0 and 127).

If you’re using a char to hold small integers (something you should not do unless you’re explicitly optimizing for space), you should always specify whether it is signed or unsigned. A signed char can hold a number between -128 and 127. An unsigned char can hold a number between 0 and 255.

## Escape sequences

![Escaep Sequences](escape-sequences.png)


## What about the other char types, wchar_t, char8_t, char16_t, and char32_t?

Much like ASCII maps the integers 0-127 to American English characters, other character encoding standards exist to map integers (of varying sizes) to characters in other languages. The most well-known mapping outside of ASCII is the Unicode standard, which maps over 144,000 integers to characters in many different languages. Because Unicode contains so many code points, a single Unicode code point needs 32-bits to represent a character (called UTF-32). However, Unicode characters can also be encoded using multiple 16-bit or 8-bit characters (called UTF-16 and UTF-8 respectively).

char16_t and char32_t were added to C++11 to provide explicit support for 16-bit and 32-bit Unicode characters. These char types have the same size as std::uint_least16_t and std::uint_least32_t respectively (but are distinct types). char8_t was added in C++20 to provide support for 8-bit Unicode (UTF-8). It is a distinct type that uses the same representation as unsigned char.

You won’t need to use char8_t, char16_t, or char32_t unless you’re planning on making your program Unicode compatible. wchar_t should be avoided in almost all cases (except when interfacing with the Windows API), as its size is implementation-defined.

Unicode and localization are generally outside the scope of these tutorials, so we won’t cover it further. In the meantime, you should only use ASCII characters when working with characters (and strings). Using characters from other character sets may cause your characters to display incorrectly.


## Why not UTF-32 but UTF-8?

Since UTF-32 has 4 bytes and UTF-8 has 1 byte, it is obvious that UTF-32 has more character capacity then UTF-8. But why dont we use UTF-32 if it is more capable for communication. I browsered it and found that UTF-8 has minimimum capacity 1 byte and maximum for 4 bytes. It can be enhanced to the 4 byte whenever it is obligated with print a non-common value.