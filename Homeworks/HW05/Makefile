CC=gcc
CFLAGS=-Wpedantic -Wall -Wextra -Werror -std=c89 -O3
SRC=image.c main.c mathematics.c
LIBS=-lm -lpthread

BINARIES=hw5

hw5:
	${CC} ${CFLAGS} -o hw5 ${SRC} ${LIBS}

clean:
	rm hw5