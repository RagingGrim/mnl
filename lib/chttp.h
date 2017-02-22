#ifndef CHTTP_HEADER_GUARD
#define CHTTP_HEADER_GUARD
// Includes
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <bsd/string.h>
#include <stdio.h>
// Defines
#define CHTTPE_OK 0
#define CHTTPE_GROW 1
#define CHTTPE_LOOKUP 2
// Structures
typedef struct chttp{
	char *buffer;
	size_t size;
	}custom_http, *p_custom_http;
// Functions
void *chttp_init();
void chttp_destroy(p_custom_http chttp);
const short chttp_add_header(p_custom_http chttp, const char *data, const size_t size);
const short chttp_add(p_custom_http chttp, const char *data, const size_t size);
const short chttp_grow(const p_custom_http chttp, const size_t size);
char *chttp_lookup(const p_custom_http chttp, const char *key);
const short chttp_finalise(const p_custom_http chttp , const char *data, const size_t size);
char *chttp_getData(const p_custom_http chttp);
const char *_chttp_find(const char *buffer, const size_t bufferSize, const char *find, const size_t findSize);
#endif
