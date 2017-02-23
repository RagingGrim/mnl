#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H
// INCLUDES
#include <stdlib.h>
// DEFINES

// STRUCTURES
typedef struct node{
	void *elem;
	struct node *next;
}node, *p_node;

typedef struct cl{
	p_node tail;
}circularList, *p_circularList;
// FUNCTIONS ( NODE )
p_node node_init();
p_node node_init_adv(const void *elem);
void node_free(p_node node);

// FUNCTION ( CIRCULAR LIST )
p_circularList circularList_init();
void circularList_free(p_circularList cl);
short circularList_insertHead(const p_circularList cl, const p_node node);
void circularList_deleteTail(const p_circularList cl);
const p_node circularList_at(const p_circularList cl, const size_t size);
const size_t circularList_getSize(const p_circularList cl);

#endif
