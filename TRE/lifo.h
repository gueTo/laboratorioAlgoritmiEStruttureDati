#ifndef _LIFO_STRUCT_
    #define _LIFO_STRUCT_

typedef struct lifoType{
    void* element;
    struct lifoType* next;
}lifo;

#endif // _LIFO_LIFO_STRUCT_

lifo* lifoPush(lifo*, void*);
lifo* lifoTop(lifo*);
int lifoIsEmpty(lifo*);
lifo* lifoPop(lifo*);
lifo* deleteLifo(lifo*);
