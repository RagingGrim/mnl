#include "../lib/vVector.h"

p_vvector vvector_init_adv(const size_t chunkSize){
	p_vvector newVect = malloc(sizeof(struct vvector));
	if(!newVect) // Base structure allocation.
		return NULL;

	newVect->chunkSize = chunkSize;
	newVect->elements = 0;
	newVect->data = malloc(sizeof(void *) * chunkSize);
	if(!newVect->data){
		free(newVect);
		return NULL;
	}

	return newVect;
}

p_vvector vvector_init(){
	return vvector_init_adv(VVECTOR_CHUNK_SIZE); // This is short ; it can be inlined.
}

void vvector_free(p_vvector vector){
	vector->chunkSize = 0;
	free(vector->data);
	vector->data = NULL;
	vector->elements = 0;
	free(vector);
	vector = NULL;
}

short _vvector_grow(const p_vvector vector){
	size_t oldSize = vector->chunkSize;
	vector->chunkSize *= 2; // Double size

	void *old_pnter = vector->data;
	vector->data = realloc(vector->data, sizeof(void *) * vector->chunkSize);
	if(!vector->data){
		vector->data = old_pnter;
		vector->chunkSize = oldSize;
		return VVECTORE_GROW;
	}

	return VVECTORE_OK;
}

short vvector_push(const p_vvector vector, const void *element){
	if(vector->elements == vector->chunkSize)
		if ( _vvector_grow(vector) != VVECTORE_OK )
			return VVECTORE_GROW;

	vector->data[vector->elements++] = (void *)element;
	return VVECTORE_OK;
}

void *vvector_pop(const p_vvector vector){
	if( vector->elements == 0 )
		return NULL;

	void *pnter = vector->data[vector->elements - 1];
	vector->data[vector->elements - 1] = NULL;
	vector->elements--;
	return pnter;
}

void *vvector_at(const p_vvector vector, const size_t i){
	if( vector->elements < i )
		return NULL;
	return vector->data[i];
}

void *vvector_pop_bottom(const p_vvector vector){
	void *pnter = vvector_at(vector, 0);
	if(!pnter)
		return NULL;

	for(size_t i = 0 ; i < vector->elements ; i++)
		vector->data[i] = vector->data[i+1];
	vector->elements--;

	return pnter;
}
