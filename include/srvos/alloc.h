#ifndef ALLOC_H
#define ALLOC_H
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#define CHUNK_HEADER_MAGIC 0xAB
#define GET_HEADER(ptr) ((chunk_header_t*) ptr - sizeof(chunk_header_t))
#define GET_PTR(header) ((void*)(header) + sizeof(chunk_header_t))
typedef struct chunk_header chunk_header_t;
struct chunk_header {
	uint8_t magic;
	bool state;
	size_t size;
	chunk_header_t* prev;
	chunk_header_t* next;
};
void init_chunk_header(
	chunk_header_t* header,
	bool state,
	size_t size, 
	chunk_header_t* prev,
	chunk_header_t* next
);
void init_heap(void);
void* kmalloc(size_t size);
void* kcalloc(size_t n, size_t size);
void* krealloc(void* ptr, size_t size);
void kfree(void* ptr);
#endif

