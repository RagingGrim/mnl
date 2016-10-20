#include "Vector.h"

strVector *strVector_init(size_t chunkSize){
      strVector *new_vector = malloc(sizeof(strVector));
      if(!new_vector)
            return NULL;

      new_vector->_basePointerSize = chunkSize;
      new_vector->data = malloc(sizeof(char *) * chunkSize);
      if(!new_vector->data){
            free(new_vector);
            return NULL;
      }

      size_t i;
      for( i = 0 ; i < new_vector->_basePointerSize ; i++){
            new_vector->data[i] = malloc(STD_STR_SIZE);
      }

      new_vector->size = 0;
      return new_vector;
};
void strVector_destroy(strVector *vector){
      size_t i;
      for(i = 0 ; i < vector->_basePointerSize ; i++){
            free(vector->data[i]);
            vector->data[i] = NULL;
      }
      free(vector->data);
      vector->data = NULL;

      free(vector);
      vector = NULL;

      return;
}
short strVector_grow(strVector *vector){
      char **backPnter = vector->data;
      vector->data = realloc(vector->data, sizeof(char *) * (vector->_basePointerSize * 2));
      if(!vector->data){
            vector->data = backPnter;
            return 1;
      }

      size_t i = vector->_basePointerSize;

      vector->_basePointerSize *= 2;

      for(i = i-1+1 ; i < vector->_basePointerSize ; i++){  //-1+1 disables a warning. => compiler should remove it fine.
            vector->data[i] = malloc(STD_STR_SIZE);
            if(!vector->data[i])
                  return 2;
      }
      return 0;
}
short strVector_pushBack(strVector *vector , char *buffer , size_t bufferSize){
      if(vector->size == vector->_basePointerSize){
            short ret = strVector_grow(vector);
            if( ret != 0 )
                  return ret;
      }

      char *location = vector->data[vector->size];
      if(bufferSize > STD_STR_SIZE){
            char *backPnter = location;
            location = realloc(location, bufferSize + 1); //for null terminator
            if(!location){
                  location = backPnter;
                  return 6;
            }
            else
                  vector->data[vector->size] = location;

      }

      memcpy(location , buffer , bufferSize+1);
      vector->size++;
      return 0;
}
short strVector_popBack(strVector *vector){
      if(vector->size > 0){
            free(vector->data[vector->size]);
            vector->data[vector->size] = NULL;
            vector->size--;
      }

      return 0;
}

char *strVector_get(strVector *vector ,size_t i){
      if(i > vector->size)
            return NULL;
      else
            return vector->data[i];
}

size_t strVector_search_adv(strVector *vector , size_t startAt , char *value , int *err){
      *err = 1;
      for(size_t i = startAt ; i < vector->size ; i++)
            if(strcmp(vector->data[i], value) == 0){
                  *err = 0;
                  return i;
            }

      return 0;
}

size_t strVector_search(strVector *vector , char *value , int *err){
      return strVector_search_adv(vector, 0, value,err);
}
