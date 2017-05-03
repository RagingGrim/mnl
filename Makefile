CC=clang
STD=c11
L_FLAGS=-O2 -shared
FLAGS=-O2 -fPIC -c

mnl: mnl_generate_headers
	clang -fPIC src/*.c -shared -o build/mnl.so
	@echo "Static library built."

mnl_compile:
	@echo "Compiling . . ."
	$(CC) $(FLAGS) src/controller.c -o build/controller.o
	$(CC) $(FLAGS) src/debug.c -o build/debug.o
	$(CC) $(FLAGS) src/logger.c -o build/logger.o
	$(CC) $(FLAGS) src/networking.c -o build/networking.o
	$(CC) $(FLAGS) src/vVector.c -o build/vVector.o
	$(CC) $(FLAGS) src/circularList.c -o build/circularList.o
	$(CC) $(FLAGS) src/chttp.c -o build/chttp.o
	$(CC) $(FLAGS) src/map.c -o build/map.o
	$(CC) $(FLAGS) src/llist.c -o build/llist.o	

mnl_generate_headers:
	@echo "Generating header . . . "
	@touch build/mnl.h
	@printf "#ifndef MNL_H_GUARD\n#define MNL_H_GUARD\n" > build/mnl.h
	# Can't use * because the order in which the header is printed matters
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

mnl_debug:
	clang build/main.c build/mnl.a -ggdb -lm -lpthread -o build/a.out


package: mnl
	tar -czvf ./build/mnl.tar.gz ./build/mnl.h ./build/mnl.a
	
