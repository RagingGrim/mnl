# Description


mnl ( multithreaded-networking-library ) is a tool to rapidly develop applications using c , the Berkley socket library and POSIX pthreads. The library will be extensively tested.

To use the code run make inside of mnl. It will generate a mnl.a file which you can copy to your project directory. To compile simply do

# Building
Use tab to see the different make targets.

# Cpp

Please note to use this library with cpp you need to do a
```cpp
extern "C" {
	include "mnl.h"
}
```

