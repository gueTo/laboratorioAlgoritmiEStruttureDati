typedef struct lifoType{
    void* element;
    struct lifoType* next;
}lifo;

lifo* lifoPush(lifo*, void*);
lifo* lifoTop(lifo*);
int lifoIsEmpty(lifo*);
lifo* lifoPop(lifo*);
lifo* deleteLifo(lifo*);
