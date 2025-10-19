## Linker and naming conflictions in different namespaces.


As we know if we had 2 files like this:

main.cpp: 
```cpp

void Log(const char*);

int main(){
    Log("Say hi to my friends");
    return 0;
}
```

And log.cpp:
```cpp
#include <iostream>

void Log(const char* message){
    std::cout << message << std::endl;
}
```
I will compile and build via linker without any error.

But what if we have a different **declaration** in main.cpp? Then it will compile absoloutely without any error but when linker comes into play it abort with an error. We dont even call Log function btw.


How we can avoid this naming conflictions?

TODO: Fill this.
