#ifndef MNL_H_GUARD
#define MNL_H_GUARD
#ifndef VVECTOR_H_GUARD
#define VVECTOR_H_GUARD
// Includes
#include <stdlib.h>

// Constants
#define VVECTOR_CHUNK_SIZE 250

// Error Constants
#define VVECTORE_OK 0
#define VVECTORE_GROW 1


// Structures
typedef struct vvector{
	void **data;
	size_t chunkSize; // Chunk size will be doubled every time it's reached.
	size_t elements;
	} *p_vvector , vvector;

// Functions
p_vvector vvector_init();
p_vvector vvector_init_adv(const size_t chunkSize);
void vvector_free(p_vvector vector);

short _vvector_grow(const p_vvector vector); // _because it's an internal function.
short vvector_push(const p_vvector vector, const void *element);
void *vvector_pop(const p_vvector vector);
void *vvector_pop_bottom(const p_vvector vector);
void *vvector_at(const p_vvector vector, const size_t i);
void *vvector_set(const p_vvector vector, void *p, const size_t i);
void *vvector_delete(const p_vvector vector ,const size_t i);


#endif
#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H
// INCLUDES
// DEFINES

#define p_circularList p_vvector	// Circular lists are in essence just vvectors.
#define circularList vvector		// TODO: This is temporary and should be fixed in before release 2.
#define circularList_free vvector_free
#define circularList_init vvector_init

short circularList_enqueue(p_circularList cl, const void *pnter);
void *circularList_dequeue(p_circularList cl);
#endif
#ifndef C_DEBUG_H
#define C_DEBUG_H
#include <stddef.h>
// DEFINES
#define DEBUG_PORT 14

// FUNCTIONS
void debugMsg( const char *msg , short critical );
const char *_genDbgMsg( const char *msg );

char *genData( char Char , size_t Size );
char *genData_addDelim( char Char , char Delim , size_t Size );
char *genData_complicatedStr(size_t Size);
short genData_evalComplicatedStr(char *Data , size_t Size );
#endif
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
#ifndef NETWORKING_H
#define NETWORKING_H
#include <sys/socket.h>
//DEFINES
#define SOCKET_MAGIC_NUMBER 1


// FUNCTIONS
#ifdef __linux__
/**
 * Returns the first ipv4/ipv6 address associated with a hostname.
 * @param  Hostname The hostname to resolve.
 * @param  strIP    The buffer to write the ip to.
 * @param  AI_FAM   AF_INET / AF_INET6
 * @return          Returns 1 on success.
 */
short getAddrP(const char *Hostname,char *strIP,const int AI_FAM);
#endif

/**
 * Receives all incoming data on a BLOCKING socket.
 * @param  Socket Socket to receive on.
 * @param  Buffer Buffer to receive to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t recvAllFixed(int Socket , char *Buffer , const size_t Size , const int Flags);

/**
 * Sends all incoming data on a BLOCKING socket ( This function may be redundant).
 * @param  Socket Socket to send to.
 * @param  Buffer Buffer to send to (preallocated).
 * @param  Size   The amount of bytes to receive
 * @param  Flags  Socket Flags
 * @return        The amount of bytes returned / or -1 for an error
 */
ssize_t sendAllFixed(int Socket , char *Buffer , const size_t Size , int Flags);

// TODO: Check why inside a thread this function isn't setting the ip.
char *get_ip_str(const struct sockaddr *sa, char *s, size_t maxlen);
char *getPeerAddr(const struct sockaddr *sa, socklen_t maxlen);
#endif
/*
	Stores thread id's using vvectors.
*/

#ifndef CONTROLLER
#define CONTROLLER
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


// DEFINES
#define THREAD_SIGNAL_READY 0

// STRUCTURES
typedef struct threadVVector{
	p_vvector _internalVect;
	pthread_mutex_t *mutex;
}threadVector, *p_threadVector;


typedef struct threadQueue{
	p_circularList queue;
	pthread_mutex_t *mutex;
}threadQueue, *p_threadQueue;

typedef struct threadController{
	p_vvector threads;
	p_vvector threadQueues;
	p_threadQueue controllerQueue;
}threadController , *p_threadController;

typedef struct threadInfo{
	p_threadQueue queue;
	p_threadQueue controllerQueue;
	void *(* routine)(void *);
	void *reserved;
}threadInfo, *p_threadInfo;

