CC=clang
STD=c11
FLAGS=-02

mnl: mnl_compile mnl_generate_headers
	ar -rcs build/mnl.a build/*.o
	@rm build/*.o
	@echo "Static library built."

mnl_compile:
	@echo "Compiling . . ."
	$(CC) -c src/buffer.c -o build/buffer.o
	$(CC) -c src/controller.c -o build/controller.o
	$(CC) -c src/debug.c -o build/debug.o
	$(CC) -c src/logger.c -o build/logger.o
	$(CC) -c src/networking.c -o build/networking.o
	$(CC) -c src/vVector.c -o build/vVector.o
	$(CC) -c src/circularList.c -o build/circularList.o
	$(CC) -c src/chttp.c -o build/chttp.o

mnl_generate_headers:
	@echo "Generating header . . . "
	@touch build/mnl.h
	@printf "#ifndef MNL_H_GUARD\n#define MNL_H_GUARD\n" > build/mnl.h
	# Can't use * because the order in which the header is printed matters
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/buffer.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/vVector.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/circularList.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/debug.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/logger.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/networking.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/controller.h >> build/mnl.h
	grep -v '//<<MARK IGNORE>>'  --no-filename  lib/chttp.h >> build/mnl.h

	@printf "#endif\n" >> build/mnl.h

mnl_debug:
	clang build/main.c build/mnl.a -ggdb -lm -lpthread -o build/a.out
