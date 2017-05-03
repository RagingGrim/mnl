CC=clang
DYNAMIC_FLAGS=-fPIC -shared
OPT_FLAGS=-O3
FLAGS=$(OPT_FLAGS) -fPIC -c
STD=c11

default: dynamic 
	@echo "Dynamic build finished"

dynamic: gen_headers
	$(CC) $(OPT_FLAGS) $(DYNAMIC_FLAGS) src/*.c -o build/mnl.so

static: gen_headers 
	$(CC) $(FLAGS) src/controller.c -o build/controller.o
	$(CC) $(FLAGS) src/debug.c -o build/debug.o
	$(CC) $(FLAGS) src/logger.c -o build/logger.o
	$(CC) $(FLAGS) src/networking.c -o build/networking.o
	$(CC) $(FLAGS) src/vVector.c -o build/vVector.o
	$(CC) $(FLAGS) src/circularList.c -o build/circularList.o
	$(CC) $(FLAGS) src/chttp.c -o build/chttp.o
	$(CC) $(FLAGS) src/map.c -o build/map.o
	$(CC) $(FLAGS) src/llist.c -o build/llist.o
	ar rcs build/mnl.a build/*.o
	@echo "Static build finished"


gen_headers:
	@if [ ! -d "build" ]; then mkdir "build"; fi
	@echo "Generating header . . . "
	@touch build/mnl.h
	@printf "#ifndef MNL_H_GUARD\n#define MNL_H_GUARD\n" > build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/vVector.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/circularList.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/debug.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/logger.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/networking.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/controller.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/chttp.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/map.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/llist.h >> build/mnl.h
	@printf "#endif\n" >> build/mnl.h

package: static dynamic 
	cd ./build && tar -czvf mnl.tar.gz *.a *.so *.h
	@mv ./build/mnl.tar.gz ../
	@$(MAKE) clean
	@mv ../mnl.tar.gz ./build/
	@echo "Package generated."
clean:
	@rm -f ./build/*
