We are on the step called: 

## "Step 4: Compiling your source code"


![graph](./image.png)

When compiler begins to compile the whole project it sequentially compile each source code file which is cpp file and does two things:

1. Checks the grammer of the files to prevent syntax error.

2. And then turn your code into machine code so the hardware can understand it. These instructions are stored in an intermediate file called an **object file.** The object file also contains other data that is required or useful in subsequent steps.

(There are question that come to my mind. I will discuss it later.)


Object files has extension of .obj (or .o but less usual) and has name of the cpp file that it get origined from.

For example, if your program had 3 .cpp files, the compiler would generate 3 object files:

![Object Files](obj.png)

## Step 5: Linking object files and libraries and creating the desired output file


After the compilation **Linker** comes into play. It links all the .obj files and needed libraries to produce desired output. This process is called as **linking**.

Linker sequence: 1. Reades all necessarry obj and library files and checks they are valid. 2. Second, the linker ensures all cross-file dependencies are resolved properly. For example, if you define something in one .cpp file, and then use it in a different .cpp file, the linker connects the two together. If linker could not do this, you will get an error. 3. Third, the linker typically links in one or more library files.

Finally, the linker outputs the desired output file. 

![Linking](linking.png)


### The standart library

Library that provided by cpp itself that includes vital operations about a program.


### Building 

Building is full process of converting source code files into an executable that can be run.

## Steps 6 & 7: Testing and Debugging

Nothing new.

#### My questions about compiling and .obj file sequence. My questions are:

1. are .obj files the files of result of compilation each cpp files individually?

2. Are all obj files recombined to produce desired output? (Yes, documentation already gave the answer)

3. What are the compilation sequence of a bunch of files like, is it queue or stack? Inspect the files:



main.cpp:

#include <firstofthesecond>
#include <secondofthesecond>

firstofthesecond.cpp:

#include <firstofthethird>

secondofthesecond.cpp:

#include<secondofthethird>

If it was queue, it will like this sequence:

main -> firstofthesecond -> secondofthesecond -> firstofthethird -> secondofthethird

If it was stack:

main -> firstofthesecond -> first of the third -> secondofthesecond -> secondofthethird.

Which one is true?


#### Answers of my individual questions:

1. Yes. Each cpp file compiled invidually and produces .obj (in Windows) or .o (in Linux) file.

2. Answered.

3. Not the both. The critical difference is that Preprocessors and compilation.

#include statements are preprocessors. include statements does not decide the compilation sequence. You are not includeing a cpp file by include statement but a header file like .h or .hpp. Preprocessor just **COPY** the **WHOLE** header file and paste it to the correspoding #include file.

After pasting all #include statemtn we have only one enourmous cpp file and compiler **ONLY** compile main.cpp and gets the main.obj.

Mean: Compiler does not even know about firstofthesecond.cpp or all the other stuff. It only knows the header files of them. So compilation of main.cpp file has nothing to do with compilation firstofthesecond or any kind of similar .cpp file in that project. It deals with only header files.

The truth process in my little project. 

We have 5 files:

main.cpp, firstofthesecond.cpp, secondofthesecond.cpp, firstofthethirrd.cpp, secondofthethird.cpp

Any of them does not wait to compile for end the compilation.

The answer was this. I don't know what the header files are but I seen the title so I am not going into that terms in this section.