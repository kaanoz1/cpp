## Type aliases

In C++, **using** is a keyword that creates an alias for an existing data type. To create such a type alias, we use the **using** keyword, followed by a name for the type alias, followed by an equals sign and an existing data type. For example:

`using Distance = double; // define Distance as an alias for type double`

Once defined, a type alias can be used anywhere a type is needed. For example, we can create a variable with the type alias name as the type:

```cpp
Distance milesToDestination{ 3.4 }; // defines a variable of type double
```

## The scope of a type alias

Because scope is a property of an identifier, **type alias identifiers follow the same scoping rules as variable identifiers**: 

## Typedefs

A typedef (which is short for “type definition”) is an older way of creating an alias for a type. To create a typedef alias, we use the typedef keyword:

```cpp
// The following aliases are identical
typedef long Miles;
//typedef Miles long is valid also.
using Miles = long;
```

Second, the syntax for typedefs can get ugly with more complex types. For example, here is a hard-to-read typedef, along with an equivalent (and slightly easier to read) type alias:
```cpp
typedef int (*FcnType)(double, char); // FcnType hard to find
using FcnType = int(*)(double, char); // FcnType easier to find
```

Da fuq?

## Using type aliases to make complex types easier to read

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
{
    // some code here
    return false;
}

int main()
{
     std::vector<std::pair<std::string, int>> pairlist;

     return 0;
}
```

What about this?

```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}

int main()
{
     VectPairSI pairlist; // instantiate a VectPairSI variable

     return 0;
}
```

**Key concepts of this file:**
- Type aliases
- Scope of type aliases
- How can you define type alises? using and typedef keywords.



