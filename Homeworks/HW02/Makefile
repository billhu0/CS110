CC=gcc
CFLAGS=-Wpedantic -Wall -Wextra -Werror -std=c89
# CFLAGS=-Wall -Wextra -std=c11

all: main

main: main.c ringbuffer.c ringbuffer.h
	${CC} ${CFLAGS} ringbuffer.c main.c -o main

debug: main.c ringbuffer.c ringbuffer.h
	${CC} ${CFLAGS} ringbuffer.c main.c -o main -g

memcheck: main
	valgrind --tool=memcheck --leak-check=full ./main

submit:
	tar -cvf hw2.tar ringbuffer.c dynamiclib.sh staticlib.sh

clean:
	rm -f ./main
	rm -f ./*.o

fuck: main.c ringbuffer.c ringbuffer.h
	python3 fuck_comment.py
	${CC} ${CFLAGS} ringbuffer.c main.c -o main

.PHONY: clean