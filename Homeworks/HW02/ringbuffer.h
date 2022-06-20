#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* To use boolean expressions */
typedef int bool;
#define true (1)
#define false (0)

/* Initial size of the buffer */
#define RING_BUFFER_INIT_SIZE       8

/* You should grow buffer size to RING_BUFFER_GROW_FACTOR1 * capacity, when current capacity < 1024
   And RING_BUFFER_GROW_FACTOR2 * capacity, when current capacity >= 1024 */
#define RING_BUFFER_GROW_FACTOR1    2
#define RING_BUFFER_GROW_FACTOR2    1.5

/* The ring_buffer structure */
typedef struct ring_buffer_{
    size_t      capacity;
    size_t      read_pos;
    size_t      write_pos;
    int*        content;
} ring_buffer;

/* A function pointer for mapping operations */
typedef int(*map_func)(int);

/* Create a new ring buffer. You should allocate memory for its content,
   initialize the read_pos, write_pos and capacity properly. 
   And finally return a pointer to the new ring buffer. */
ring_buffer* ring_buffer_new();

/* Destroy the given ring buffer, free all resources you've allocated.
   Finally you should set the buffer pointer to NULL, that is why we pass
   ring_buffer** as parameter, instead of ring_buffer*. */
void ring_buffer_destroy(ring_buffer** buffer);

/* Returns true if the given ring buffer is empty, false otherwise */
bool ring_buffer_is_empty(const ring_buffer* buffer);

/* Read an element from the ring buffer (i.e., the dequeue operation), *data records 
   the element popped. returns true if the operation succeeded, false otherwise. */
bool ring_buffer_read(ring_buffer* buffer, int* data);

/* Write an element which value is `data` to the ring buffer (i.e., the enqueue operation),
   returns true if the operation succeeded, false otherwise. Note that when the buffer is 
   full, grow its size to make sure the element can be write successfully. The detailed 
   requirements of size growth are in the homework description. */
bool ring_buffer_write(ring_buffer* buffer, const int data);

/* Read "rdsize" elements from the ring buffer, and fill them to "data".
   Notice that you should only return true when this operation succeeds.
   If there are not enough elements in the buffer, just DO NOTHING and 
   return false. DO NOT modify the ring buffer and data for such cases. */
bool ring_buffer_read_multi(ring_buffer* buffer, size_t rdsize, int* data);

/* Write "wrtsize" elements to the ring buffer. The values to write are 
   provided in "data". Returns true if succeeds, false otherwise. Don't 
   forget to grow your buffer size properly. */
bool ring_buffer_write_multi(ring_buffer* buffer, size_t wrtsize, const int* data);

/* For every element in the ring buffer, apply "func" to it. For example,
   Your buffer currently contains 3 elements 1, 2, 4. If the map function is to 
   "add five", then their values should be 6, 7, 9 after calling this function. */
bool ring_buffer_map(ring_buffer* buffer, map_func func);

#endif

