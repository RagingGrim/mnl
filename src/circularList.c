#include "../lib/circularList.h"

short circularList_enqueue(p_circularList cl, const void *pnter){
	return vvector_push(cl, pnter);
}

void *circularList_dequeue(p_circularList cl){
	return vvector_pop_bottom(cl);
}
