/*
██╗   ██╗███████╗██████╗         ██████╗ 
██║   ██║██╔════╝██╔══██╗        ╚════██╗
██║   ██║█████╗  ██████╔╝         █████╔╝
╚██╗ ██╔╝██╔══╝  ██╔══██╗         ╚═══██╗
 ╚████╔╝ ███████╗██║  ██║        ██████╔╝
  ╚═══╝  ╚══════╝╚═╝  ╚═╝        ╚═════╝ */

#include "ringbuffer.h" 

/*
███╗   ██╗███████╗██╗    ██╗
████╗  ██║██╔════╝██║    ██║
██╔██╗ ██║█████╗  ██║ █╗ ██║
██║╚██╗██║██╔══╝  ██║███╗██║
██║ ╚████║███████╗╚███╔███╔╝
╚═╝  ╚═══╝╚══════╝ ╚══╝╚══╝ */
/*ffh */
/* Create a new ring buffer. You should allocate memory for its content,
   initialize the read_pos, write_pos and capacity properly.
   And finally return a pointer to the new ring buffer. */
ring_buffer* ring_buffer_new() {
    /* Alloc a space for the new ring buffer */
    ring_buffer* new_buf = (ring_buffer*)malloc(sizeof(ring_buffer));
    /* Abort if malloc failed */
    if (!new_buf) exit(0);
    /* Alloc a space for the content of the buffer */
    new_buf->content = (int*)malloc(sizeof(int) * RING_BUFFER_INIT_SIZE);
    /* Abort if malloc failed */
    if (!new_buf->content){
        free(new_buf);
        exit(0); /* abort  */
    }
    /* Init the ring buffer */
    new_buf->capacity = RING_BUFFER_INIT_SIZE;
    new_buf->read_pos = 0;
    new_buf->write_pos = 0;
    /* Init complete. Return the ptr to the new ring buffer */
    return new_buf;
}

/*
██████╗ ███████╗███████╗████████╗██████╗  ██████╗ ██╗   ██╗
██╔══██╗██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗╚██╗ ██╔╝
██║  ██║█████╗  ███████╗   ██║   ██████╔╝██║   ██║ ╚████╔╝ 
██║  ██║██╔══╝  ╚════██║   ██║   ██╔══██╗██║   ██║  ╚██╔╝  
██████╔╝███████╗███████║   ██║   ██║  ██║╚██████╔╝   ██║   
╚═════╝ ╚══════╝╚══════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝    ╚═╝   */

/* Destroy the given ring buffer, free all resources you've allocated.
   Finally you should set the buffer pointer to NULL, that is why we pass
   ring_buffer** as parameter, instead of ring_buffer*. */
void ring_buffer_destroy(ring_buffer** buffer) {
    /* Check if null buffer ptr's ptr or buffer ptr passed in */
    if (!buffer || !(*buffer)) return;
    /* free buffer's content first */
    if ((*buffer)->content) free((*buffer)->content);
    /* then free the buffer itself */
    free(*buffer);
    /* finally set the buffer ptr to null */
    *buffer = NULL;
    /* done! */
    return;
}

/*
███████╗███╗   ███╗██████╗ ████████╗██╗   ██╗
██╔════╝████╗ ████║██╔══██╗╚══██╔══╝╚██╗ ██╔╝
█████╗  ██╔████╔██║██████╔╝   ██║    ╚████╔╝ 
██╔══╝  ██║╚██╔╝██║██╔═══╝    ██║     ╚██╔╝  
███████╗██║ ╚═╝ ██║██║        ██║      ██║   
╚══════╝╚═╝     ╚═╝╚═╝        ╚═╝      ╚═╝   */

/* Returns true if the given ring buffer is empty, false otherwise */
bool ring_buffer_is_empty(const ring_buffer* buffer) {
    if (!buffer) return true;  /* Check if null buffer ptr passed */
    if (buffer->read_pos == buffer->write_pos)
        return true; /* when read_pos is the same as write_pos, the buffer is empty */
    else
        return false; /* otherwise, the buffer is not empty */
}

