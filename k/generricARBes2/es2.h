/***DICHIARAZIONI***/
typedef void*(*FUNINS)();
typedef int(* FUNCOM)(void*, void*);
typedef void(* FUNPRINT)(void*);
typedef void(*FUNDEL)(void*);
typedef void*(*FUNRAND)();
typedef void*(*FUNCPY)(void*, void*);
typedef int(FUNODD)(void*, int);

typedef struct ARBType{
    void* element;
    struct ARBType* sx;
    struct ARBType* dx;
}ARB;

