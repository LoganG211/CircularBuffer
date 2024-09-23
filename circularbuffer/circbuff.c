#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "circbuff.h"
#include <pthread.h>

#define debug 0

int cb_is_full(cb_t *cb)
{
    if(cb->count != cb_size){
        return 0;
    } else {
        return 1;
    }
};

int cb_is_empty(cb_t *cb)
{
    if(cb->count != 0){
        return 0;
    } else {
        return 1;
    }
}

void cb_init(cb_t * cb)
{
    cb->write_idx = 0;
    cb->read_idx = 0;
    cb->count = 0;
    pthread_mutex_init(&cb->lock, 0);
};

void cb_increment(uint8_t *ptr)
{
    *ptr = (*ptr+1) % cb_size;
};

void cb_increase_count(cb_t *cb)
{
    cb->count = cb->count + 1;
}

void cb_decrease_count(cb_t *cb)
{
    cb->count = cb->count - 1;
}

// Inserts an element with given value into the buffer
int cb_push(cb_t *cb, uint32_t val)
{
    int rv;
    pthread_mutex_lock(&cb->lock);
    if( !cb_is_full(cb) ) { // if there is available space
        if((cb->write_idx+1) % cb_size != cb->read_idx && cb->count != 0){
            cb_increment(&cb->write_idx);
            cb->Buffer[cb->write_idx] = val;
            cb_increase_count(cb);
            rv = 0;
        } else {
            cb->Buffer[cb->write_idx] = val;
            cb_increase_count(cb);
            rv = 0;
        }
#if debug
        printf("Read_idx: %d\n", cb->read_idx);
        printf("Write_idx: %d\n", cb->write_idx);
        printf("    Value: %d\n", val);
        printf("        Long Size: %d\n", (((cb->write_idx - cb->read_idx) + cb_size) % cb_size));
#endif
    } else {
        printf("There is no more space! POP to create space!\n");
        rv = 1;
    }
    pthread_mutex_unlock(&cb->lock);
    return rv;
}

// Pops the foremost element in the buffer.
int cb_pop(cb_t * cb, uint32_t * data)
{
    pthread_mutex_lock(&cb->lock);
    int rv;
    if( !cb_is_empty(cb) ) { // if there is actual value
        *data = cb->Buffer[((cb_size + (cb->read_idx)) % cb_size)];
        cb->Buffer[cb->read_idx] = 0;
        cb_increment(&cb->read_idx);
        cb_decrease_count(cb);
        rv = 0; //0 is success
    } else {
        printf("The buffer is empty!\n");
        rv = -1; //error 1 is negative output
    }
    pthread_mutex_unlock(&cb->lock);
    return rv;
}

// Removes all the elements in the circular buffer
void cb_empty(cb_t * cb)
{
    cb->read_idx = cb->write_idx;
    cb->count = 0;
}

// Prints all the elements in the circular buffer
void cb_dump(cb_t * cb)
{
    pthread_mutex_lock(&cb->lock);
    for(int i=0; i<cb->count; i++) {
        printf("%i ", cb->Buffer[((cb->read_idx+i) % cb_size)]);
    }
    printf("\n");
    pthread_mutex_unlock(&cb->lock);
}
