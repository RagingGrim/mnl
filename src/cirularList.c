#include "../circularList.h"

p_node node_init(){
	return node_init_adv(NULL);
}

p_node node_init_adv(const void *elem){
	p_node node = malloc(sizeof(struct node));
	if(!node)
		return NULL;

	node->elem = elem;
	return node;
}

void node_free(p_node node){
	node->elem = NULL;
	free(node);
	node = NULL;
}


// Circular List

p_circularList circularList_init(){
	p_circularList cl = malloc(sizeof(circularList));
	if(!cl)
		return NULL;

	cl->tail = NULL;
}

void circularList_free(p_circularList cl){
	// First implement the linked list then look how to free();
}


short circularList_insertHead(const p_circularList cl, const p_node node){

}

void circularList_deleteTail(const p_circularList cl){
	if(cl->tail == NULL)
		return;


}

const p_node circularList_at(const p_circularList cl, const size_t size){
	if(cl->tail == NULL)
		return NULL;

	size_t i = 0;
	p_node node = cl->tail->next;
	while(node != cl->tail){
		if(i++ == size)
		 	return node;
		node = node->next;
	}
	return node;
}

const size_t circularList_getSize(const p_circularList cl){
	if(cl->tail == NULL)
		return 0;

	size_t size = 0;
	p_node node = cl->tail->next;
	while(node != cl->tail){
		size++;
		node = node->next;
	}

	return size;
}
