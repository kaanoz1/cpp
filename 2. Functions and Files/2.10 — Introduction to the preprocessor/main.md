# About compilation

Before each file getting compile it goes a preprocessor state. In this state compiler makes some bunch of changes in your code.

Whenever preprocessor done its job the output is called as translation unit.

When preprocessor run, it looks for, from top to bottom, for preprocessor directives. They start with # symbols.

Directive **#include**:

When you #include a file, the preprocessor replaces the #include directive with the contents of the included file. The included contents are then preprocessed (which may result in additional #includes being preprocessed recursively), then the rest of the file is preprocessed.

Consider the following program:

```cpp

#include <iostream>

int main()
{
    std::cout << "Hello, world!\n";
    return 0;
}

```

When the preprocessor runs on this program, the preprocessor will replace #include <iostream> with the contents of the file named “iostream” and then preprocess the included content and the rest of the file.

Directive **Macro defines**:

In C++, a macro is a rule that defines how input text is converted into replacement output text.

The #define directive can be used to create a macro.

There are two basic types of macros: object-like macros, and function-like macros.

Object-like macros can be defined in one of two ways:

```cpp
#define IDENTIFIER
#define IDENTIFIER substitution_text
```

The identifier for a macro uses the same naming rules as normal identifiers: they can use letters, numbers, and underscores, cannot start with a number, and should not start with an underscore. By convention, macro names are typically all uppercase, separated by underscores.

Object-like macros with substitution text:

```cpp
#include <iostream>

#define MY_NAME "Alex"

int main()
{
    std::cout << "My name is: " << MY_NAME << '\n';

    return 0;
}
```

The output of preprocessor is:

```cpp
// The contents of iostream are inserted here

int main()
{
    std::cout << "My name is: " << "Alex" << '\n';

    return 0;
}
```

Object-like macros without a substituation text:

Conditional compilation:

The conditional compilation preprocessor directives allow you to specify under what conditions something will or won’t compile. There are quite a few different conditional compilation directives, but we’ll only cover a few that are used the most often: #ifdef, #ifndef, and #endif.

The #ifdef preprocessor directive allows the preprocessor to check whether an identifier has been previously defined via #define. If so, the code between the #ifdef and matching #endif is compiled. If not, the code is ignored.

```cpp

#include <iostream>

#define PRINT_JOE

int main()
{
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif

    return 0;
}
```
#ifndef is the opposite of #ifdef, in that it allows you to check whether an identifier has NOT been #defined yet.

```cpp
#include <iostream>

int main()
{
#ifndef PRINT_BOB
    std::cout << "Bob\n";
#endif

    return 0;
}
```

# #if 0 ?

One more common use of conditional compilation involves using #if 0 to exclude a block of code from being compiled (as if it were inside a comment block):

```cpp
#include <iostream>

int main()
{
    std::cout << "Joe\n";

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    std::cout << "Steve\n";
#endif // until this point

    return 0;
}
```

# The scope of #defines

Directives are resolved before compilation, from top to bottom on a **file-by-file** basis.

And since #include directive just copy the content of the file so we can copy our macros. Check this out:

Alex.h:

```cpp
#define MY_NAME "Alex"
```

main.cpp:

```cpp

#include "Alex.h" // copies #define MY_NAME from Alex.h here
#include <iostream>

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n'; // preprocessor replaces MY_NAME with "Alex"

	return 0;
}

```

Once the preprocessor has finished, all defined identifiers from that file are discarded. This means that directives are only valid from the point of definition to the end of the file in which they are defined. Directives defined in one file do not have any impact on other files (unless they are #included into another file). For example:

function.cpp:

```cpp
#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}
```

main.cpp:

```cpp

void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();

    return 0;
}

```

Output will be:

```text
Not printing!
```

