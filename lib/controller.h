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
typedef struct threadQueue{
	p_circularList queue;
	pthread_mutex_t *mutex;
}threadQueue, *p_threadQueue;

typedef struct threadController{
	p_vvector threads;
	p_vvector threadQueues;
}threadController , *p_threadController;

typedef struct threadInfo{
	p_threadQueue queue;
	p_vvector reserved;
}threadInfo, *p_threadInfo;

// FUNCTIONS (THREAD CONTROLLER)
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(const threadController *tc,const pthread_t id);
void threadController_stopAll(const threadController *tc);

// FUNCTIONS (THREAD QUEUES)
p_threadQueue threadQueue_init();
void threadQueue_free(p_threadQueue tq);
void threadQueue_enqueue(const p_threadQueue tq, const void *data);
void *threadQueue_dequeue(const p_threadQueue tq);

// FUNCTIONS (THREAD INFO)
p_threadInfo threadInfo_init();
void threadInfo_free(p_threadInfo ti);
void threadInfo_enqueue(const p_threadInfo tq, const void *data);
void *threadInfo_dequeue(const p_threadInfo tq);



#endif
