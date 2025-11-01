## Template does not have to be typename parameter.

## Implicit conversions for non-type template arguments Optional

```cpp
#include <iostream>

template <int N> // int non-type template parameter
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // no conversion necessary
    print<'c'>(); // 'c' converted to type int, prints 99

    return 0;
}
```

## Type deduction for non-type template parameters using auto C++17

```cpp
#include <iostream>

template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`

    return 0;
}
```