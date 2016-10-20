#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "controller.h"
#include "../logging/logger.h"

void *l(void *d){
	logger* log = d;
	size_t i = 0;
	while(++i != 15){
		logIt(log, "IN A THREAD\n");
	}
	return NULL;
}

int main(){
	logger *log = logger_init(NULL);
	threadController *tc = threadController_init();
	logIt(log , "Startup!\n");
	size_t i = 0;
	while(++i != 5){
		pthread_t id;
		pthread_create(&id, NULL, l, log);
		threadController_pushback(tc, id);

	}
	puts("FIN");
	threadController_stopAll(tc);
	logger_destroy(log);
	threadController_destroy(tc);
	return 0;
}
