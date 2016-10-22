#include <stdlib.h>
#include <stdio.h>
#ifdef __linux__
	#include <sys/errno.h>
#endif
#include "debug.h"

#ifdef __linux__
void debugMsg( const char *msg , short critical ){
	printf("Debug %s:%i -> [%s]\n" , __FILE__ , __LINE__ , msg );
	if( critical )
		exit(errno);
}
#endif

char *genData( char Char , size_t Size ){
	char *buffer = malloc(Size);
	if( !buffer )
		return NULL;
	for( size_t i = 0 ; i < Size ; i++ )
		buffer[i] = Char;
	buffer[Size-1] = 0;
	return buffer;
}

char *genData_addDelim( char Char , char Delim , size_t Size ){
	char *buffer = genData( Char , Size + 1 );
	if( !buffer )
		return NULL;

	buffer[Size-1] = Delim;
	buffer[Size] = 0;
	return buffer;
}
//TODO: Work on windows error messages.