// FUNCTIONS (THREAD CONTROLLER)
threadController *threadController_init();
void threadController_destroy(threadController *tc);
short threadController_messsage(const threadController *tc, const size_t at, void *msg);
short threadController_pushback(const threadController *tc,void *(* routine)(void *), void *data);
void threadController_stopAll(const threadController *tc);

// FUNCTIONS (THREAD QUEUES)
p_threadQueue threadQueue_init();
void threadQueue_free(p_threadQueue tq);
short threadQueue_enqueue(const p_threadQueue tq, const void *data);
void *threadQueue_dequeue(const p_threadQueue tq);

// FUNCTIONS (THREAD INFO)
p_threadInfo threadInfo_init();
p_threadInfo threadInfo_init_no_queue();
void threadInfo_free(p_threadInfo ti);
void threadInfo_free_no_queue(p_threadInfo ti);
short threadInfo_enqueue(const p_threadInfo tq, const void *data);
void *threadInfo_dequeue(const p_threadInfo tq);


// FUNCTIONS (THREAD VECTORS)
p_threadVector threadVector_init();
void threadVector_free(p_threadVector tv);
short threadVector_push(const p_threadVector tv, const void *data);
void *threadVector_pop(const p_threadVector tv);
void *threadVector_at(const p_threadVector tv, const size_t i);
size_t threadVector_getSize(const p_threadVector tv);
void *threadVector_delete(const p_threadVector tv ,const size_t i);
void *threadVector_set(const p_threadVector tv, void *p, const size_t i);


#endif		//TODO: Implement an advanced pushback function to set the stack size.
#ifndef CHTTP_HEADER_GUARD
#define CHTTP_HEADER_GUARD
// Includes
#include <stdlib.h>
#include <math.h>
#include <string.h>
// #include <bsd/string.h>
#include <stdio.h>
// Defines
#define CHTTPE_OK 0
#define CHTTPE_GROW 1
#define CHTTPE_LOOKUP 2
// Structures
typedef struct chttp{
	char *buffer;
	size_t size;
	}custom_http, *p_custom_http;
// Functions
void *chttp_init();
void chttp_destroy(p_custom_http chttp);
const short chttp_add_header(p_custom_http chttp, const char *data, const size_t size);
const short chttp_add(p_custom_http chttp, const char *data, const size_t size);
const short chttp_grow(const p_custom_http chttp, const size_t size);
char *chttp_lookup(const p_custom_http chttp, const char *key);
const short chttp_finalise(const p_custom_http chttp , const char *data, const size_t size);
char *chttp_getData(const p_custom_http chttp);
const char *_chttp_find(const char *buffer, const size_t bufferSize, const char *find, const size_t findSize);
#endif
#ifndef MAP_H
#define MAP_H
// Includes
#include <stdlib.h>
#include <stdio.h> // TODO: Remove
#include <string.h>
// Typedefs
typedef struct map{
	p_vvector key;
	p_vvector value;
	size_t size;
}basic_map, *p_map;

// Functions

basic_map *mapCreate();
basic_map *mapCreate_fromParams(const int argc ,const char **argv);
void mapDestroy(basic_map *map);
const short mapAdd(basic_map *map, const char *key, const char *value);
const char *mapKeyLookup(const basic_map *map,const char *key);
const char *mapValueLookup(const basic_map *map,const char *value);
const short _mapKeyExist(const basic_map *map,const char *key);
const short _mapValueExist(const basic_map *map,const char *value);
#endif
#ifndef LLIST_H
#define LLIST_H
// Includes
#include <stdlib.h>

// Defines
#define LLIST_EOK 0
#define LLIST_EGROW 1

// Structures
typedef struct node{
	void *data;	
	struct node *next;
}node, *p_node;

typedef struct llist{
	p_node root;
	size_t size;
}llist, *p_llist;

// Function Prototypes (Node)

p_node node_init( const void *data );
void node_free( p_node node );

// Function Prototypes (Linked List)

p_llist llist_init();
short llist_push( const p_llist l ,const p_node node );
short llist_push_adv( const p_llist l, const void *data );
p_node llist_pop( const p_llist l);
p_llist llist_clone();
void llist_free( p_llist list );
#endif 
#endif
