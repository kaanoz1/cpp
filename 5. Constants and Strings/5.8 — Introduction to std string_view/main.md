## Initializing std::string is slow. (Since it does copy the variable)

```cpp
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    printString(s);

    return 0;
}
```
This example makes two copies of the C-style string “Hello, world!”: one when we initialize s in main(), and another when we initialize parameter str in printString(). **That’s a lot of needless copying just to print a string!**

## std::string_view

To address the issue with std::string being expensive to initialize (or copy), C++17 introduced std::string_view (which lives in the <string_view> header). std::string_view provides read-only access to an existing string (a C-style string, a std::string, or another std::string_view) without making a copy. Read-only means that we can access and use the value being viewed, but we can not modify it.

The following example is identical to the prior one, except we’ve replaced std::string with std::string_view.

```cpp
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```

When we initialize std::string_view s with C-style string literal "Hello, world!", s provides read-only access to “Hello, world!” without making a copy of the string. When we pass s to printSV(), parameter str is initialized from s. This allows us to access “Hello, world!” through str, again without making a copy of the string.


## std::string_view can be initialized with many different types of strings

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view s1 { "Hello, world!" }; // initialize with C-style string literal
    std::cout << s1 << '\n';

    std::string s{ "Hello, world!" };
    std::string_view s2 { s };  // initialize with std::string
    std::cout << s2 << '\n';

    std::string_view s3 { s2 }; // initialize with std::string_view
    std::cout << s3 << '\n';

    return 0;
}
```

## std::string_view parameters will accept many different types of string arguments

Function definitions:

```cpp
void printSV(std::string_view str)
```

Usage:

```cpp
printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view
```

## std::string_view will not implicitly convert to std::string

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printString(std::string str)
{
	std::cout << str << '\n';
}

int main()
{
	std::string_view sv{ "Hello, world!" };

	// printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string

	std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string

	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

	return 0;
}
```

## Assignment changes what the std::string_view is viewing

Assigning a new string to a std::string_view causes the std::string_view to view the new string. It does not modify the prior string being viewed in any way.

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string name { "Alex" };
    std::string_view sv { name }; // sv is now viewing name
    std::cout << sv << '\n'; // prints Alex

    sv = "John"; // sv is now viewing "John" (does not change name)
    std::cout << sv << '\n'; // prints John

    std::cout << name << '\n'; // prints Alex

    return 0;
}
```
But da fuq? I just said string_view is readonly. Yes they are, you cannot change the string_view's content. by sv[0] = "A". Impossible.

Check this example:

string name = "Alex"

Now name is looking for Alex; name -> Alex.
then:

string_view sv = name;

Then string_view is also looking for Alex. Which is the same string.

name -> & sv -> Alex.

But when ever you do sv = "Kaan"
Now, it looks seperate data.

sv -> "Kaan"
whereas 
name -> "Alex"

## Literals for std::string_view

Double-quoted string literals are C-style string literals by default. We can create string literals with type std::string_view by using a sv suffix after the double-quoted string literal. The sv must be lower case.


```cpp
#include <iostream>
#include <string>      // for std::string
#include <string_view> // for std::string_view

int main()
{
    using namespace std::string_literals;      // access the s suffix
    using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    return 0;
}
```