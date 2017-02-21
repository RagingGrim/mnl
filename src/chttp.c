#include "../lib/chttp.h"

void *chttp_init(){
	p_custom_http chttp = malloc(sizeof(custom_http));
	if( !chttp )
		return NULL;

	chttp->buffer = NULL;
	chttp->size = 0;
	return chttp;
}

void chttp_destroy(p_custom_http chttp){
	memset(chttp->buffer, 0, chttp->size);
	free(chttp->buffer);
	chttp->buffer = NULL;
	chttp->size = 0;

	free(chttp);
	chttp = NULL;
}

const short chttp_add(p_custom_http chttp, const char *data, const size_t size){
	size_t oldSize = chttp->size;
	short err = chttp_grow(chttp, size + 2);
	if( err != CHTTPE_OK )
		return CHTTPE_GROW;

	memcpy(chttp->buffer + oldSize, data, size);
	memcpy(chttp->buffer + oldSize + size, "\r\n", 2);

	return CHTTPE_OK;
}


const short chttp_grow(p_custom_http chttp, const size_t size){
	char *old = chttp->buffer;
	chttp->buffer = realloc(chttp->buffer, (chttp->size + size) * sizeof(char));

	if( !chttp->buffer ){
		chttp->buffer = old;
		return CHTTPE_GROW;
	}

	chttp->size += size;
	return CHTTPE_OK;
}

char *chttp_lookup(const p_custom_http chttp, const char *key){
	char *location = strstr(chttp->buffer, key);
	if( !location )
		return NULL;

	location += strlen(key);
	char *end = strstr(location, "\r\n");
	if( !end )
		return NULL;

	size_t size = (end - location + 1) * sizeof(char);

	char *newBuffer = malloc( size );

	if( !newBuffer )
		return NULL;

	memcpy(newBuffer, location, size - 1);


	newBuffer[size - 1] = '\0';

	return newBuffer;
}

const short chttp_finalise(const p_custom_http chttp , const char *data, const size_t size){
	unsigned int nDigits = ceil(log10(size));


	char *buffer = malloc(17 + nDigits);
	if(!buffer)
		return CHTTPE_GROW;

	size_t tempSize = snprintf(buffer, 17 + nDigits, "Content-Length: %zu", size);
	if(chttp_add(chttp, buffer, tempSize) != CHTTPE_OK){
		free(buffer);
		return CHTTPE_GROW;
	} // Add the end of header identifier.

	free(buffer);
	buffer = NULL;

	if(chttp_add(chttp, "\r\n", 2) != CHTTPE_OK) // Add the end of header identifier.
		return CHTTPE_GROW;

	if(chttp_add(chttp, data, size) != CHTTPE_OK)
		return CHTTPE_GROW;

	return CHTTPE_OK;
}
