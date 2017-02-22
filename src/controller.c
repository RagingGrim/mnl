#include "../lib/controller.h"
/*
	I'll have to refactor all of this code.
	I changed the library functions and how they work so now things are a tad more complex.
*/
threadController *threadController_init(){
	threadController *tc = malloc(sizeof(threadController));
	if( !tc )
		goto cleanup;

	tc->threads = vvector_init();
	if( !tc->threads )
		goto cleanup_one;

	return tc;

	cleanup_one:
		free(tc);
	cleanup:
		return NULL;
}

void threadController_destroy(threadController *tc){
	for( size_t i = 0 ; i < tc->threads->elements ; i++ )
		free(tc->threads->data[i]);
	vvector_free(tc->threads);
	tc->threads = NULL;

	free(tc);
	tc = NULL;
}

short threadController_pushback(const threadController *tc,const pthread_t id){
	pthread_t *temp = malloc(sizeof(pthread_t));
	*temp = id;
	return vvector_push(tc->threads , temp);
}

void threadController_stopAll(const threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++){
		// pthread_join(*(pthread_t *)vvector_at(tc->threads , i), NULL);
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
	}
}



// SIGNALS

p_signalStruct signal_init(){
	p_signalStruct signalStruct = malloc(sizeof(struct signalStruct));
	if(!signalStruct)
		return NULL;

	signalStruct->master_signal = THREAD_SIGNAL_READY;
	signalStruct->thread_signal = THREAD_SIGNAL_READY;
	signalStruct->_mutex_thread_signal = malloc(sizeof(pthread_mutex_t));
	if(!signalStruct->_mutex_thread_signal)
		goto signal_cleanup_one;

	signalStruct->_mutex_master_signal = malloc(sizeof(pthread_mutex_t));
	if(!signalStruct->_mutex_thread_signal)
		goto signal_cleanup_two;

	pthread_mutex_init(signalStruct->_mutex_thread_signal, NULL);
	pthread_mutex_init(signalStruct->_mutex_master_signal, NULL);
	return signalStruct;

	signal_cleanup_two:
	free(signalStruct->_mutex_thread_signal);
	signal_cleanup_one:
	free(signalStruct);
	return NULL;
}

void signal_destroy(p_signalStruct signalStruct){
	signalStruct->master_signal = THREAD_SIGNAL_READY;
	signalStruct->thread_signal = THREAD_SIGNAL_READY;

	pthread_mutex_destroy(signalStruct->_mutex_thread_signal);
	pthread_mutex_destroy(signalStruct->_mutex_master_signal);

	free(signalStruct->_mutex_thread_signal);
	free(signalStruct->_mutex_master_signal);

	free(signalStruct);
	signalStruct = NULL;
}

void signal_set_thread(const p_signalStruct signalStruct,const unsigned short value){
	pthread_mutex_lock(signalStruct->_mutex_thread_signal);
	signalStruct->thread_signal = value;
	pthread_mutex_unlock(signalStruct->_mutex_thread_signal);
}

void signal_set_master(const p_signalStruct signalStruct,const unsigned short value){
	pthread_mutex_lock(signalStruct->_mutex_master_signal);
	signalStruct->master_signal = value;
	pthread_mutex_unlock(signalStruct->_mutex_master_signal);
}

const unsigned short signal_get_thread(const p_signalStruct signalStruct){
	pthread_mutex_lock(signalStruct->_mutex_thread_signal);
	unsigned short value = signalStruct->thread_signal;
	pthread_mutex_unlock(signalStruct->_mutex_thread_signal);
	return value;
}

const unsigned short signal_get_master(const p_signalStruct signalStruct){
	pthread_mutex_lock(signalStruct->_mutex_master_signal);
	unsigned short value = signalStruct->master_signal;
	pthread_mutex_unlock(signalStruct->_mutex_master_signal);
	return value;
}
