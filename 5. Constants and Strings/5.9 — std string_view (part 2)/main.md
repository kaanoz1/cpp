## Destruction of viewer while owner is destroyed or moved. ??

## Warning:

It is important to note that a std::string_view remains dependent on the initializer through its lifetime. If the string being viewed is modified or destroyed while the view is still being used, unexpected or undefined behavior will result.

Whenever we use a view, it is up to us to ensure these possibilities do not occur.

Example:
```cpp

std::string dangerousFunction(){
    std::string x = "....'.. ........."
    return x;
}

int main(){
    std::string_view sv = dangerousFunction();

    std::cout << sv << std::endl;
    return 0;
}
```

## std::string_view is best used as a read-only function parameter

The best use for std::string_view is as a read-only function parameter. This allows us to pass in a C-style string, std::string, or std::string_view argument without making a copy, as the std::string_view will create a view to the argument.

```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str) // now a std::string_view, creates a view of the argument
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```

## Should I prefer std::string_view or const std::string& function parameters? Advanced

Prefer std::string_view in most cases. We cover this topic further in lesson 12.6 -- Pass by const lvalue reference.


## Do not initialize a std::string_view with a std::string literal, as this will leave the std::string_view dangling.

It is okay to initialize a std::string_view with a C-style string literal or a std::string_view literal. It’s also okay to initialize a std::string_view with a C-style string object, a std::string object, or a std::string_view object, as long as that string object outlives the view.

We can also get undefined behavior when the underlying string is modified:

```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, a!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    return 0;
}
```

## Revalidating an invalid std::string_view



```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, universe!"

    return 0;
}
```


## Be careful returning a std::string_view


std::string_view can be used as the return value of a function. However, this is often dangerous.

Because local variables are destroyed at the end of the function, returning a std::string_view that is viewing a local variable will result in the returned std::string_view being invalid, and further use of that std::string_view will result in undefined behavior. For example:

```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view getBoolName(bool b)
{
    std::string t { "true" };  // local variable
    std::string f { "false" }; // local variable

    if (b)
        return t;  // return a std::string_view viewing t

    return f; // return a std::string_view viewing f
} // t and f are destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    return 0;
}
```

In the above example, when getBoolName(true) is called, the function returns a std::string_view that is viewing t. However, t is destroyed at the end of the function. This means the returned std::string_view is viewing an object that has been destroyed. So when the returned std::string_view is printed, undefined behavior results.

Your compiler may or may not warn you about such cases.

There are two main cases where a std::string_view can be returned safely. First, because C-style string literals exist for the entire program, it’s fine (and useful) to return C-style string literals from a function that has a return type of std::string_view.

```cpp
#include <iostream>
#include <string_view>

std::string_view getBoolName(bool b)
{
    if (b)
        return "true";  // return a std::string_view viewing "true"

    return "false"; // return a std::string_view viewing "false"
} // "true" and "false" are not destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // ok

    return 0;
}
```

When getBoolName(true) is called, the function will return a std::string_view viewing the C-style string "true". Because "true" exists for the entire program, there’s no problem when we use the returned std::string_view to print "true" within main().

Second, it is generally okay to return a function parameter of type std::string_view:


```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view firstAlphabetical(std::string_view s1, std::string_view s2)
{
    if (s1 < s2)
        return s1;
    return s2;
}

int main()
{
    std::string a { "World" };
    std::string b { "Hello" };

    std::cout << firstAlphabetical(a, b) << '\n'; // prints "Hello"

    return 0;
}
```

## View modification functions


Consider a window in your house, looking at an electric car sitting on the street. You can look through the window and see the car, but you can’t touch or move the car. Your window just provides a view to the car, which is a completely separate object.

Many windows have curtains, which allow us to modify our view. We can close either the left or right curtain to reduce what we can see. We don’t change what’s outside, we just reduce the visible area.

Because std::string_view is a view, it contains functions that let us modify our view by “closing the curtains”. This does not modify the string being viewed in any way, just the view itself.

    The remove_prefix() member function removes characters from the left side of the view.
    The remove_suffix() member function removes characters from the right side of the view.



```cpp
#include <iostream>
#include <string_view>

int main()
{
	std::string_view str{ "Peach" };
	std::cout << str << '\n';

	// Remove 1 character from the left side of the view
	str.remove_prefix(1);
	std::cout << str << '\n';

	// Remove 2 characters from the right side of the view
	str.remove_suffix(2);
	std::cout << str << '\n';

	str = "Peach"; // reset the view
	std::cout << str << '\n';

	return 0;
}
```

Output:

```plaintext
Peach
each
ea
Peach
```

Note that: A C-style string literal and a std::string are always null-terminated.
A std::string_view may or may not be null-terminated.

In almost all cases, this doesn’t matter -- a std::string_view keeps track of the length of the string or substring it is viewing, so it doesn’t need the null-terminator. Converting a std::string_view to a std::string will work regardless of whether or not the std::string_view is null-terminated.


## A quick guide on when to use std::string vs std::string_view

This guide is not meant to be comprehensive, but is intended to highlight the most common cases:


Variables

Use a std::string variable when:

    You need a string that you can modify.
    You need to store user-inputted text.
    You need to store the return value of a function that returns a std::string.

Use a std::string_view variable when:

    You need read-only access to part or all of a string that already exists elsewhere and will not be modified or destroyed before use of the std::string_view is complete.
    You need a symbolic constant for a C-style string.
    You need to continue viewing the return value of a function that returns a C-style string or a non-dangling std::string_view.

Function parameters

Use a std::string function parameter when:

    The function needs to modify the string passed in as an argument without affecting the caller. This is rare.
    You are using language standard C++14 or older and aren’t comfortable using references yet.

For advanced readers

Also see 12.6 -- Pass by const lvalue reference.

Use a const std::string& function parameter when:

    You are using language standard C++14 or older, and the function needs a read-only string to work with (as std::string_view is not available until C++17).
    You are calling other functions that require a const std::string, const std::string&, or const C-style string (as std::string_view may not be null-terminated).

Use a std::string& function parameter when:

    You are using a std::string as an out-parameter (see 12.13 -- In and out parameters).
    You are calling other functions that require a std::string&, or non-const C-style string.

Return types

Use a std::string return type when:

    The return value is a std::string local variable or function parameter.
    The return value is a function call or operator that returns a std::string by value.

Use a std::string_view return type when:

    The function returns a C-style string literal or local std::string_view that has been initialized with a C-style string literal.
    The function returns a std::string_view parameter.

For advanced readers

See lesson 12.12 -- Return by reference and return by address for more information on returning reference types.

Use a std::string_view return type when:

    Writing an accessor for a std::string_view member.

Use a std::string& return type when:

    The function returns a std::string& parameter.

Use a const std::string& return type when:

    The function returns a const std::string& parameter.
    Writing an accessor for a std::string or const std::string member.
    The function returns a static (local or global) const std::string.

Insights

Things to remember about std::string:

    Initializing and copying std::string is expensive, so avoid this as much as possible.
    Avoid passing std::string by value, as this makes a copy.
    If possible, avoid creating short-lived std::string objects.
    Modifying a std::string will invalidate any views to that string.
    It is okay to return a local std::string by value.

Things to remember about std::string_view:

    std::string_view is typically used for passing string function parameters and returning string literals.
    Because C-style string literals exist for the entire program, it is always okay to set a std::string_view to a C-style string literal.
    When a string is destroyed, all views to that string are invalidated.
    Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
    A std::string_view may or may not be null-terminated.

TODO: REVIEW STRING_VIEWERS. C-STYLE STRINGS AND STRING LITERALS.