/*
██████╗ ███████╗ █████╗ ██████╗ 
██╔══██╗██╔════╝██╔══██╗██╔══██╗
██████╔╝█████╗  ███████║██║  ██║
██╔══██╗██╔══╝  ██╔══██║██║  ██║
██║  ██║███████╗██║  ██║██████╔╝
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝ */

/* Read an element from the ring buffer (i.e., the dequeue operation), *data
   records the element popped. returns true if the operation succeeded, false
   otherwise. */
bool ring_buffer_read(ring_buffer* buffer, int* data) {
    /* check if the buffer or the data passed in is nullptr */
    if (!buffer || !data || !buffer->content) return false;
    /* check if the buffer is empty */
    if (ring_buffer_is_empty(buffer)) return false;
    /* read out the data */
    *data = buffer->content[buffer->read_pos];
    /* iterate 'read_pos' once by using mod */
    buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
    return true;
}

/*
██████╗ ███████╗ █████╗ ██████╗     ███╗   ███╗██╗   ██╗██╗     
██╔══██╗██╔════╝██╔══██╗██╔══██╗    ████╗ ████║██║   ██║██║     
██████╔╝█████╗  ███████║██║  ██║    ██╔████╔██║██║   ██║██║     
██╔══██╗██╔══╝  ██╔══██║██║  ██║    ██║╚██╔╝██║██║   ██║██║     
██║  ██║███████╗██║  ██║██████╔╝    ██║ ╚═╝ ██║╚██████╔╝███████╗
╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝     ╚═╝     ╚═╝ ╚═════╝ ╚══════╝*/

/* Read "rdsize" elements from the ring buffer, and fill them to "data".
   Notice that you should only return true when this operation succeeds.
   If there are not enough elements in the buffer, just DO NOTHING and
   return false. DO NOT modify the ring buffer and data for such cases. */
bool ring_buffer_read_multi(ring_buffer* buffer, size_t rdsize, int* data) {
    /* C89: variables declaration first */
    size_t i = 0;
    size_t element_cnt;
    /* 'buffer', 'data' nullptr check, 'rdsize=0' check, and buffer-is-empty check */
    if (!buffer || !rdsize || !data || ring_buffer_is_empty(buffer)) return false;
    /* calculate the buffer's size (how many elements stored?) */
    element_cnt = (buffer->write_pos - buffer->read_pos + buffer->capacity) % buffer->capacity;
    /* Check if there are enough elements? */
    if (rdsize > element_cnt) return false;  /* not enough elements */
    /* There are enough elements. Read out */
    while (rdsize) {
        /* read the content and store */
        data[i] = buffer->content[buffer->read_pos];
        /* iterate 'read_pos' once by using mod */
        buffer->read_pos = (buffer->read_pos + 1) % buffer->capacity;
        i++;
        rdsize--;
    }
    return true;
}

/*
██╗    ██╗██████╗ ██╗████████╗███████╗
██║    ██║██╔══██╗██║╚══██╔══╝██╔════╝
██║ █╗ ██║██████╔╝██║   ██║   █████╗  
██║███╗██║██╔══██╗██║   ██║   ██╔══╝  
╚███╔███╔╝██║  ██║██║   ██║   ███████╗
 ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝ */

/* Write an element which value is `data` to the ring buffer (i.e., the enqueue
   operation), returns true if the operation succeeded, false otherwise. Note
   that when the buffer is full, grow its size to make sure the element can be
   write successfully. The detailed requirements of size growth are in the
   homework description. */
