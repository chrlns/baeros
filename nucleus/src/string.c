#include "div.h"
#include "string.h"

size_t strlen(const char* str) {
    size_t l = 0;
    while(*str != '\0') {
        str++;
        l++;
    }
    return l;
}

char* strncpy(char* dst, const char* src, size_t n) {
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dst[i] = src[i];
    }
    for (; i < n; i++) {
        dst[i] = '\0';
    }
    return dst;
}

char* itoa(int value, char* str, int base) {
    char* rc = str;
    char* ptr = str;
    char* low;
    
    // Check for supported base
    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }
    
    // Handle negative numbers for base 10
    if (value < 0 && base == 10) {
        *ptr++ = '-';
    }
    
    // Remember where the numbers start
    low = ptr;
    
    // The actual conversion
    do {
        int digit = idivmod(value, base);
        value = idiv(value, base);
        // Handle negative values
        if (digit < 0) {
            digit = -digit;
        }
        *ptr++ = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[digit];
    } while (value);
    
    // Terminate the string
    *ptr-- = '\0';
    
    // Invert the numbers
    while (low < ptr) {
        char tmp = *low;
        *low++ = *ptr;
        *ptr-- = tmp;
    }
    
    return rc;
}