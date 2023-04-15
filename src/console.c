// TODO: split into uart files
// TODO: actually initialize UART
#include <srvos/console.h>
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

