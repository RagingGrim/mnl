CC=clang
STD=c11
L_FLAGS=-O2 -shared
FLAGS=-O2 -fPIC -c

mnl: mnl_generate_headers
	clang -fPIC src/*.c -shared -o build/mnl.so
	@echo "Dynamic library built."

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
	tar -czvf ./build/mnl.tar.gz ./build/mnl.h ./build/mnl.so
	
