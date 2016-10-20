#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef VECTOR_H
#define VECTOR_H
//defines
#define STD_STR_SIZE 256

//structures
typedef struct strVector{
size_t _basePointerSize;
size_t size;
char **data;
}strVector , STR_VECTOR;

//functions
strVector *strVector_init(size_t chunkSize);
void strVector_destroy(strVector *vector);
short strVector_grow(strVector *vector);
short strVector_pushBack(strVector *vector , char *buffer , size_t bufferSize);
short strVector_popBack(strVector *vector);
char *strVector_get(strVector *vector , size_t i);
size_t strVector_search_adv(strVector *vector , size_t startAt , char *value , int *err);
size_t strVector_search(strVector *vector , char *value , int *err);

#endif
