## std::string vs std::string_view

## Introducing std::string

The easiest way to work with strings and string objects in C++ is via the std::string type, which lives in the <string> header.

We can create objects of type std::string just like other objects:

```cpp
#include <string> // allows use of std::string

int main()
{
    std::string name {}; // empty string

    return 0;
}
```

Just like normal variables, you can initialize or assign values to std::string objects as you would expect:

```cpp
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    name = "John";               // change name to "John"

    return 0;
}
```

## String length:

Name is initialized with the string "Alex", which contains five characters (four explicit characters and a null-terminator). We then set name to a larger string, and then a smaller string. std::string has no problem handling this! You can even store really long strings in a std::string.

This is one of the reasons that std::string is so powerful.

## String input with std::cin

Using std::string with std::cin may yield some surprises! Consider the following example:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

Output:

```plaintext
Enter your full name: John Doe
Enter your favorite color: Your name is John and your favorite color is Doe
```

Hmmm, that isn’t right! What happened? It turns out that when using operator>> to extract a string from std::cin, operator>> only returns characters up to the first whitespace it encounters. Any other characters are left inside std::cin, waiting for the next extraction.

## Use std::getline() to input text

To read a full line of input into a string, you’re better off using the std::getline() function instead. std::getline() requires two arguments: the first is std::cin, and the second is your string variable.

```cpp
#include <iostream>
#include <string> // For std::string and std::getline

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // read a full line of text into name

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // read a full line of text into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```

```plaintext
Enter your full name: John Doe
Enter your favorite color: blue
Your name is John Doe and your favorite color is blue
```

## What the heck is std::ws?

In lesson 4.8 -- Floating point numbers, we discussed output manipulators, which allow us to alter the way output is displayed. In that lesson, we used the output manipulator function std::setprecision() to change the number of digits of precision that std::cout displayed.

C++ also supports input manipulators, which alter the way that input is accepted. **The std::ws input manipulator tells std::cin to ignore any leading whitespace before extraction.** Leading whitespace is any whitespace character (spaces, tabs, newlines) that occur at the start of the string.


Consider the following:


```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

Output:

```plaintext
Pick 1 or 2: 2
Now enter your name: Hello, , you picked 2
```

This program first asks you to enter 1 or 2, and waits for you to do so. All good so far. Then it will ask you to enter your name. However, it won’t actually wait for you to enter your name! Instead, it prints the “Hello” string, and then exits.

When you enter a value using operator>>, std::cin not only captures the value, it also captures the newline character ('\n') that occurs when you hit the enter key. So when we type 2 and then hit enter, std::cin captures the string "2\n" as input. It then extracts the value 2 to variable choice, leaving the newline character behind for later. Then, when std::getline() goes to extract text to name, it sees "\n" is already waiting in std::cin, and figures we must have previously entered an empty string! Definitely not what was intended.

We can amend the above program to use the std::ws input manipulator, to tell std::getline() to ignore any leading whitespace characters:

```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```

Output:
```plaintext
Pick 1 or 2: 2
Now enter your name: Alex
Hello, Alex, you picked 2
```

## Length of a string:

Use length() function.

```cpp
text.length(); //Excluding the null terminator.
```

Also note that std::string::length() returns an unsigned integral value (most likely of type size_t). If you want to assign the length to an int variable, you should static_cast it to avoid compiler warnings about signed/unsigned conversions:

```cpp
int length { static_cast<int>(name.length()) };
```

**Note**: Do not pass std::string by value, as it makes an expensive copy.

In most other cases, prefer to avoid returning a std::string by value, as doing so will make an expensive copy.



## Literals for std::string

Double-quoted string literals (like “Hello, world!”) are C-style strings by default (and thus, have a strange type).

We can create string literals with type std::string by using a s suffix after the double-quoted string literal. The s must be lower case.


```cpp
#include <iostream>
#include <string> // for std::string

int main()
{
    using namespace std::string_literals; // easy access to the s suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal

    return 0;
}
```

**Reminder**: We need to be careful not to mix signed and unsigned values. std::string::length() returns an unsigned value. If you’re C++20 capable, use std::ssize() to get the length as a signed value. Otherwise, static_cast the return value of std::string::length() to an int.