bool ring_buffer_write(ring_buffer* buffer, const int data) {
    /* C89: variables declaration first */
    size_t element_cnt;
    /* buffer nullptr check */
    if (!buffer) return false;
    /* calculate the buffer's size */
    element_cnt = (buffer->write_pos - buffer->read_pos + buffer->capacity) % buffer->capacity;
    if (element_cnt == buffer->capacity - 1) { /* ring buffer is full */ /* expand capacity */
        /* C89: variables declaration first */
        size_t i, new_capacity;
        int* new_content;
        /* calculate the new capacity according to current capacity */
        new_capacity = buffer->capacity * ((buffer->capacity < 1024)? RING_BUFFER_GROW_FACTOR1:RING_BUFFER_GROW_FACTOR2);
        /* malloc a new content */
        new_content = (int*) malloc(sizeof(int) * new_capacity);
        /* Abort if malloc failed */
        if (!new_content) return false;
        /* copy data */
        i = 0;
        while (!ring_buffer_is_empty(buffer)){
            ring_buffer_read(buffer, &new_content[i]);
            i++; 
        }
        /* free the old buffer content */	
        free(buffer->content);
        /* update buffer properties */
        buffer->content = new_content;
        buffer->capacity = new_capacity;
        buffer->read_pos = 0;
        buffer->write_pos = element_cnt;
    }
    /* capacity already expanded if full. Now we have sufficient capacity. */
    /* write the data */
    buffer->content[buffer->write_pos] = data;
    /* iterate 'write_pos' once */
    buffer->write_pos = (buffer->write_pos + 1) % buffer->capacity;
    /* write complete, return */
    return true;
}

/*
██╗    ██╗██████╗ ██╗████████╗███████╗    ███╗   ███╗██╗   ██╗██╗     
██║    ██║██╔══██╗██║╚══██╔══╝██╔════╝    ████╗ ████║██║   ██║██║     
██║ █╗ ██║██████╔╝██║   ██║   █████╗      ██╔████╔██║██║   ██║██║     
██║███╗██║██╔══██╗██║   ██║   ██╔══╝      ██║╚██╔╝██║██║   ██║██║     
╚███╔███╔╝██║  ██║██║   ██║   ███████╗    ██║ ╚═╝ ██║╚██████╔╝███████╗
 ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝    ╚═╝     ╚═╝ ╚═════╝ ╚══════╝*/

/* Write "wrtsize" elements to the ring buffer. The values to write are
   provided in "data". Returns true if succeeds, false otherwise. Don't
   forget to grow your buffer size properly. */
bool ring_buffer_write_multi(ring_buffer* buffer, size_t wrtsize, const int* data) {
    /* buffer, data nullptr check, and wrtsize=0 check */
    if (!buffer || !data || !wrtsize) return false;
    else {
        /* C89: variables declaration first */
        size_t i = 0;
        /* use a for-loop to write all the data */
        for (; i < wrtsize; i++) 
            ring_buffer_write(buffer, data[i]);
        return true;
    }
}

/*
███╗   ███╗ █████╗ ██████╗ 
████╗ ████║██╔══██╗██╔══██╗
██╔████╔██║███████║██████╔╝
██║╚██╔╝██║██╔══██║██╔═══╝ 
██║ ╚═╝ ██║██║  ██║██║     
╚═╝     ╚═╝╚═╝  ╚═╝╚═╝     */

/* For every element in the ring buffer, apply "func" to it. For example,
   Your buffer currently contains 3 elements 1, 2, 4. If the map function is to
   "add five", then their values should be 6, 7, 9 after calling this function.
 */
bool ring_buffer_map(ring_buffer* buffer, map_func func) {
    /* buffer ptr and function ptr NULLPTR check */
    if (!buffer || !func) return false;
    else {
        /* start iteration from read_pos */
        size_t iter = buffer->read_pos;
        /* continue iterating until reaching write_pos (end) */
        while (iter != buffer->write_pos) {
            /* apply map function */
            buffer->content[iter] = func(buffer->content[iter]);
            /* iterate */
            iter = (iter + 1) % buffer->capacity;
        }
        /* operation complete, return true */
        return true;
    }
}

