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

char _map[] = {"abcd"};
char *genData_complicatedStr(size_t Size){
	char *buffer = malloc(Size);

	if( !buffer )
		return NULL;
	size_t j = 0;
	for( size_t i = 0 ; i < Size ; i++ , j++ ){
		buffer[i] = _map[j];
		if(j==3)
			j=0;
	}

	buffer[Size-1] = 0;
	return buffer;
}

short genData_evalComplicatedStr(char *Data , size_t Size ){
	size_t j = 0;
	size_t correct = 0;
	for( size_t i = 0 ; i < Size ; i++ , j++ ){
		if(Data[i] == _map[j])
			correct++;
		else{
			if(correct == Size - 1)
				return 1;
			printf("Evaluation of complicated string failed at : %i:%c -> %i:%c\n" , _map[j],_map[j] ,Data[i],Data[i]);
			getchar();
			return 0;
		}
		if(j==3)
			j=0;
	}
	return 1;
}
//TODO: Work on windows error messages.
