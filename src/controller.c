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

	tq->mutex = malloc(sizeof(pthread_mutex_t));
	if(!tq->mutex){
		free(tq);
		tq = NULL;
		return NULL;
	}
	pthread_mutex_init(tq->mutex, NULL);

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

void threadQueue_enqueue(const p_threadQueue tq, const void *data){
	pthread_mutex_lock(tq->mutex);
	circularList_enqueue(tq->queue, data);
	pthread_mutex_unlock(tq->mutex);
}

void *threadQueue_dequeue(const p_threadQueue tq){
	pthread_mutex_lock(tq->mutex);
	void *data = circularList_dequeue(tq->queue);
	pthread_mutex_unlock(tq->mutex);
	return data;
}

// Thread Controller
threadController *threadController_init(){
	p_threadController tc = malloc(sizeof(threadController));
	if(!tc)
		return NULL;

	tc->threadQueues = vvector_init();
	if(!tc->threadQueues){
		free(tc);
		return NULL;
	}

	tc->threads = vvector_init();
	if(!tc->threads){
		vvector_free(tc->threadQueues);
		free(tc);
		return NULL;
	}

	return tc;
}

void threadController_destroy(threadController *tc){
	for(size_t i = 0 ; i < tc->threadQueues->elements ; i++)
		threadQueue_free(tc->threadQueues->data[i]);
	vvector_free(tc->threadQueues);
	vvector_free(tc->threads);
	free(tc);
	tc = NULL;
}

short threadController_pushback(const threadController *tc,const pthread_t id){
	short ret = vvector_push(tc->threads, &id);
	if( ret != VVECTORE_OK)
		return VVECTORE_GROW;

	p_threadQueue tq = threadQueue_init();
	if(!tq){
		vvector_pop(tc->threads);
		return VVECTORE_GROW;
	}


	ret = vvector_push(tc->threadQueues, tq);
	if(ret != VVECTORE_OK){
		vvector_pop(tc->threads);
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}

	return VVECTORE_OK;
}

void threadController_stopAll(const threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++){
		// pthread_join(*(pthread_t *)vvector_at(tc->threads , i), NULL);
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
	}
}



// Thread Info
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

	ti->reserved = vvector_init();
	if(!ti->reserved){
		threadQueue_free(ti->queue);
		free(ti);
		return NULL;
	}
	return ti;
}

void threadInfo_free(p_threadInfo ti){
	threadQueue_free(ti->queue);
	vvector_free(ti->reserved);
	free(ti);
	ti = NULL;
}

void threadInfo_enqueue(const p_threadInfo tq, const void *data){
	threadQueue_enqueue(tq->queue, data);
}

void *threadInfo_dequeue(const p_threadInfo tq){
	return threadQueue_dequeue(tq->queue);
}
