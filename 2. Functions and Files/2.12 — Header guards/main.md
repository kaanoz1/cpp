## Header Guards:

Consider the situation:

In upcoming examples, we’ll define some functions inside header files. You generally shouldn’t do this.

We are doing so here because it is the most effective way to demonstrate some concepts using functionality we’ve already covered.

square.h:
```cpp
int getSquareSides()
{
    return 4;
}
```

wave.h:
```cpp
#include "square.h"
```

main.cpp:
```cpp
#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}

```

Result is:

```cpp

int getSquareSides()  // from square.h
{
    return 4;
}

int getSquareSides() // from wave.h (via square.h)
{
    return 4;
}

int main()
{
    return 0;
}

```

The good news is that we can avoid the above problem via a mechanism called a header guard (also called an include guard). Header guards are conditional compilation directives that take the following form:


```cpp
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```

When this header is #included, the preprocessor will check whether SOME_UNIQUE_NAME_HERE has been previously defined in this translation unit. If this is the first time we’re including the header, SOME_UNIQUE_NAME_HERE will not have been defined. Consequently, it #defines SOME_UNIQUE_NAME_HERE and includes the contents of the file. If the header is included again into the same file, SOME_UNIQUE_NAME_HERE will already have been defined from the first time the contents of the header were included, and the contents of the header will be ignored (thanks to the #ifndef).

**All of your header files should have header guards on them.** SOME_UNIQUE_NAME_HERE can be any name you want, but by convention is set to the full filename of the header file, typed in all caps, using underscores for spaces or punctuation. For example, square.h would have the header guard:

square.h

```cpp
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

#endif
```

Review of our first example:

square.h:

```cpp
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

#endif
```

wave.h:

```cpp

#ifndef WAVE_H
#define WAVE_H

#include "square.h"

#endif

```

main.cpp

```cpp

#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```

Result of main.cpp:

```cpp
// Square.h included from main.cpp
#ifndef SQUARE_H // square.h included from main.cpp
#define SQUARE_H // SQUARE_H gets defined here

// and all this content gets included
int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H

#ifndef WAVE_H // wave.h included from main.cpp
#define WAVE_H
#ifndef SQUARE_H // square.h included from wave.h, SQUARE_H is already defined from above
#define SQUARE_H // so none of this content gets included

int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H
#endif // WAVE_H

int main()
{
    return 0;
}
```

## #pragma once (short for "pragmatic information")

Modern compilers support a simpler, alternate form of header guards using the #pragma preprocessor directive:

#pragma once serves the same purpose as header guards: to avoid a header file from being included multiple times. With traditional header guards, the developer is responsible for guarding the header (by using preprocessor directives #ifndef, #define, and #endif). With #pragma once, we’re requesting that the compiler guard the header. How exactly it does this is an implementation-specific detail.

Warning

The #pragma directive was designed for compiler implementers to use for whatever purposes they desire. As such, which pragmas are supported and what meaning those pragmas have is completely implementation-specific. With the exception of #pragma once, do not expect a pragma that works on one compiler to be supported by another.

## Summary of Header Guards:

Header guards are designed to ensure that the contents of a given header file are not copied more than once into any single file, in order to prevent duplicate definitions.

Duplicate declarations are fine -- but even if your header file is composed of all declarations (no definitions) it’s still a best practice to include header guards.

Note that header guards do not prevent the contents of a header file from being copied (once) into separate project files. This is a good thing, because we often need to reference the contents of a given header from different project files.