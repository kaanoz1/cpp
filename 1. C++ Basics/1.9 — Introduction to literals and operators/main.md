```cpp
std::cout << "Hello world!";
int x { 5 };
```

A literal (also known as a literal constant) is a fixed value that has been inserted directly into the source code.

Unlike a variable (whose value can be set and changed through initialization and assignment respectively), the value of a literal is fixed and cannot be changed.

Literal’s value is placed directly in the executable, and the executable itself can’t be changed after it is created. A variable’s value is placed in memory, and the value of memory can be changed while the executable is running. But executable file cannot be changed.

## Operators and Operands:

For example, as children we all learn that 2 + 3 equals 5. In this case, the literals 2 and 3 are the operands, and the symbol + is the operator that tells us to apply mathematical addition on the operands to produce the new value 5.

This output value is then printed to the console. In C++, the output value of an operation is often called a **return value**.

You are likely already quite familiar with standard arithmetic operators from common usage in mathematics, including addition (+), subtraction (-), multiplication (*), and division (/). In C++, assignment (=) is an operator as well, as are insertion (<<), extraction (>>), and equality (==). While most operators have symbols for names (e.g. +, or ==), there are also a number of operators that are keywords (e.g. new, delete, and throw).

## Return values and side effects

Most operators in C++ just use their operands to calculate a return value. For example, -5 produces return value -5 and 2 + 3 produces return value 5. There are a few operators that do not produce return values (such as delete and throw). We’ll cover what these do later.

Some operators has side effects which is doing something that doing something else then just returning value. For instance in the statement of 5 + 3 just returns something which is 8. But std::cout << returns same object in order to chaining. But also prints the value to the console so it does something then returning a value. So it has **side effect**.

