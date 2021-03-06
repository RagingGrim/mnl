#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/errno.h>
#include "../lib/logger.h"


logger *logger_init(const char *file){
	logger *newLogger = malloc( sizeof(logger) );
	if( !newLogger )
		return NULL;

	if( file ){
		newLogger->file = fopen(file, "a");
		newLogger->mutex_logOut = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(newLogger->mutex_logOut, NULL);

		if( !newLogger->file ){
			free(newLogger);
			return NULL;
		}
	}
	else{
		newLogger->file = NULL;
	}

	newLogger->mutex_stdOut = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(newLogger->mutex_stdOut, NULL);
	return newLogger;
}

void logger_destroy(logger *log){
	if( log->file ){
		pthread_mutex_lock(log->mutex_logOut);
		pthread_mutex_unlock(log->mutex_logOut);
		pthread_mutex_destroy(log->mutex_logOut);
		free(log->mutex_logOut);

		fclose(log->file);
	}

	pthread_mutex_lock(log->mutex_stdOut);
	pthread_mutex_unlock(log->mutex_stdOut);
	pthread_mutex_destroy(log->mutex_stdOut);
	free(log->mutex_stdOut);

	free(log);
	log = NULL;
	return;
}

void logIt(logger* log , const char *string){
	if( log->file ){
		size_t len = strlen(string);
		pthread_mutex_lock( log->mutex_logOut );
		fwrite(string, 1,len , log->file);	//TODO: Using fwrite to write the raw size might not always work.
		pthread_mutex_unlock( log->mutex_logOut );
	}

	pthread_mutex_lock( log->mutex_stdOut );
	printf("%s",string);
	pthread_mutex_unlock( log->mutex_stdOut );
}
