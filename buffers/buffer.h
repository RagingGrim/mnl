#ifndef BUFFER_H
#define BUFFER_H
#include <stddef.h>
//structures
typedef struct Buffer{
unsigned char *data;
short mode;
size_t size;
size_t at;
}BUFFER,Buffer;
#define BLOCK_DOUBLE 1
#define BLOCK_DYNAMIC 2

//External Functions
Buffer *buffer_init(size_t chunkSize , short mode);
short buffer_grow(Buffer *buffer,size_t growBy);
short buffer_cat(Buffer *buffer, unsigned char *data , size_t dataSize);
void buffer_destroy(Buffer *buffer , short clear);
unsigned char *buffer_getRaw(Buffer *buffer);
short buffer_shrink(Buffer *buffer,size_t shrinkBy);
short buffer_scrape(Buffer *buffer, char *startIdent , char *endIdent , char **res , size_t *size);
//This function is built with the idea of parsing C-Strings , or any other string for that matter, It can parse binary data though.


//Internal Functions
size_t _buffer_find(Buffer *buffer , char *ident ,size_t identLen, short *err);
//This function is built with the idea of parsing C-Strings , or any other string for that matter, It can parse binary data though.

#endif
