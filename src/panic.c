#include <srvos/panic.h>
#include <srvos/console.h>

void panic(char* msg) {
	putline(msg);
	while (1);
}
