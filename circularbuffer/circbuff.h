#ifndef CIRCBUFF_H
#define CIRCBUFF_H

#define cb_size 8

// Contains references to all the different functions of a circular buffer here

//Contains the data of the buffer
typedef struct {
    uint32_t Buffer[cb_size];
    uint8_t write_idx, read_idx;
    pthread_mutex_t lock;
    uint8_t count;
} cb_t;
int cb_is_full(cb_t *cb);
int cb_is_empty(cb_t *cb);
void cb_init(cb_t * cb);
int cb_push(cb_t *cb, uint32_t val);
int cb_pop(cb_t * cb, uint32_t * data);
void cb_empty(cb_t * cb);
void cb_dump(cb_t * cb);

#endif

//git repo
//pop_thread