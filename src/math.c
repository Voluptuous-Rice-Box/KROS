#include "math.h"
#include "error.h"

long abs(long n) {
    if (n < 0) {
        return -n;
    }
    return n;
}

long log(unsigned long n, unsigned int base) {
    if (base <= 1) {
        kernel_panic("log base 0 and log base 1 are not defined");
    }
    if (n == 0) {
        kernel_panic("log(0) is not defined");
    }

    long result = 0;
    while(n > 1) {
        n = n / base;
        result++;
    }
    return result;
}

long log2(unsigned long n) {
    return log(n, 2);
}

long log10(unsigned long n) {
    return log(n, 10);
}

long pow(long base, int exp) {
    if (exp < 0) {
        kernel_panic("pow called with negative exponent");
    }
    // Treat 0^0 as 1
    if (base == 0 && exp != 0) {
        return 0;
    }

    long result = 1;
    for (int i = 0; i < exp; i++) {
        result = result * base;
    }
    return result;
}
