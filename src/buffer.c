#include <stdlib.h>
#include <string.h>
#include "../lib/buffer.h"

//External functions
Buffer *buffer_init(size_t chunkSize , short mode){
      Buffer *newBuffer = malloc(sizeof(Buffer));
      if(!newBuffer)
            return NULL;

      newBuffer->data = malloc(sizeof(unsigned char) * chunkSize);
      if(!newBuffer->data)
            return NULL;

      for(size_t i = 0 ; i < chunkSize ; i++)
            newBuffer->data[i] = 0; //zero the newly allocated chunk
      newBuffer->size = chunkSize;
      newBuffer->at = 0; //look at the buffer_cat
      newBuffer->mode = mode;
      return newBuffer;
}

short buffer_grow(Buffer *buffer, size_t growBy){
      if(!buffer)
            return 1;
      if(!buffer->data)
            return 2;

      unsigned char *old = buffer->data;
      size_t oldSize = buffer->size;

      if(buffer->mode == BLOCK_DOUBLE)
            buffer->size *= 2; //double the size
      if(buffer->mode == BLOCK_DYNAMIC)
            buffer->size += growBy;

      buffer->data = realloc(buffer->data, sizeof(unsigned char) * buffer->size);
      if(!buffer->data){
            buffer->data = old;
            return -1; //Alloc failed but we could save the data
      }

      for(size_t i = oldSize + 1 ; i < buffer->size ; i++)
                  buffer->data[i] = 0;

      return 0;
}

short buffer_shrink(Buffer *buffer,size_t shrinkBy){
      unsigned char *old = buffer->data;
      size_t startAt = buffer->at - shrinkBy;
       size_t j = 0;
      for(size_t i = startAt ; j < shrinkBy ; i++ , j++)
            buffer->data[i] = 0;

      unsigned char *new = realloc(buffer->data , startAt);
      if(!new){
            buffer->data = old; //restore pointer;
            return 1;
      }

      buffer->at = startAt; //change the at variable to point to the new memory block ( or not past it)

      buffer->size = startAt; //change the chunkSize to the new size

      buffer->data = new; //Update the data pointer itself
      return 0;
}

short buffer_cat(Buffer *buffer, unsigned char *data , size_t dataSize){
      size_t sizeLeft = buffer->size - buffer->at;

      while(sizeLeft < dataSize){
            if(buffer_grow(buffer,dataSize-sizeLeft))
                  return 1;
            sizeLeft = buffer->size - buffer->at;
      }

      size_t j = 0;
      size_t i = 0;

      for(i = buffer->at ; j < dataSize ; i++ , j++)
            buffer->data[i] = data[j];


      buffer->at = i;
      return 0;
}

void buffer_destroy(Buffer *buffer , short clear){
      if(clear){
            for(size_t i = 0 ; i <  buffer->size ; i++)
                  buffer->data[i] = 0;
      }
      free(buffer->data);

      buffer->data = NULL;
      buffer->size = 0;
      buffer->at = 0;

      free(buffer);
      buffer = NULL;
}

unsigned char *buffer_getRaw(Buffer *buffer){
      return buffer->data;
}

short buffer_scrape(Buffer *buffer, char *startIdent , char *endIdent , char **res , size_t *size){
      size_t lenStart = strlen(startIdent);
      size_t lenEnd = strlen(endIdent);

      short err = 0;
      size_t startAt = _buffer_find(buffer, startIdent, lenStart, &err);
      if(err == 1)
            return 1;

      size_t startEnd = _buffer_find(buffer, endIdent, lenEnd, &err);
      if(err == 1)
            return 1;

      *size =startEnd - lenEnd + 1; //fixing off by one,

      *res = malloc(sizeof(unsigned char) * (*size) + 1); //null terminator
      if(!*res)
            return 2;
      char *lazy = *res;

      size_t i = 0;
      for(size_t j = startAt + 1 ; j < *size ;j++){
            lazy[i++] = buffer->data[j];
      }
      lazy[i++] = 0;

      return 0;
}
//Internal functions
size_t _buffer_find(Buffer *buffer , char *ident ,size_t identLen, short *err){
      size_t matches = 0;
      size_t i,j = 0;

      for(i = 0 ; i < buffer->at ; i++){
            if(buffer->data[i] == ident[j++])
                  matches++;
            else{
                  i=  i - j;
                  i++;
                  j = 0;
                  matches = 0;

            }
            if(matches == identLen)
                  break;
      }
      if(matches == identLen)
            return i;
      else
            *err = 1;
      return 0;
}
