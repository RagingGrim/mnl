CC=clang
STD=c11
FLAGS=-02


mnl: mnl_compile mnl_generate_headers
	@ar -rcs build/mnl.a build/*.o
	@rm build/*.o
	@echo "Static library built."

mnl_compile:
	@echo "Compiling . . ."
	@clang -c src/buffer.c -o build/buffer.o
	@clang -c src/controller.c -o build/controller.o
	@clang -c src/debug.c -o build/debug.o
	@clang -c src/logger.c -o build/logger.o
	@clang -c src/networking.c -o build/networking.o
	@clang -c src/vVector.c -o build/vVector.o

mnl_generate_headers:
	@echo "Generating header . . . "
	@touch build/mnl.h
	@printf "#ifndef MNL_H_GUARD\n#define MNL_H_GUARD\n" > build/mnl.h
	@cat lib/*.h >> build/mnl.h
	@printf "#endif" >> build/mnl.h
