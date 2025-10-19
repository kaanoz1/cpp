## Memory Addresses:

Each memory address refers to a 1 byte. A byte is a group of bits that are operated on as a unit. The modern standard is that a byte is comprised of 8 sequential bits. But byte do not have to consist of 8 bits.

## Fundamental data types

![Fundamental Data Types](fundamental-data-types.png)

## Other set of types:

C++ contains three sets of types.

The first two are built-in to the language itself (and do not require the inclusion of a header to use):

    1. The “fundamental data types” provide the most the basic and essential data types.
    2. The “compound data types” provide more complex data types and allow for the creation of custom (user-defined) types. We cover these in lesson 12.1 -- Introduction to compound data types.

    3. The third (and largest) set of types is provided by the C++ standard library. Because the standard library is included in all C++ distributions, these types are broadly available and have been standardized for compatibility. Use of the types in the standard library requires the inclusion of the appropriate header and linking in the standard library.


## The _t suffix

Many of the types defined in newer versions of C++ (e.g. std::nullptr_t) use a _t suffix. This suffix means “type”, and it’s a common nomenclature applied to modern types.

If you see something with a _t suffix, it’s probably a type. But many types don’t have a _t suffix, so this isn’t consistently applied.


## Void type

Void is the easiest of the data types to explain. Basically, void means “no type”!

Void is our first example of an incomplete type. An incomplete type is a type that has been declared but not yet defined.