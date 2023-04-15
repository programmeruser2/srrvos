#include <srvos/alloc.h> 
#include <srvos/string.h>
#include <stdbool.h>

// debug stuff
#include <srvos/console.h>
#include <srvos/string.h>

extern unsigned char __heap_start;
extern unsigned char __heap_size;
chunk_header_t* min_addr_chunk;
void init_chunk_header(
	chunk_header_t* header,
	bool state,
	size_t size,
	chunk_header_t* prev,
	chunk_header_t* next
) {
	header->magic = CHUNK_HEADER_MAGIC;
	header->state = state;
	header->size = size;
	header->prev = prev;
	header->next = next;
}
void init_heap(void) {
	min_addr_chunk = (chunk_header_t*) &__heap_start;
	init_chunk_header(
		min_addr_chunk,
		false,
		(size_t)&__heap_size - sizeof(chunk_header_t),
		NULL,
		NULL
	);

}

void* kmalloc(size_t size) {
	if (size == 0) {
		return NULL;
	}
	// align memory on an 8 byte boundary
	if (size & 0x7) {
		size += 8 - (size & 0x7);
	}
	chunk_header_t* current = min_addr_chunk;
	while (current) {
		if (!current->state) {
			if (current->size == size) {
				current->state = true;
				return current + sizeof(chunk_header_t);
			} else if (current->size > size) {
				// "fragment"/split up the chunk
				size_t remaining = current->size - size;
				current->size = size;
				if (remaining > sizeof(chunk_header_t)) {
					chunk_header_t* new_header = current+size;
					init_chunk_header(
						new_header,
						false,
						remaining,
						current,
						current->next
					);
				}
				return GET_PTR(current);
			}
		}
		current = current->next;
	}
	// something went wrong, return NULL
	return NULL;
}
void* kcalloc(size_t n, size_t size) {
	void* res = kmalloc(n*size);
	memset(res, 0, n*size);
	return res;
}
void* krealloc(void* ptr, size_t size) {
	if (ptr == NULL) {
		return kmalloc(size);
	}
	chunk_header_t* header = GET_HEADER(ptr);
	// case 1: size < existing
	if (size < header->size) {
		// shrink chunk
		size_t remaining = header->size - size;
		header->size = size;
		// then create a new chunk from the free space
		// TODO: what if we waste too much memory from shrinking?
		// there's no point in a 0 length chunk
		// so it's > not <=
		if (remaining > sizeof(chunk_header_t)) {
			chunk_header_t* new_header = ptr+size;
			init_chunk_header(
				new_header,
				false,
				remaining,
				ptr,
				header->next 
			);
		}
	} else if (size == header->size) {
		// case 2: same size
		// in this case, return the same pointer without doing anything
		return ptr;
	} else {
		// then size > header->size
		// we must reallocate
		// first free so we get more space (this isnt actually a uaf vuln im pretty sure? TODO: audit this more in-depth)
		//kfree(ptr);
		// nvm this isn't the safest way (TODO: maybe use memmove instead of memcpy and reimplement?)
		// then malloc
		void* newptr = kmalloc(size);
		if (newptr == NULL) return NULL;
		memcpy(newptr, ptr, header->size);
		return newptr;
	}
	// something went wrong, return NULL?
	return NULL;
}
void kfree(void* ptr) {
	if (ptr == NULL) {
		return;
	}
	
	chunk_header_t* header = GET_HEADER(ptr);
	if (header < min_addr_chunk) {
		min_addr_chunk = header;
	}
	header->state = false;
	// merge with other free chunks if we can
	// case 1: merge with left and right
	if (header->prev && header->next && !header->prev->state && !header->next->state) {
		header->prev->size += header->size + header->next->size;
		if (header->next->next) {
			header->prev->next = header->next->next;
			// fix other references
			//header->prev->prev->next = header->prev;
			header->next->next->prev = header->prev;
		}
	} else if (header->prev && !header->prev->state) {
		header->prev->size += header->size;
		header->prev->next = header->next;
		//fix refs
		header->next->prev = header->prev;
	} else if (header->next && !header->next->state) {
		// move next header to current
		header->size += header->next->size;
		header->next = header->next->next;
		if (header->next->next) header->next->next->prev = header;
	}
	// done
}
