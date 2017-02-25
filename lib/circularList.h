#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H
// INCLUDES
#include "../lib/vVector.h" //<<MARK IGNORE>>
// DEFINES

#define p_circularList p_vvector	// Circular lists are in essence just vvectors.
#define circularList vvector		// TODO: This is temporary and should be fixed in before release 2.
#define circularList_free vvector_free
#define circularList_init vvector_init

short circularList_enqueue(p_circularList cl, const void *pnter);
void *circularList_dequeue(p_circularList cl);
#endif
