# How to statically link

Yes this is redundant; It's actually a dummy file!

````sh
gcc -c $(DESIRED_INPUT_SRC_FILES) -o $(DESIRED_OUTPUT_FILES) # Do each of these seperately
ar $(DESIRED_INPUT_FILES) -rcs $(DESIRED_OUTPUT_FILE)
# Use some tool to generate a single header for all the included code.
gcc $(ANOTHER_PROJECT) $(RESULING_LIBRARY) # The output .a file can be added to the input source file and it should work.
````
