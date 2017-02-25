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

	tc->queues = vvector_init();
	if( !tc->queues )
		goto cleanup_two;

	return tc;

	cleanup_two:
		free(tc->threads);
	cleanup_one:
		free(tc);
	cleanup:
		return NULL;
}

void threadController_destroy(threadController *tc){
	for( size_t i = 0 ; i < tc->threads->elements ; i++ ){
		free(tc->threads->data[i]);
		vvector_free(&tc->queues[i]);
	}

	vvector_free(tc->threads);
	vvector_free(tc->queues);
	tc->threads = NULL;

	free(tc);
	tc = NULL;
}

short threadController_pushback(const threadController *tc,const pthread_t id){
	pthread_t *temp = malloc(sizeof(pthread_t));
	if(!temp)
		return VVECTORE_GROW;
	*temp = id;

	p_vvector vector = vvector_init();
	if( !vector ){
		free(temp);
		return VVECTORE_GROW;
	}

	short val = vvector_push(tc->queues, vector);
	if(val != VVECTORE_GROW){
		vvector_free(vector);
		free(temp);
		return VVECTORE_GROW;
	}

	return vvector_push(tc->threads , temp);
}

void threadController_stopAll(const threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++){
		// pthread_join(*(pthread_t *)vvector_at(tc->threads , i), NULL);
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
	}
}
