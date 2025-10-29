## Sentinal Value:
```cpp
// The reciprocal of x is 1/x
double reciprocal(double x)
{
    return 1.0 / x;
}
```

The reciprocal of some number x is defined as 1/x, and a number multiplied by its reciprocal equals 1.


However, what happens if the user calls this function as reciprocal(0.0)? We get a divide by zero error and a program crash, so clearly we should protect against this case. But this function must return a double value, so what value should we return? It turns out that this function will never produce 0.0 as a legitimate result, so we can return 0.0 to indicate an error case.

// The reciprocal of x is 1/x, returns 0.0 if x=0
constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace

double reciprocal(double x)
{
    if (x == 0.0)
       return error_no_reciprocal;

    return 1.0 / x;
}

A sentinel value is a value that has some special meaning in the context of a function or algorithm. In our reciprocal() function above, 0.0 is a sentinel value indicating that the function failed. The caller can test the return value to see if it matches the sentinel value -- if so, then the caller knows the function failed. While functions often return the sentinel value directly, returning a constant that describes the sentinel value can add additional readability.

## Fatal Error:

Fatal errors

If the error is so bad that the program can not continue to operate properly, this is called a non-recoverable error (also called a fatal error). In such cases, the best thing to do is terminate the program. If your code is in main() or a function called directly from main(), the best thing to do is let main() return a non-zero status code. However, if you’re deep in some nested subfunction, it may not be convenient or possible to propagate the error all the way back to main(). In such a case, a halt statement (such as std::exit()) can be used.

```cpp
double doIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);
    }
    return x / y;
}
```


## When to use std::cout vs std::cerr vs logging

## Invalid Input Validations:

```cpp
#include <iostream>

double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        std::cout << x / y << '\n';
        return;
    }
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    printResult(x, operation, y);

    return 0;
}
```

## Error case 2: Extraction succeeds but with extraneous input

Consider the following execution of the above program:

Enter a decimal number: 5*7

What do you think happens next?

Enter a decimal number: 5*7
Enter one of the following: +, -, *, or /: Enter a decimal number: 5 * 7 is 35

The program prints the right answer, but the formatting is all messed up. Let’s take a closer look at why.

When the user enters 5*7 as input, that input goes into the buffer. Then operator>> extracts the 5 to variable x, leaving *7\n in the buffer. Next, the program prints “Enter one of the following: +, -, *, or /:”. However, when the extraction operator was called, it sees *7\n waiting in the buffer to be extracted, so it uses that instead of asking the user for more input. Consequently, it extracts the ‘*’ character, leaving 7\n in the buffer.


After asking the user to enter another decimal number, the 7 in the buffer gets extracted without asking the user. Since the user never had an opportunity to enter additional data and hit enter (causing a newline), the output prompts all run together on the same line.

Although the above program works, the execution is messy. It would be better if any extraneous characters entered were simply ignored. Fortunately, it’s easy to ignore characters:

```cpp
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
```

To ignore all characters up to the next ‘\n’, we can pass `std::numeric_limits<std::streamsize>::max() to >std::cin.ignore(). std::numeric_limits<std::streamsize>::max()` returns the largest value that can be stored in a variable of type std::streamsize. Passing this value to std::cin.ignore() causes it to disable the count check.

To ignore everything up to and including the next ‘\n’ character, we call

std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

Because this line is quite long for what it does, it’s handy to wrap it in a function which can be called in place of std::cin.ignore().
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```

Since the last character the user entered is typically a ‘\n’, we can tell std::cin to ignore buffered characters until it finds a newline character (which is removed as well).

Let’s update our getDouble() function to ignore any extraneous input:
```cpp
double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;

    ignoreLine();
    return x;
}
```
Now our program will work as expected, even if we enter 5*7 for the first input -- the 5 will be extracted, and the rest of the characters will be removed from the input buffer. Since the input buffer is now empty, the user will be properly asked for input the next time an extraction operation is performed!

## Error case 3: Extraction fails

Extraction fails when no input can be extracted to the specified variable.

Now consider the following execution of our updated calculator program:

Enter a decimal number: a

You shouldn’t be surprised that the program doesn’t perform as expected, but how it fails is interesting:

Enter a decimal number: a
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.

and that last line keeps printing until the program is closed.

This looks pretty similar to the extraneous input case, but it’s a little different. Let’s take a closer look.

When the user enters ‘a’, that character is placed in the buffer. Then operator>> tries to extract ‘a’ to variable x, which is of type double. Since ‘a’ can’t be converted to a double, operator>> can’t do the extraction. Two things happen at this point: ‘a’ is left in the buffer, and std::cin goes into “failure mode”.

Once in “failure mode”, future requests for input extraction will silently fail. Thus in our calculator program, the output prompts still print, but any requests for further extraction are ignored. This means that instead waiting for us to enter an operation, the input prompt is skipped, and we get stuck in an infinite loop because there is no way to reach one of the valid cases.

In order to get std::cin working properly again, we typically need to do three things:

    Detect that a prior extraction has failed.
    Put std::cin back in normal operation mode.
    Remove the input that caused the failure (so the next extraction request doesn’t fail in an identical manner).

Here’s what that looks like:
```cpp
if (std::cin.fail()) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```
Because std::cin has a Boolean conversion indicating whether the last input succeeded, it’s more idiomatic to write the above as following:
```cpp

if (!std::cin) // If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // Put us back in 'normal' operation mode
    ignoreLine();     // And remove the bad input
}
```

Key insight

Once an extraction has failed, future requests for input extraction (including calls to ignore()) will silently fail until the clear() function is called. Thus, after detecting a failed extraction, calling clear() is usually the first thing you should do.

```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        // Our extraction succeeded
        ignoreLine(); // Ignore any additional input on this line
        return x;     // Return the value we extracted
    }
}
```

## Checking for EOF

There’s another case that we need to address.

An end-of-file (EOF) is a special error state that means “No more data available”. This is normally generated after an input operation fails due to no data being available. For example, if you were reading the contents of a file on disk, and then try to read in more data after you’ve already reached the end of the file, an EOF will be generated to tell you that no more data is available. In the case of file input, this is no problem -- we can just close the file and move on.

Now consider std::cin. If we try to extract input from std::cin and there is none, by design it won’t generate an EOF -- it will just wait for the user to enter more input. However, std::cin can generate an EOF in certain cases -- most commonly when the user enters a special key combination for their OS. Both Unix (via ctrl-D) and Windows (via ctrl-Z + ENTER) support entering an “EOF character” from the keyboard.

Key insight

In C++, EOF is an error state, not a character. Different OSes have special character combinations that are treated as a “user-entered EOF request”. These are sometimes called “EOF characters”.

When extracting data to std::cin and the user enters an EOF character, the behavior is OS-specific. Here’s what typically happens:

    If the EOF is not the first character of input: All input prior to the EOF will be flushed, and the EOF character is ignored. On Windows, any characters entered after the EOF are ignored, except for the newline.
    If the EOF is the first character entered: The EOF error will be set. The input stream may (or may not) be disconnected.

Although std::cin.clear() will clear an EOF error, if the input stream is disconnected, the next input request will generate another EOF error. This is problematic when our input is inside a while(true) loop, as we will get stuck in an infinite loop of EOF errors.

Since the intent of an keyboard-entered EOF character is to terminate the input stream, the best thing to do is detect the EOF (via std::cin.eof()) and then terminate the program.

Because clearing a failed input stream is something we’re likely to be checking for a lot, this is a good candidate for a reusable function:

```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```

## Putting it all together

Here’s our example calculator, updated with a few additional bits of error checking:
```cpp
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
```