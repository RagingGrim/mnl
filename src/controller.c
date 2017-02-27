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

short threadQueue_enqueue(const p_threadQueue tq, const void *data){
	pthread_mutex_lock(tq->mutex);
	short val = circularList_enqueue(tq->queue, data);
	pthread_mutex_unlock(tq->mutex);
	return val;
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

	for(size_t i = 0 ; i < tc->threads->elements ; i++)
		free(vvector_at(tc->threads, i));


	vvector_free(tc->threadQueues);
	vvector_free(tc->threads);
	free(tc);
	tc = NULL;
}

short threadController_pushback(const threadController *tc,void *(* routine)(void *), void *data){
	p_threadQueue tq = threadQueue_init();
	if(!tq)
		return VVECTORE_GROW;

	pthread_t *id = malloc(sizeof(pthread_t));
	if(!id){
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}

	//TODO: Make sure to pass the threads queue to the actual thread.
	p_threadInfo ti = threadInfo_init_no_queue();
	ti->queue = tq;
	ti->reserved = data;

	if(!ti){
		free(id);
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}

	if( pthread_create(id, NULL, routine, ti) != 0 ){
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}
	else{
		pthread_join(*id, NULL);
	}


	//TODO: Remember to fix error handling here ( aka , stop the thread if it has been started and an error occurs during the push.

	short ret = vvector_push(tc->threads, id);
	if( ret != VVECTORE_OK)
		return VVECTORE_GROW;

	ret = vvector_push(tc->threadQueues, tq);
	if(ret != VVECTORE_OK){
		vvector_pop(tc->threads);
		threadQueue_free(tq);
		return VVECTORE_GROW;
	}

	return VVECTORE_OK;
}

short threadController_messsage(const threadController *tc, const size_t at, void *msg){
	void *data = vvector_at(tc->threads, at);
	if(data){
		p_threadQueue tq = vvector_at(tc->threadQueues, at); // Should never have to check this return value
		if(tq){
			return threadQueue_enqueue(tq, msg);
		}
	}
	return VVECTORE_GROW;
}

void threadController_stopAll(const threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++){
		// pthread_join(*(pthread_t *)vvector_at(tc->threads , i), NULL);
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
	}
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
