/*
	Stores thread id's using vvectors.
*/

#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "../lib/vVector.h" //<<MARK IGNORE>>
#include "../lib/circularList.h" //<<MARK IGNORE>>

// DEFINES
#define THREAD_SIGNAL_READY 0

// STRUCTURES
typedef struct threadController{
	p_vvector threads;
	p_vvector threadQueues;
}threadController , *p_threadController;

typedef struct threadInfo{
	threadQueue queue;
	p_vvector reserved;
}threadInfo, *p_threadInfo;

// FUNCTIONS (THREAD CONTROLLER)
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(const threadController *tc,const pthread_t id);
void threadController_stopAll(const threadController *tc);


#endif
