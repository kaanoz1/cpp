#include <iostream>


int main() {
    std::cout << "Enter a integer: ";

    int num;

    std::cin >> num;

    const int result = num * 2;
    std::cout << "Here is the result: " << result << std::endl;


    return 0;
}