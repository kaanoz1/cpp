## Halts:

The last category of flow control statement we’ll cover in this chapter is the halt. A halt is a flow control statement that terminates the program. In C++, halts are implemented as functions (rather than keywords), so our halt statements will be function calls.

Let’s take a brief detour, and recap what happens when a program exits normally. When the main() function returns (either by reaching the end of the function, or via a return statement), a number of different things happen.

First, because we’re leaving the function, all local variables and function parameters are destroyed (as per usual).

Next, a special function called std::exit() is called, with the return value from main() (the status code) passed in as an argument. So what is std::exit()?

## The std::exit() function

std::exit() is a function that causes the program to terminate normally. Normal termination means the program has exited in an expected way. Note that the term normal termination does not imply anything about whether the program was successful (that’s what the status code is for). For example, let’s say you were writing a program where you expected the user to type in a filename to process. If the user typed in an invalid filename, your program would probably return a non-zero status code to indicate the failure state, but it would still have a normal termination.

## std::exit() does not clean up local variables

One important note about calling std::exit() explicitly: std::exit() does not clean up any local variables (either in the current function, or in functions up the call stack). This means calling std::exit() can be dangerous if your program relies on any local variables cleaning themselves up.

## std::atexit

Because std::exit() terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc…

To assist with this, C++ offers the std::atexit() function, which allows you to specify a function that will automatically be called on program termination via std::exit().

```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

A few notes here about std::atexit() and the cleanup function: First, because std::exit() is called implicitly when main() terminates, this will invoke any functions registered by std::atexit() if the program exits that way. Second, the function being registered must take no parameters and have no return value. Finally, you can register multiple cleanup functions using std::atexit() if you want, and they will be called in reverse order of registration (the last one registered will be called first).

## std::abort and std::terminate

C++ contains two other halt-related functions.

The std::abort() function causes your program to terminate abnormally. Abnormal termination means the program had some kind of unusual runtime error and the program couldn’t continue to run. For example, trying to divide by 0 will result in an abnormal termination. std::abort() does not do any cleanup.

```cpp
#include <cstdlib> // for std::abort()
#include <iostream>

int main()
{
    std::cout << 1 << '\n';
    std::abort();

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```

The std::terminate() function is typically used in conjunction with exceptions (we’ll cover exceptions in a later chapter). Although std::terminate can be called explicitly, it is more often called implicitly when an exception isn’t handled (and in a few other exception-related cases). By default, std::terminate() calls std::abort().

## When should you use a halt?

The short answer is “almost never”. Destroying local objects is an important part of C++ (particularly when we get into classes), and none of the above-mentioned functions clean up local variables. Exceptions are a better and safer mechanism for handling error cases.

