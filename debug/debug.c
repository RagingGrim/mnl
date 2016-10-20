#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include "debug.h"

void debugMsg( const char *msg , short critical ){
	printf("Debug %s:%i -> [%s]\n" , __FILE__ , __LINE__ , msg );
	if( critical )
		exit(errno);
}
