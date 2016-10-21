#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "timer.h"
#include "../logging/logger.h"

void *say(void *data){
	puts(data);
	return NULL;
}

int main(){
	timer Timer;
	Timer._func = say;
	Timer._seconds = 50;
	return 0;
}
