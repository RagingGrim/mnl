#include <stdlib.h>
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

short threadController_pushback(threadController *tc,pthread_t id){
	pthread_t *temp = malloc(sizeof(pthread_t));
	*temp = id;
	return vvector_push(tc->threads , temp);
}

void threadController_stopAll(threadController *tc){
	for(size_t i = 0 ; i < tc->threads->elements ; i++){
		pthread_join(*(pthread_t *)vvector_at(tc->threads , i), NULL);
		pthread_cancel(*(pthread_t *)vvector_at(tc->threads , i));
	}
}
