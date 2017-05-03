#include <iostream>
extern "C" {
#include "mnl.h"
}

int main(const int argc,const char **argv){
	std::cout << "hurdurhur c++" << std::endl;
	p_threadController tc = threadController_init();
}
