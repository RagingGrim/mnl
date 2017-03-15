#include "../lib/controller.h"
#include <stdlib.h> //TODO: REMOVE
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
	if(tq->queue->elements == 0){
		pthread_mutex_unlock(tq->mutex);
		return NULL;
	}
	void *data = circularList_dequeue(tq->queue);
	pthread_mutex_unlock(tq->mutex);
	return data;
}

// Thread Controller
threadController *threadController_init(){
	p_threadController tc = malloc(sizeof(threadController));
	if(!tc)
		return NULL;

	tc->threads = vvector_init();
	if(!tc->threads){
		free(tc);
		return NULL;
	}

	tc->threadQueues = vvector_init();
	if(!tc->threadQueues){
		vvector_free(tc->threads);
		free(tc);
		return NULL;
	}

	tc->controllerQueue = threadQueue_init();
	if(!tc->controllerQueue){
		vvector_free(tc->threadQueues);
		vvector_free(tc->threads);
		free(tc);
		return NULL;
	}

	return tc;
}

void threadController_destroy(threadController *tc){
	void *someData;

	do{
		someData = vvector_pop(tc->threadQueues);
		if(someData){
			void *id = vvector_pop(tc->threads);
			pthread_join(*(pthread_t *)id, NULL);
			free(id);
		}


	}while(someData);

	vvector_free(tc->threads);
	vvector_free(tc->threadQueues);
	threadQueue_free(tc->controllerQueue);
	free(tc);
}

void *threadController_trampoline(void *data){
	p_threadInfo ti = data;
	ti->routine(data);
	threadInfo_free(ti);
	return NULL;
}

short threadController_pushback(const threadController *tc,void *(* routine)(void *), void *data){
	pthread_t *id = malloc(sizeof(pthread_t));
	if(!id)
		return VVECTORE_GROW;

	if(vvector_push(tc->threads, id) != VVECTORE_OK){
		free(id);
		return VVECTORE_GROW;
	}

	p_threadQueue tq = threadQueue_init();
	if(!tq){
		free(vvector_pop(tc->threads));
		return VVECTORE_GROW;
	}

	if(vvector_push(tc->threadQueues, tq) != VVECTORE_OK){
		free(vvector_pop(tc->threads));
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}

	p_threadInfo ti = threadInfo_init_no_queue();
	if(!ti){
		threadQueue_free(vvector_pop(tc->threadQueues));
		free(vvector_pop(tc->threads));
		return VVECTORE_GROW;
	}

	ti->queue =  tq;
	ti->reserved = data;
	ti->routine = routine;
	ti->controllerQueue = tc->controllerQueue;

	if(pthread_create(id, NULL, threadController_trampoline, ti) != 0){
		threadQueue_free(vvector_pop(tc->threadQueues));
		free(vvector_pop(tc->threads));
		return VVECTORE_GROW;
	}

	return VVECTORE_OK;
}

short threadController_messsage(const threadController *tc, const size_t at, void *msg){
	return threadQueue_enqueue(vvector_at(tc->threadQueues, at), msg);
}

void threadController_stopAll(const threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++)
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
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
