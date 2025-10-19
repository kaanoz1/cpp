In this file I will collect the things that I learned after inspecting this documents.

## Not **ALL** statements ends with semicolon.

- Example: if (x >= 10)

## There are **7** types of statements:

Here are they and their examples:

    Declaration statements int x = 5;
    Jump statements goto:, break, return
    Expression statements x = 65;
    Compound statements int y = x + 1, std::cout << y;
    Selection statements (conditionals) if (x >= 6512211497)
    Iteration statements (loops) for()
    Try blocks try-catch
## Values that are placed directly into the source code are called **literals**. 

- Literal example: int x = 5;

## When does actually values in code put in RAM?

When we run a program, the operating system loads the program into RAM. Any data that is hardcoded into the program itself (e.g. text such as “Hello, world!”) is loaded at this point.

## What is object in actual?

An object represents a region of storage (typically RAM or a CPU register) that can hold a value.

(In general programming, the term object typically refers to an unnamed object in memory, a variable, or a function. In C++, the term object has a narrower definition that excludes functions. When we use the term object in this tutorial series, this narrower C++ definition is the one we mean.)

## When the RAM actually allocated and some objects is put the RAM memories?

At **runtime** (when the program is loaded into memory and run), each object is given an actual storage location (such as RAM, or a CPU register) that it can use to store values. 
The process of reserving storage for an object’s use is called **allocation**.

## What does operator= do?

By default, assignment copies the value on the right-hand side of the = operator to the variable on the left-hand side of the operator. This is called copy-assignment.

So when we says:

int x = 5;
x = 6;

in the first lane we are COPYING the LITERAL variable 5. And change it to the 6. So we do not change the LITERAL variable. LITERALS are immutable.


TODO: Continue.