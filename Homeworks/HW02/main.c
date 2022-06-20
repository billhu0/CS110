#include <stdio.h>
#include <assert.h>
#include "ringbuffer.h"

/* A simple map function, which adds an element by 5 */
int add_five(int x){
    return x + 5;
}

/* The main function entry */
int main(){
    /* Get a new ring buffer */
    ring_buffer* rb = ring_buffer_new();
    int i, rbuf[20], wbuf[20];
    printf("Test\n");
    /* Initialize data buffers */
    memset(rbuf, 0, sizeof(rbuf));
    memset(wbuf, 0, sizeof(wbuf));

    /* Write some data */
    for (i = 0; i < 20; i++)
        wbuf[i] = i + 1;
    assert(ring_buffer_write_multi(rb, 20, wbuf));
    printf("001\n");
    /* After write, it cannot be empty */
    assert(!ring_buffer_is_empty(rb));

    /* Read 10 elements by "multi" */
    assert(ring_buffer_read_multi(rb, 10, rbuf));
    for (i = 0; i < 10; i++){
        assert(rbuf[i] == i + 1);
    }
    printf("002\n");
    /* Add all elements by 5 */
    ring_buffer_map(rb, add_five);
    printf("003\n");
    /* Read remaining 10 elements one by one */
    for (i = 10; i < 20; i++){
        int x;
        assert(ring_buffer_read(rb, &x));
        assert(x == i + 6);
    }
    printf("003\n");
    /* Now, it should be empty */
    assert (ring_buffer_is_empty(rb));
    printf("004\n");
    /* It should be NULL after destroy */
    ring_buffer_destroy(&rb);
    assert(rb == NULL);

    /* Test passed */
    printf("Congratulations! You passed the simple test!\n");
    return 0;
}
