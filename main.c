#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include "logging/logger.h"
#include "networking/networking.h"

int main(){
	logger *log = logger_init("mnl.log");
	logIt(log, "Hello world!\n");
	printf("%zu\n",sizeof(log));
	logger_destroy(log);


	return 0;
}
