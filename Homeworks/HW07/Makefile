CXX = g++
CXX_FLAGS = -Wpedantic -Wall -Wextra -Werror -std=c++14
DBG_FLAGS = -Wpedantic -Wall -Wextra -std=c++14 -g -M
INC_FILES = ringbuffer.hpp ringbuffer.ipp
SRC_FILES = main.cpp

all: ${INC_FILES} ${SRC_FILES}
	${CXX} ${CXX_FLAGS} -o main ${SRC_FILES}

debug: ${INC_FILES} ${SRC_FILES}
	${CXX} ${DBG_FLAGS} -o main ${SRC_FILES}

memcheck: main
	valgrind --tool=memcheck --leak-check=full ./main

clean:
	rm -f main

submit: ${INC_FILES}
	tar -cvf hw7.tar ringbuffer.ipp

.PHONY: clean
