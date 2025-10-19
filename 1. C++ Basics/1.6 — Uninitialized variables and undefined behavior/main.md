Unlike some programming languages, C/C++ does not automatically initialize most variables to a given value (such as zero). 

When a variable that is not initialized is given a memory address to use to store data, the default value of that variable is whatever (garbage) value happens to already be in that memory address!

A variable that has not been given a known value (through initialization or assignment) is called an uninitialized variable.

“Initialized” and “uninitialized” to be strict opposites, but they aren’t quite!

“Uninitialized” means the object has not been given a known value yet (through any means, including assignment). Therefore, an object that is not initialized but is then **assigned** a value is no longer uninitialized (because it has been given a known value).

Using the values of uninitialized variables can lead to unexpected results. Consider the following short program:

```cpp
#include <iostream>

int main()
{
    // define an integer variable named x
    int x; // this variable is uninitialized because we haven't given it a value

    // print the value of x to the screen
    std::cout << x << '\n'; // who knows what we'll get, because x is uninitialized

    return 0;
}
```

In this case, the computer will assign some unused memory to x. It will then send the value residing in that memory location to std::cout, which will print the value (interpreted as an integer). But what value will it print? The answer is “who knows!”, and the answer may (or may not) change every time you run the program. When the author ran this program in Visual Studio, std::cout printed the value 7177728 one time, and 5277592 the next. Feel free to compile and run the program yourself (your computer won’t explode).

Why this happens? Because one program is terminated that program does not clean your exact RAM adderss with 000000..000; Just points out there it is not used anymore. When our main program got executed x got a address value from our RAM. And if it coincidence with that TRASH value. (meant that old value that not used anymore) is got for x now. So it can be anything.

## Undefined behavior

Undefined behavior (often abbreviated UB) is the result of executing code whose behavior is not well-defined by the C++ language.

Might resulted in:

    Your program produces different results every time it is run.
    Your program consistently produces the same incorrect result.
    Your program behaves inconsistently (sometimes produces the correct result, sometimes not).
    Your program seems like it’s working but produces incorrect results later in the program.
    Your program crashes, either immediately or later.
    Your program works on some compilers but not others.
    Your program works until you change some other seemingly unrelated code.

## Implementation-defined behavior and unspecified behavior

A specific compiler and the associated standard library it comes with are called an implementation (as these are what actually implements the C++ language).

A specific compiler and the associated standard library it comes with are called an implementation (as these are what actually implements the C++ language).

Behavior that is defined by the implementation is called implementation-defined behavior. Implementation-defined behavior must be documented and consistent for a given implementation.



Let’s look at a simple example of implementation-defined behavior:
```cpp
#include <iostream>

int main()
{
	std::cout << sizeof(int) << '\n'; // print how many bytes of memory an int value takes

	return 0;
}
```
On most platforms, this will produce 4, but on others it may produce 2.

## Unspecified Behaviour

Undefined behavior is the result of executing code whose behavior is not well defined by the language. The result can be almost anything, including something that behaves correctly.

### Examples of UB, US, IDB

UB:

    - Reading an uninitialized variable:

    ```cpp
        int x;
        std::cout << x; // UB: 'x' contains a garbage value.
    ```

    - Accessing an array out of bounds:

    ```cpp
        int my_array[5] = {1, 2, 3, 4, 5};
        std::cout << my_array[10]; // UB: The valid indices are 0 through 4.
    ```
    - Dereferencing a null pointer:

    ```cpp
        int* ptr = nullptr;
        int value = *ptr; // UB: Attempting to read from memory address 0.
    ```

    - Signed integer overflow:

    ```cpp
        int x = 2'147'483'647; // Maximum value for a 32-bit signed int
        x = x + 1; // UB: The result cannot be represented. (Note: unsigned overflow is well-defined)
    ```

    - Modifying a variable twice between sequence points (a classic example, though modern C++ rules are stricter, this general idea holds):

    ```cpp
        int i = 5;
        i = ++i + 1; // UB: 'i' is modified twice without a sequence point in between.
            // A more modern example: v[i] = i++;
    ```

US-B:

    - Order of evaluation of function arguments

    ```cpp
        int x = 1;
        auto f = [&]() { x = 2; return 0; };
        auto g = [&]() { return x; };

        // Önce f() mi g() mi çağrılacak? Bilinmiyor (Unspecified).
        // Önce f() çağrılırsa, çıktı: (0, 2)
        // Önce g() çağrılırsa, çıktı: (0, 1)
        printf("%d, %d\n", f(), g());
    ```


    - Order of evaluation of operands in an expression

    ```cpp
        int result = f() + g();
    ```

    - The value of members in a union after another member is initialized:

    ```cpp
        union MyUnion {
            int i;
            float f;
        };
        MyUnion u = { 10 }; // u.i = 10'dur.
    ```

IDB:

    - The size of fundamental types (Temel türlerin boyutu):

    ```cpp
        size_t s = sizeof(int);
    ```

    - Whether char is signed or unsigned (char türünün işaretli mi işaretsiz mi olduğu):

    ```cpp
        char c = 200; // 200, ikilik tabanda 11001000'dir.

        int i = c;
    ```

The differences between Undefined Behvariour, Unspecified Behaviour and Implmeneted Defined Behaviour:

| Feature | Undefined Behaviour | Unspecified Behaviour | Implementation-Defined 
| --------------- | --------------- | --------------- | --------------- |
| Standard Rule | NO RULES AT ALL | A list that "might happend" exists | A list that "might happend" exists |
| Result | Eveything might happen.  | Cannot estimated. But we know that something will occur in that list. | Can be estimated. |
| Documentation needed? | No, this is an error. | No. | Yes, have to.| 
| Danger Level | VERY | Not trusted, not dangerous. | Safe. |


What is documentation? 