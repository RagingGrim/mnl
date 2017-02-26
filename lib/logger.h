#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <pthread.h>
// DEFINES
#define CHUNK_SIZE 265

// STRUCTURES
typedef struct logger{
	FILE *file;
	pthread_mutex_t *mutex_stdOut;
	pthread_mutex_t *mutex_logOut;
}logger, *p_logger;

// FUNCTIONS
logger *logger_init(const char *file);
void logger_destroy(logger *log);
void logIt(logger* log , const char *string);

#endif
