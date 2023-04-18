#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdarg.h>
void putchar(char c);
void puts(char* s);
void putline(char* s);
char getchar(void);
void vprintf(char* fmt, va_list ap);
void printf(char* s, ...);
#endif
