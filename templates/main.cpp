#include <iostream>

extern "C"{
#include "mnl.h"
}

/*
 * The compiler needs to know that you're using C bindings.
 */

int main(){
	p_threadController tc = threadController_init();
}
