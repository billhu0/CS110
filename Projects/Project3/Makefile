CC = gcc-9
CFLAGS = -O2 -fopenmp -mavx2 -mavx -march=native -mfma
LIBS = -lm
all : base_test fast_test check_test

clean:
	@-rm -f *.o gbfloat_base
	@-rm -f *.o gbfloat_fast
	@-rm -f *.o test_accuracy
	
base:
	@-rm -f *.o gbfloat_base
	$(CC) $(CFLAGS) -o gbfloat_base gbfloat_base.c $(LIBS)

fast:
	@-rm -f *.o gbfloat_fast
	$(CC) $(CFLAGS) -o gbfloat_fast gbfloat_fast.c $(LIBS)

check:
	@-rm -f *.o test_accuracy
	$(CC) $(CFLAGS) -o test_accuracy test_accuracy.c $(LIBS)

base_test: base
	./gbfloat_base test.jpg test_base.jpg 0.6 -2.0 2.0 1001 201

fast_test: fast
	./gbfloat_fast test.jpg test_fast.jpg 0.6 -2.0 2.0 1001 201

check_test: check
	./test_accuracy test_base.jpg test_fast.jpg

 