#include <iostream>
#include <ostream>


int global_var = 1974;

static int static_var = 5;

void printLocalVars() {
    std::cout << "Static var is: " << static_var << std::endl;
    std::cout << "Local var is: " << global_var << std::endl;

}