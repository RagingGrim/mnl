#include "../lib/controller.h"
/*
	I'll have to refactor all of this code.
	I changed the library functions and how they work so now things are a tad more complex.
*/


// Thread Queue
p_threadQueue threadQueue_init(){
	p_threadQueue tq = malloc(sizeof(threadQueue));
	if(!tq)
		return NULL;

	tq->mutex = NULL;
	tq->mutex = malloc(sizeof(pthread_mutex_t));

	if(!tq->mutex){
		free(tq);
		tq = NULL;
		return NULL;
	}

	if(pthread_mutex_init(tq->mutex, NULL) != 0){
		free(tq);
		tq = NULL;
		return NULL;
	}

	tq->queue = vvector_init();
	if(!tq->queue){
		pthread_mutex_destroy(tq->mutex);
		free(tq->mutex);
		free(tq);
		tq = NULL;
		return NULL;
	}
	return tq;
}

void threadQueue_free(p_threadQueue tq){
	pthread_mutex_destroy(tq->mutex);
	free(tq->mutex);
	tq->mutex = NULL;
	vvector_free(tq->queue);
	tq->queue = NULL;
	free(tq);
	tq = NULL;
}

short threadQueue_enqueue(const p_threadQueue tq, const void *data){
	pthread_mutex_lock(tq->mutex);
	short val = circularList_enqueue(tq->queue, data);
	pthread_mutex_unlock(tq->mutex);
	return val;
}

void *threadQueue_dequeue(const p_threadQueue tq){
	pthread_mutex_lock(tq->mutex);
	if(tq->queue->elements == 0)
		return NULL;
	void *data = circularList_dequeue(tq->queue);
	pthread_mutex_unlock(tq->mutex);
	return data;
}

// Thread Controller
threadController *threadController_init(){

}

void threadController_destroy(threadController *tc){

}

short threadController_pushback(const threadController *tc,void *(* routine)(void *), void *data){

}

short threadController_messsage(const threadController *tc, const size_t at, void *msg){
	
}

void threadController_stopAll(const threadController *tc){

}



// Thread Info
p_threadInfo threadInfo_init_no_queue(){
	p_threadInfo ti = malloc(sizeof(threadInfo));
	if(!ti)
		return NULL;

	ti->queue = NULL;
	ti->reserved = NULL;
	return ti;
}

void threadInfo_free_no_queue(p_threadInfo ti){
	ti->reserved = NULL;
	free(ti);
	ti = NULL;
}


p_threadInfo threadInfo_init(){
	p_threadInfo ti = malloc(sizeof(threadInfo));
	if(!ti)
		return NULL;

	ti->queue = threadQueue_init();
	if(!ti->queue){
		free(ti);
		ti = NULL;
		return NULL;
	}

	ti->reserved = NULL;
	return ti;
}

void threadInfo_free(p_threadInfo ti){
	threadQueue_free(ti->queue);
	free(ti);
	ti = NULL;
}

short threadInfo_enqueue(const p_threadInfo tq, const void *data){
	return threadQueue_enqueue(tq->queue, data);
}

void *threadInfo_dequeue(const p_threadInfo tq){
	return threadQueue_dequeue(tq->queue);
}
