#include <srvos/string.h>
#include <stddef.h>
#include <stdbool.h>

size_t strlen(char* str) {
	size_t len = 0;
	while (*str) ++len;
	return len;
}

void strcat(char* str1, char* str2) {
	size_t offset = strlen(str1);
	while (*str2) {
		*(str1 + offset) = *str2;
		++offset;
		++str2;
	}
}

void itoa(unsigned long long number, char* str, unsigned int base) {
	if (number == 0) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	//bool sign = number < 0;
	//if (sign) number = -number;
	size_t len = 0;
	while (number != 0) {
		unsigned long long d = number % base;
		number = (number - d) / base;
		if (d <= 9) {
			str[len] = (char)d + '0';
		} else {
			str[len] = (char)d - 10 + 'a';
		}
		++len;
	}
	/*if (sign) {
		str[len] = '-';
		++len;
	}*/
	// reverse string
	size_t bound;
	if (len % 2 == 0) bound = len/2;
	else bound = (len+1)/2;
	for (size_t i = 0; i < bound; ++i) {
		char tmp = str[i];
		str[i] = str[len-1-i];
		str[len-1-i] = tmp;
	}
	// null terminator
	str[len] = '\0';
}

unsigned char* memset(unsigned char* ptr, unsigned char c, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		*(ptr+i) = c;
	}
	return ptr;
}

unsigned char* memcpy(unsigned char* dest, const unsigned char* src, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		*(dest+i) = *(src+i);
	}
	return dest;
}
