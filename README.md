# Description


mnl ( multithreaded-networking-library ) is a tool to rapidly develop applications using c , the Berkley socket library and POSIX pthreads. The library will be extensively tested.

To use the code run make inside of mnl. It will generate a mnl.a file which you can copy to your project directory. To compile simply do

## Static Linking:
```bash
$(CC) main.c mnl.a
```

## Dynamic Linking:
```bash
$(CC) main.c -lmnl
```

I will manually generate the single header for the library everytime.

# Cpp

Please note to use this library with cpp you need to do a
```cpp
extern "C" {
	include "mnl.h"
}
```

## Controllers
The library exposes a thread controller which can be used to communicate between server and master threads.

A controller is initialised by:

```C
p_threadController tc = threadController_init();
```
___
Creating a thread which starts on function hello:
```C
void *Hello(void *data){
	//Do stuff
}

threadController_pushback(tc, Hello, NULL);
```


To clean up memory used by the controller:
```C
	threadController_destroy(tc);
```

Planned Features:
- Add a structure which makes loading plugins as so files easier.
