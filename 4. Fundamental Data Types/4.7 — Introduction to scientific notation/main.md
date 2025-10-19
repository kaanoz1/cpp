## Scientific Notation

```cpp
long long x = 5.94e24;
```
## How to convert decimal numbers to scientific notation


Use the following procedure:

    - Your exponent starts at zero.
    - If the number has no explicit decimal point (e.g. 123), it is implicitly on the right end (e.g. 123.)
    - Slide the decimal point left or right so there is only one non-zero digit to the left of the decimal.
        - Each place you slide the decimal point to the left increases the exponent by 1.
        - Each place you slide the decimal point to the right decreases the exponent by 1.
    - Trim off any leading zeros (on the left end of the significand)
    - Trim off any trailing zeros (on the right end of the significand) only if the original number had no decimal point. We’re assuming they’re not significant. If you have additional information to suggest they are significant, you can keep them.