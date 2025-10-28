## Unnamed (anonymous) namespaces

An unnamed namespace (also called an anonymous namespace) is a namespace that is defined without a name, like so:
```cpp
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

All content declared in an unnamed namespace is treated as if it is part of the parent namespace. So even though function doSomething() is defined in the unnamed namespace, the function itself is accessible from the parent namespace (which in this case is the global namespace), which is why we can call doSomething() from main() without any qualifiers.

Unnamed namespaces are typically used when you have a lot of content that you want to ensure stays local to a given translation unit, as it’s easier to cluster such content in a single unnamed namespace than individually mark all declarations as static. Unnamed namespaces will also keep program-defined types (something we’ll discuss in a later lesson) local to the translation unit, something for which there is no alternative equivalent mechanism to do.