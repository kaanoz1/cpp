## Inline functions:

Think about a function do actually little work but for enhancing readibilty you define it in a function. Like max of a two numbers.
As you might guess in actual it would be greate just copying and pasting that function in the aspect of performance. So this is why we should use keyword ```inline```. Check this function out:

```cpp
inline int max(int a, int b){
    return a > b ? a : b;
}
```
So if we would not have used ```inline``` keyword in this function compiler would had have to follow these steps:

1. First off, the CPU must store the address of the current instruction it is executing 
2. Then parameters x and y must be instantiated and then initialized. 
3. Then the execution path has to jump to the code in the max() function. 
4. When the function ends, the program has to jump back to the location of the function call.
5. And the return value has to be copied so it can be output.

All this journey is called as **overhead**.

So using ```inline``` keyword we are getting rid of this type of calls. But then why dont we use ```inline``` every function that we encounter? Because for functions that are large and/or perform complex tasks, the overhead of the function call is typically insignificant compared to the amount of time the function takes to run. 

So what does actually ```inline``` keyword do?

Inline expansion is a process where a function call is replaced by the code from the called function’s definition.

But we cannot use ```inline``` keyword everywhere.

However, inline expansion has its own potential cost: if the body of the function being expanded takes more instructions than the function call being replaced, then each inline expansion will cause the executable to grow larger. Larger executables tend to be slower (due to not fitting as well in memory caches).

But however in most and modern compilers it generally does not care about whether you mark the functions as inline or not. It will decide by itself.

## But know Inline is not used for requesting compiler that this functions might be used in inline.

But know, in modern cpp environment we use in order for telling the compiler that `I might declare this function multiple times.` do not see it as an error.

So by that we can declare mini functions in header files and since compiler will assume that they are same. (Even though it encounter multiple definitions of a function)


