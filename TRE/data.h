/***DICHIARAZIONE FUNZIONI***/

#ifndef STRING_MAX_SIZE

    #define STRING_MAX_SIZE 10

#endif // STRING_MAX_SIZE

void* insertString();
void* insertInteger();
void* insertFloat();
void printInteger(void*);
void printFloat(void*);
void printString(void*);
int compareInteger(void*, void*);
int compareFloat(void*, void*);
int compareString(void*, void*);
void deleteString(void*);
void deleteInteger(void*);
void deleteFloat(void*);
void* casualInteger();
void* casualFloat();
void* casualString();
void* copyString(void*, void*);
void* copyInteger(void*, void*);
void* copyFloat(void*, void*);
int oddInteger(void*, int);
int oddFloat(void*, int);
int oddString(void*, int);
