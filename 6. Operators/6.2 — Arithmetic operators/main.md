## Integer Divison or Float Point Division?

If either (or both) of the operands are floating point values, the division operator performs floating point division. Floating point division returns a floating point value, and the fraction is kept. For example, 7.0 / 4 = 1.75, 7 / 4.0 = 1.75, and 7.0 / 4.0 = 1.75. As with all floating point arithmetic operations, rounding errors may occur.

If both of the operands are integers, the division operator performs integer division instead. Integer division drops any fractions and returns an integer value. For example, 7 / 4 = 1 because the fractional portion of the result is dropped. Similarly, -7 / 4 = -1 because the fraction is dropped.

## Modifying and non-modifying operators

An operator that can modify the value of one of its operands is informally called a modifying operator. In C++, most operators are non-modifying -- they just use the operands to calculate and return a value. However, two categories of built-in operators do modify their left operand (as well as return a value):