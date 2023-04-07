// TODO: split into uart files
void putchar(char c) {
	*(volatile char*) 0x10000000 = c;
}
void puts(char* s) {
	while (*s) {
		putchar(*s);
		++s;
	}
}
void kmain(void) {
	puts("Hello kernel world!");
}
