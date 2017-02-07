#ifndef VVECTOR_H_GUARD
#define VVECTOR_H_GUARD
// Includes
#include <stdlib.h>

// Constants
#define VVECTOR_CHUNK_SIZE 250

// Error Constants
#define VVECTORE_OK 0
#define VVECTORE_GROW 1


// Structures
typedef struct vvector{
	void **data;
	size_t chunkSize; // Chunk size will be doubled every time it's reached.
	size_t elements;
	} *p_vvector , vvector;

// Functions
p_vvector vvector_init();
p_vvector vvector_init_adv(const size_t chunkSize);
void vvector_free(p_vvector vector);

short _vvector_grow(const p_vvector vector); // _because it's an internal function.
short vvector_push(const p_vvector vector, const void *element);
void *vvector_pop(const p_vvector vector);
void *vvector_at(const p_vvector vector, const size_t i);


#endif
