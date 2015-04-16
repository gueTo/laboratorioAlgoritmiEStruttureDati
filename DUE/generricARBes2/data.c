/********LIBRERIA GESTIONE VARIABILI*********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***DICHIARAZIONE FUNZIONI***/

#define STRING_MAX_SIZE 10

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
void* copyString();
void* copyInteger();
void* copyFloat();


int main(){
    void* i=insertFloat();
    void* j;
    j=copyFloat(j, i);
    free(i);
    printf("\n");
    i=insertFloat();
    printFloat(j);
    return 0;
}


/***
FUNZIONI DI INSERIMENTO
***/
//LEGGE DA INPUT UN CARATTERE ALLA VOLTA, ALLOCA UNA STRINGA DI GRANDEZZA ADATTA
//E LA RIEMPIE CON I CARATTERI INSERITI. IN SEGUITO LA RESTITUISCE
void* insertString(){
	char stringa[100];
	char* ret;
	int i=-1;
	do{
		i++;
		stringa[i]=getchar();
	}while(stringa[i]!='\n' && i<99);
	stringa[i]='\0';
	ret=(char*)malloc(strlen(stringa)*sizeof(char));
	strcpy(ret, stringa);
	return ret;
}

//LEGGE UN INTERO CHIAMANDO LA LETTURA DI CARATTERI DA TASTIERA, QUINDI COME UNA
//STRINGA DI CARATTERI NUMERICI, POI LA CONVERTE IN UN INTERO ALLOCATO DINAMICAMENTE CHE RESTITUISCE
void* insertInteger(){
    char* string=insertString();
    void* elem=(int*)malloc(sizeof(int));
    elem=(void*)(atoi(string));
    free(string);
    return elem;
};


//LEGGE UN FLOAT CHIAMANDO LA LETTURA DI CARATTERI DA TASTIERA, QUINDI COME UNA
//STRINGA DI CARATTERI NUMERICI, POI LA CONVERTE IN UN FLOAT ALLOCATO DINAMICAMENTE CHE RESTITUISCE
void* insertFloat(){
    char* string=insertString();
    void* elem=(float*)malloc(sizeof(int));
    *(float*)elem=atof((char*)string);
    free(string);
    return elem;
};


/***
FUNZIONI RANDOMICHE
***/
void* casualString(){
    srand(time(NULL));
 	char character;
	int lenght=0;
	int i=-1;
	lenght=(rand()%STRING_MAX_SIZE)+2;
	char *string;
	string=(char*)malloc(lenght*sizeof(char));
	do{
		i++;
		character=(rand()%26)+97;
		string[i]=character;
	}while(i<lenght-1);
	string[lenght-1]='\0';
	return string;
}

void* casualInteger(){
    srand(time(NULL));
    void* retInt=(int*)malloc(sizeof(int));
    retInt=(rand()%100);
    return retInt;
}

void* casualFloat(){
    srand(time(NULL));
    float a = 1.55;
    void* retFlo=(float*)malloc(sizeof(float));
    *(float*)retFlo=(((float)rand()/(float)(RAND_MAX))*(float)(rand()))/(111.11);
    return retFlo;
}

/***
FUNZIONI DI STAMPA
***/
void printInteger(void* toPrint){
    printf("%d", ((int*)(toPrint)));
}

void printFloat(void* toPrint){
    printf("%f", *(float*)(toPrint));
}

void printString(void* toPrint){
    printf("%s", (char*)(toPrint));
}


/***
FUNZIONI PER IL CONFRONTO

PREVEDONO L'INPUT DI DUE PUNTATORI A VOID CHE SUBISCONO UN CAST VERSO IL TIPO PREVISTO
IN SEGUITO CONFRONTANO I DUE INPUT
***/
int compareInteger(void* a, void* b){
    if((((int*)a))==(((int*)b)))
        return 0;
    if((((int*)a))<(((int*)b)))
        return -1;
    return 1;
}

int compareFloat(void* a, void* b){
    if((*((float*)a))==(*((float*)b)))
        return 0;
    if((*((float*)a))<(*((float*)b)))
        return -1;
    return 1;
}

int compareString(void* a, void* b){
    return (strcmp((char*)a, (char*)b));
}


/***
FUNZIONI PER LA DEALLOCAZIONE
***/
void deleteString(void* string){
    free(string);
}

void deleteInteger(void* n){
    free(n);
}

void deleteFloat(void* f){
    free(f);
}

void* copyString(void* cop, void* original){
    cop=(char*)malloc(sizeof(char)*strlen(original));
    strcpy((char*)cop, (char*)original);
    return cop;
}

void* copyInteger(void* cop, void* original){
    cop=(int*)malloc(sizeof(int));
    cop=(int*)(original);
    return cop;
}

void* copyFloat(void* cop, void* original){
    cop=(float*)malloc(sizeof(float));
    (*(float*)cop)=*((float*)(original));
    return cop;
}
