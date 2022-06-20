#!/bin/bash

# The first step is to generate .o files, that is 
# ringbuffer.c   ==>   ringbuffer.o
# test.c         ==>   test.o
gcc -Wpedantic -Wall -Wextra -Werror -std=c89 -c ringbuffer.c -o ringbuffer.o
gcc -Wpedantic -Wall -Wextra -Werror -std=c89 test.c -c -o test.o


# Generate a static lib (.a) from ringbuffer.o
# The 'ar' command is used for generating static lib from .o files
# '-c' arg means 'create', '-r' arg means rewrite
ar -r libringbuffer.a ringbuffer.o


# link the static lib with the test.o file to create a static-linked executable
# by using 'ld'
ld -o staticringbuffer test.o libringbuffer.a -lc

# generate a static library 
# rb.c, rb.h ==> libringbuffer.a

# test.c ==> test.o


# create a static-linked executable
# libringbuffer.a, test.c ==> staticringbuffer

# chmod +x ./staticringbuffer  # this sentence might be unnecessary


# static library (.a) and dynamic library (.so) are all created 
# from .o files, so we need to produce .o files first (gcc -c xx.c -o xx.o)

# then, we need to produce a .a file (static library) from the .o file
# by using 'ar' command (ar -r means replace, -c means create)

# finally, we need to use the static library in our program.
# -L indicates the position where the compiler can find the library (. for current dir)
# -l indicates the name of the lib (.a / .so) can be omitted