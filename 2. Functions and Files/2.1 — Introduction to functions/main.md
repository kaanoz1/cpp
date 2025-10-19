The function initiating the function call is the **caller**, and the function being called (executed) is the **callee**. A function call is also sometimes called an invocation, with the caller invoking the **callee**.

Nested functions are not supported:

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