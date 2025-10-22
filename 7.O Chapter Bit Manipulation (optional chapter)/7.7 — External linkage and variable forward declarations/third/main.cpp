#include <iostream>
#include "test.h"


extern int global_var;

extern int static_var; // This should provide error.

int main() {

    printLocalVars();
    global_var++;
    printLocalVars();

    return 0;
}