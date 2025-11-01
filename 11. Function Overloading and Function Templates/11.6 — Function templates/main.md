## Function templates

I know theme subject by generics but lets dive into what happens:

Optional reading:

In C++, the template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types.

Instead of manually creating a bunch of mostly-identical functions or classes (one for each set of different types), we instead create a single template. Just like a normal definition, a template definition describes what a function or class looks like. Unlike a normal definition (where all types must be specified), in a template we can use one or more placeholder types. A placeholder type represents some type that is not known at the time the template is defined, but that will be provided later (when the template is used).

Once a template is defined, the compiler can use the template to generate as many overloaded functions (or classes) as needed, each using different actual types!
Ezoic

The end result is the same -- we end up with a bunch of mostly-identical functions or classes (one for each set of different types). But we only have to create and maintain a single template, and the compiler does all the hard work to create the rest for us.

### Key insight

The compiler can use a single template to generate a family of related functions or classes, each using a different set of actual types.


Because the actual types aren’t determined until the template is used in a program (not when the template is written), the author of the template doesn’t have to try to anticipate all of the actual types that might be used. This means template code can be used with types that didn’t even exist when the template was written! We’ll see how this comes in handy later, when we start exploring the C++ standard library, which is absolutely full of template code!

For advanced readers

C++ supports 3 different kinds of template parameters:

- Type template parameters (where the template parameter represents a type).
Example: 
```cpp
template <typename T>
T add(T a, T b)
{
    return a + b;
}
```


- Non-type template parameters (where the template parameter represents a constexpr value).
```cpp
template <typename T, int Size>
class StaticArray
{
    T m_array[Size];
};
```
- Template template parameters (where the template parameter represents a template).
```cpp
template <typename T, template <typename...> class Container>
class Manager
{
    Container<T> storage; 
}
```

Type template parameters are by far the most common, so we’ll focus on those first. We’ll also discuss non-type template parameters, which are seeing increased usage in modern C++.



How can we define templates?
```cpp
template <typename T> // this is the template parameter declaration defining T as a type template parameter
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```

In our template parameter declaration, we start with the keyword template, which tells the compiler that we’re creating a template. Next, we specify all of the template parameters that our template will use inside angled brackets (<>). For each type template parameter, we use the keyword typename (preferred) or class, followed by the name of the type template parameter (e.g. T).



Note: There is no difference between the typename and class keywords in this context.

## Naming template parameters

```cpp
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}
```

If a type template parameter has a non-obvious usage or specific requirements that must be met, there are two common conventions for such names:

- Starting with a capital letter (e.g. Allocator). The standard library uses this naming convention.
- Prefixed with a T, then starting with a capital letter (e.g. TAllocator). This makes it easier to see that the type is a type template parameter.

**Key concepts of this file:**
- Templates
- Template functions
- How many kind of templates available in C++
- Template function definition.