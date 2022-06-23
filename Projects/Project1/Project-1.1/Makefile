CC = gcc
CFLAGS = -g -std=c89 -Wpedantic -Wall -Wextra -Werror
TRANSLATOR_FILES = src/compression.c src/utils.c
DEBUG_CFLAGS = -g -std=c11 -Wall -Wextra

all: translator

cmt:
	python3 block_comment.py

debug:
	$(CC) $(DEBUG_CFLAGS) -o translator translator.c $(TRANSLATOR_FILES)

translator: clean
	$(CC) $(CFLAGS) -o translator translator.c $(TRANSLATOR_FILES)

clean:
	@-$(MAKE) --no-print-directory -C test clean
	@-rm -f *.o translator
	@-rm -rf __pycache__
	
grade: translator
	@$(MAKE) --no-print-directory -C test grade
