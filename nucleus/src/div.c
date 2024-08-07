
int idiv(int dividend, int divisor) {
#if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_5__)
    if (divisor == 0) {
        // Handle division by zero error
        return 0; // Or some error value
    }

    int q = 0;
    int sign = 1;
    unsigned int udividend = dividend;
    unsigned int udivisor = divisor;
    
    // Handle negative numbers
    if (dividend < 0) {
        udividend = -dividend;
        sign = -sign;
    }
    if (divisor < 0) {
        udivisor = -divisor;
        sign = -sign;
    }

    // Fast track for powers of 2
    if ((udivisor & (udivisor - 1)) == 0) {
        q = udividend >> __builtin_ctz(udivisor); // Count trailing zeros
    } else {
        while (udividend >= udivisor) {
            udividend -= udivisor;
            q++;
        }
    }
    
    return sign * q;
#else 
    return dividend / divisor;
#endif
}

int idivmod(int dividend, int divisor) {
#if defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_5__)
    if (divisor == 0) {
        // Handle division by zero error
        return 0; // Or some error value
    }

    int sign = 1;
    unsigned int udividend = dividend;
    unsigned int udivisor = divisor;
    
    // Handle negative numbers
    if (dividend < 0) {
        udividend = -dividend;
        sign = -1;
    }
    if (divisor < 0) {
        udivisor = -divisor;
    }
    
    // Fast track for powers of 2
    if ((udivisor & (udivisor - 1)) == 0) {
        udividend &= (udivisor - 1);
    } else {
        while (udividend >= udivisor) {
            udividend -= udivisor;
        }
    }
    
    return sign * udividend;
#else 
    return dividend % divisor;
#endif
}
