#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include <pthread.h>
#include "../buffers/vVector.h"
// DEFINES


// STRUCTURES
typedef struct threadController{
vVector *threads;
}threadController;

// FUNCTIONS
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(threadController *tc,pthread_t id);
void stopAll(threadController *tc);
void threadController_stopAll(threadController *tc);
#endif
