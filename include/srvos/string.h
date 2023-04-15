#ifndef STRING_H
#define STRING_H

#include <stddef.h>
size_t strlen(char* str);
void strcat(char* str1, char* str2);
void itoa(int number, char* str, int base);

unsigned char* memset(unsigned char* ptr, unsigned char c, size_t n);
unsigned char* memcpy(unsigned char* dest, const unsigned char* src, size_t n);

#endif
