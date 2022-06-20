#include <stdint.h>
#include <stdio.h>
#include <time.h>

#define PRINT_SIZE(x) printf("Size of " #x ": %d\n", (unsigned int)sizeof(x))

int main(void) {
    PRINT_SIZE(char);
    PRINT_SIZE(short);
    PRINT_SIZE(short int);
    PRINT_SIZE(int);
    PRINT_SIZE(long int);
    PRINT_SIZE(unsigned int);
    PRINT_SIZE(void*);
    PRINT_SIZE(size_t);
    PRINT_SIZE(float);
    PRINT_SIZE(double);
    PRINT_SIZE(int8_t);
    PRINT_SIZE(int16_t);
    PRINT_SIZE(int32_t);
    PRINT_SIZE(int64_t);
    PRINT_SIZE(time_t);
    PRINT_SIZE(clock_t);
    PRINT_SIZE(struct tm);
    PRINT_SIZE(NULL);

    return 0;
}

/*

 * The output is as follows:

 *      typename       size in -m64      size in -m32
 * Size of char:             1               same
 * Size of short:            2               same
 * Size of short int:        2               same
 * Size of int:              4               same
 * Size of long int:         8               same
 * Size of unsigned int:     4               same
 * Size of void*:            8                 4
 * Size of size_t:           8                 4
 * Size of float:            4               same
 * Size of double:           8               same
 * Size of int8_t:           1               same
 * Size of int16_t:          2               same
 * Size of int32_t:          4               same
 * Size of int64_t:          8               same
 * Size of time_t:           8                 4
 * Size of clock_t:          8                 4
 * Size of struct tm:       56                44
 * Size of NULL:             8                 4
 */
