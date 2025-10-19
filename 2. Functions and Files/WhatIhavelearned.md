#  Nested functions are not supported

A function whose definition is placed inside another function is a nested function. Unlike some other programming languages, in C++, functions cannot be nested. The following program is not legal:

```cpp
#include <iostream>

int main()
{
    void foo() // Illegal: this function is nested inside function main()
    {
        std::cout << "foo!\n";
    }

    foo(); // function call to foo()

    return 0;
}
```

## What is return value?

The return expression produces the value to be returned. The return value is a **COPY** of that value.

But this word copy is controversional. Why?

Because when we inspect the code below:

```cpp

int function(){
    int y = 19;
    return y;
}

int x = function();
```
What we actually doing is creating a value y in memory and COPYING it to the x so we have 2 y values indeed. 

But when it comes to non-primitive types like strings. We are actually TRANSFERRING this data. Check this out:

```cpp
std::string function(){
    return "....'y. .e.......";
}

std::string secret = function();
```

What we are doing it is creating a string value NOT IN FUNCTION but IN THE SCOPE OF secret VARIABLE. So we actually did NOT create this object 2 times.


Compilers had priority for this type of situation, followings:

Pri 1: RVO (Return Value Optimization)
Which means creating the object NOT IN THE FUNCTION body BUT in the caller body.

Pri 2: Pointing out that variable which created IN FUNCTION body. But variable in caller body just pointing that variable. 

Pri 3: Copying the value.


So how we can understand which technique that c++ used to return this value?

Compiler will check from top to down in priorities:

It tries all of them.


Class that does RVO, besides copy and move.

class RVO_Class {
public:
    RVO_Class() { std::cout << "RVO_Class: Created (Default Constructor)\n"; }
    ~RVO_Class() { std::cout << "RVO_Class: Destroyed! (Destructor)\n"; }

    // Copy consturctor
    RVO_Class(const RVO_Class&) { std::cout << "RVO_Class: COPIED!\n"; }
    
    // Move constructor
    RVO_Class(RVO_Class&&) noexcept { std::cout << "RVO_Class: MOVED!\n"; }
};

Class that only be moveable.

class MoveOnly_Class {
public:
    std::string name;
    MoveOnly_Class(std::string n) : name(std::move(n)) { 
        std::cout << "MoveOnly_Class: Created (" << name << ")\n"; 
    }
    ~MoveOnly_Class() { 
        std::cout << "MoveOnly_Class: Destuctred (" << name << ")\n"; 
    }

    // Move consturctor: fast
    MoveOnly_Class(MoveOnly_Class&& other) noexcept : name(std::move(other.name)) {
        std::cout << "MoveOnly_Class: MOVED! (" << name << ")\n";
        other.name = "emptied";
    }

    // Move constuctor.
    MoveOnly_Class(const MoveOnly_Class&) =  { std::cout << "MoveOnly_Class: MOVED!\n"; }
    
    // Copy consturctor: Prohibited.
    MoveOnly_Class& operator=(const MoveOnly_Class&) = delete;
};


Class that only be copiyable.

class CopyOnly_Class {
public:
    CopyOnly_Class() { std::cout << "CopyOnly_Class: Created (Default)\n"; }
    ~CopyOnly_Class() { std::cout << "CopyOnly_Class: Destroyed\n"; }

    // Copy Constructor.
    CopyOnly_Class(const CopyOnly_Class&) {
        std::cout << "CopyOnly_Class: COPIED!\n";
    }

    // Move constructor: PROHIBITED OPENLY!
    // It forces to not use moving.
    CopyOnly_Class(CopyOnly_Class&&) = delete;
};


## Explicit function calls to main() are disallowed.


```cpp
void foo()
{
    main(); // Compile error: main not allowed to be called explicitly
}

void main() // Compile error: main not allowed to have non-int return type
{
    foo();
}
```

## Exit codes:

```cpp
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE

int main()
{
    return EXIT_SUCCESS; // OR EXIT_FAILIURE;
}
```

## A value-returning function that does not return a value will produce undefined behavior

A function that returns a value is called a **value-returning** function. A function is value-returning if the return type is anything other than void.

## Functions can only return a single value

A value-returning function can only return a single value back to the caller each time it is called.

## Parameter name of a function?

In a function definition, the name of a function parameter is optional. Therefore, in cases where a function parameter needs to exist but is not used in the body of the function, you can simply omit the name. A parameter without a name is called an unnamed parameter:

```cpp
void doSomething(int) // ok: unnamed parameter will not generate warning
{
}
```

## Optional(?) Why need we a function that has a unused parameter?

You’re probably wondering why we’d write a function that has a parameter whose value isn’t used. This happens most often in cases similar to the following:

    Let’s say we have a function with a single parameter. Later, the function is updated in some way, and the value of the parameter is no longer needed. If the now-unused function parameter were simply removed, then every existing call to the function would break (because the function call would be supplying more arguments than the function could accept). This would require us to find every call to the function and remove the unneeded argument. This might be a lot of work (and require a lot of retesting). It also might not even be possible (in cases where we did not control all of the code calling the function). So instead, we might leave the parameter as it is, and just have it do nothing.

    