#!/bin/bash

# test.c  ==>   test.o
gcc -Wpedantic -Wall -Wextra -Werror -std=c89 -c test.c -o test.o

# ringbuffer.c   ==>   libringbuffer.so (dynamic lib file)
gcc -fPIC -shared -Wpedantic -Wall -Wextra -Werror -std=c89 -c ringbuffer.c -o libringbuffer.so 
# The above is equal to the following two commands
# Step 1. ringbuffer.c   ==>   ringbuffer.o
#         gcc -Wpedantic -Wall -Wextra -Werror -std=c89 ringbuffer.c -c -o ringbuffer.o
# Step 2. ringbuffer.o   ==>   ringbuffer.so
#         gcc -fPIC -shard -o libringbuffer.so ringbuffer.o

#  test.o, libringbuffer.so   ==>(link)==>   dynamicringbuffer (executable)
gcc -o dynamicringbuffer test.o -L ./ -Bdynamic -lringbuffer # (.so can be omitted)
# In the above line, 
# '-L ./' means 'refer to the current directory to look for the dynamic lib file'
# '-Bdynamic' means using a dynamic lib
# -lxxx means using the libxxx.so file (the '.so' suffix can be ommitted)