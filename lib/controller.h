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
#define THREAD_SIGNAL_READY 0

// STRUCTURES
typedef struct signalStruct{
	unsigned short thread_signal;
	unsigned short master_signal;
	pthread_mutex_t *_mutex_thread_signal;
	pthread_mutex_t *_mutex_master_signal;
}signalStruct, *p_signalStruct;

typedef struct threadController{
	p_vvector threads;
}threadController , *p_threadController;

// FUNCTIONS (THREAD CONTROLLER)
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_pushback(const threadController *tc,const pthread_t id);
void threadController_stopAll(const threadController *tc);

// FUNCTIONS (SIGNALS)
p_signalStruct signal_init();
void signal_destroy(p_signalStruct signalStruct);
void signal_set_thread(const p_signalStruct signalStruct,const unsigned short value);
void signal_set_master(const p_signalStruct signalStruct,const unsigned short value);
const unsigned short signal_get_thread(const p_signalStruct signalStruct);
const unsigned short signal_get_master(const p_signalStruct signalStruct);


#endif
