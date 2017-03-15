#include "../lib/map.h"

basic_map *mapCreate(){
	basic_map *map = malloc(sizeof(basic_map));
	map->size = 0;
	if(!map)
		return NULL;

	map->key = vvector_init();
	if(!map->key)
		return NULL;
	map->value = vvector_init();
	if(!map->value){
		free(map->key);
		free(map);
		return NULL;
	}

	return map;
}

void mapDestroy(basic_map *map){
	vvector_free(map->key);
	vvector_free(map->value);
	free(map);
}

const short mapAdd(basic_map *map,const char *key, const char *value){
	if(vvector_push(map->key,key))
		return 0;
	if(vvector_push(map->value,value))
		return 0;

	map->size++;
	return 1;
}

const char *mapKeyLookup(const basic_map *map,const char *key){
	for( size_t i = 0 ; i < map->size; i++ )
		if(!strcmp(vvector_at(map->key, i),key))
			return vvector_at(map->value, i);
	return NULL;
}

const char *mapValueLookup(const basic_map *map,const char *value){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vvector_at(map->value, i),value))
			return vvector_at(map->key, i);
	return NULL;
}

basic_map *mapCreate_fromParams(const int argc ,const char **argv){ // TODO: This should be written differently.
	if(argc <= 1)
		return NULL;

	basic_map *map = mapCreate();
	if(!map)
		return NULL;

	// We want to loop through the command line parameters mapping options.
	// Any option which does not directly map to state is mapped to (NULL)

	for(size_t i = 1 ; i < argc ; i+=2){
		if(argv[i][0] == '-'){
			if(i + 1 < argc){
				if(argv[i+1][0] != '-'){
					mapAdd(map, argv[i], argv[i+1]);
				}
				else{
					mapAdd(map, argv[i], "(null)");
					i--;
				}
			}
		}
	}
	return map;
}


const short _mapKeyExist(const basic_map *map,const char *key){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vvector_at(map->key, i),key))
			return 1;
	return 0;
}

const short _mapValueExist(const basic_map *map,const char *value){
	for( size_t i = 0 ; i < map->size ; i++ )
		if(!strcmp(vvector_at(map->value, i),value))
			return 1;
	return 0;
}
