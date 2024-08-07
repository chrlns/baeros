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