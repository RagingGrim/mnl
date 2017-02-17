/*
	Stores thread id's using vvectors.
*/

#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../lib/vVector.h"
// DEFINES


// STRUCTURES
typedef struct threadController{
p_vvector threads;
}threadController;

// FUNCTIONS
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(const threadController *tc,const pthread_t id);
void threadController_stopAll(const threadController *tc);
#endif
