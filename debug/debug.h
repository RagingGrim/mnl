#ifndef C_DEBUG_H
#define C_DEBUG_H
#include <stddef.h>
void debugMsg( const char *msg , short critical );
const char *_genDbgMsg( const char *msg );

char *genData( char Char , size_t Size );
char *genData_addDelim( char Char , char Delim , size_t Size );
#endif
