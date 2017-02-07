#ifndef TIMER_H
#define TIMER_H
// DEFINES

// STRUCTURES
typedef struct timer{
void (*_func)(void *data);
size_t _seconds;
void *_data;
pthread_t *id;
}timer;

// FUNCTIONS
void *timer_func(void *data);

#endif
