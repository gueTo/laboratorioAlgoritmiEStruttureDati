#ifndef _FIFOSTRUCT_
#define _FIFOSTRUCT_
typedef struct fifo{
    void* el;
    struct fifo* next;
}fifo;
#endif // _FIFOSTRUCT_


fifo* enqueue(fifo*, void*);
fifo* readFifo(fifo*);
fifo* dequeue(fifo*);
