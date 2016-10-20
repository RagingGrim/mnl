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
//TODO: Work on windows error messages.
