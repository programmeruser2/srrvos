// TODO: split into uart files
// TODO: actually initialize UART
#include <srvos/console.h>
#include <srvos/string.h>
#include <stdarg.h>
#define UART_BASE 0x10000000  
static volatile char* uart = (volatile char*) UART_BASE;
void putchar(char c) {
	*uart = c;
}
void puts(char* s) {
	while (*s) {
		putchar(*s);
		++s;
	}
}
void putline(char* s) {
	puts(s);
	puts("\r\n");
}
char getchar(void) {
	while ((*(uart + 5) & 1) == 0);
	return *uart;
}
void printf(char* s, ...) {
	va_list ap;
	va_start(ap, s);
	char tmp[20];
	while (*s) {
		switch (*s) {
			case '\n':
				putline("");
				break;
			case '%':
				++s;
				switch (*s) {
					case 'd':
					case 'i':
					case 'u':
						itoa(va_arg(ap, unsigned long long), tmp, 10);
						puts(tmp);
						break;
					case 'x':
					case 'X':
						itoa(va_arg(ap, unsigned long long), tmp, 16);
						puts(tmp);
						break;
					case 's':
						puts(va_arg(ap, char*));
						break;
					case 'c':
						putchar((char)va_arg(ap, int));
						break;
					case 'p':
						itoa((unsigned long long) va_arg(ap, void*), tmp, 16);
						puts("0x");
						puts(tmp);
						break;
					// no %n
					default:
						putchar('%');
						putchar(*s);
				}
				break;
			default:
				putchar(*s);
		}
		++s;
	}
}
