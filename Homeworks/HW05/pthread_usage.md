## Basic usage of 'pthread'

### Header files 

```C
#include <pthread.h>
```

### Create threads

You can think of each thread as a running function. You pass arguments to the thread, and the thread returns something after it runs. The argument passed into the thread MUST BE `void *`. Therefore, you may need to use a `struct *` and convert it to `void *`.

Create a thread with `pthread_t` type and `pthread_create` function, which takes in the `pthread_t` value, a function pointer, and some others.

Join a thread with `pthread_join` function.

### Example

```C
typedef struct {
    int arg1;
    int arg2;
} Args_struct;


void *thread_func(void *arg){
    
    // How to receive arguments in child threads?
    int arg1 = ((Args_struct*)arg)->arg1;
    int arg2 = ((Args_struct*)arg)->arg2;
    
    // Do something in this child thread
    print("Hello\n");

    // return 
    return NULL;
} 

int main(){
    // How to create a thread?
    pthread_t th;
    Args_struct a = {1, 2, NULL};
    pthread_create(&th, NULL, func, (void*) &a);

    pthread_join(th, NULL);
    return 0;
}
```