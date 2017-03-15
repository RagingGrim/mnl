#ifndef MAP_H
#define MAP_H
// Includes
#include <stdlib.h>
#include <stdio.h> // TODO: Remove
#include <string.h>
#include "vVector.h" //<<MARK IGNORE>>
// Typedefs
typedef struct map{
	p_vvector key;
	p_vvector value;
	size_t size;
}basic_map, *p_map;

// Functions

basic_map *mapCreate();
basic_map *mapCreate_fromParams(const int argc ,const char **argv);
void mapDestroy(basic_map *map);
const short mapAdd(basic_map *map, const char *key, const char *value);
const char *mapKeyLookup(const basic_map *map,const char *key);
const char *mapValueLookup(const basic_map *map,const char *value);
const short _mapKeyExist(const basic_map *map,const char *key);
const short _mapValueExist(const basic_map *map,const char *value);
#endif
