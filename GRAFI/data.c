#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"


#ifndef _GEST_FUNCTDATA_
#define _GEST_FUNCTDATA_
FUNCTDATA *initFUNCTDATA(FUNINS ins, FUNCPY cpy, FUNRAND ran, FUNCOM com, FUNODD odd, FUNHASH has, FUNCOLLISION coll, FUNPRINT prin, FUNDEL fre){
    FUNCTDATA* ret=(FUNCTDATA*)malloc(sizeof(FUNCTDATA));
	ret->fins=ins;
	ret->fcopy=cpy;
   	ret->frand=ran;
   	ret->fcomp=com;
   	ret->fhas=has;
   	ret->fcoll=coll;
   	ret->fodd=odd;
   	ret->fpri=prin;
   	ret->funfree=fre;
    return ret;
}

FUNCTDATA* deleteFUNCTDATA(FUNCTDATA* toDel){
    free(toDel);
    return NULL;
}

#endif // _GEST_FUNCTDATA_

/***
DEFINIZIONE FUNZIONI PER TIPO DI VARIABILE
***/



/***
FUNZIONI DI INSERIMENTO
***/
//LEGGE DA INPUT UN CARATTERE ALLA VOLTA, ALLOCA UNA STRINGA DI GRANDEZZA ADATTA
//E LA RIEMPIE CON I CARATTERI INSERITI. IN SEGUITO LA RESTITUISCE
void* insertString(void* parameter){
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
void* insertInteger(void* parameter){
    char* string=insertString(parameter);
    void* elem=(int*)malloc(sizeof(int));
    *(int*)elem=atoi((char*)string);
    free(string);
    return elem;
};


//LEGGE UN FLOAT CHIAMANDO LA LETTURA DI CARATTERI DA TASTIERA, QUINDI COME UNA
//STRINGA DI CARATTERI NUMERICI, POI LA CONVERTE IN UN FLOAT ALLOCATO DINAMICAMENTE CHE RESTITUISCE
void* insertFloat(void* parameter){
    char* string=insertString(parameter);
    void* elem=(float*)malloc(sizeof(int));
    *(float*)elem=atof((char*)string);
    free(string);
    return elem;
};


/***
FUNZIONI RANDOMICHE
***/
void* casualString(void* parameter){
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

void* casualInteger(void* parameter){
    srand(time(NULL));
    void* retInt=(int*)malloc(sizeof(int));
    *(int*)retInt=(rand()%100);
    return retInt;
}

void* casualFloat(void* parameter){
    srand(time(NULL));
    void* retFlo=(float*)malloc(sizeof(float));
    *(float*)retFlo=(((float)rand()/(float)(RAND_MAX))*(float)(rand()))/(111.11);
    return retFlo;
}

/***
FUNZIONI DI STAMPA
***/

void printInteger(FILE* fp, void* toPrint, void* parameter){
    fprintf(fp, "%d", *(int*)(toPrint));
}

void printFloat(FILE* fp, void* toPrint, void* parameter){
    fprintf(fp, "%f", *(float*)(toPrint));
}

void printString(FILE* fp, void* toPrint, void* parameter){
    fprintf(fp, "%s", (char*)(toPrint));
}


/***
FUNZIONI PER IL CONFRONTO

PREVEDONO L'INPUT DI DUE PUNTATORI A VOID CHE SUBISCONO UN CAST VERSO IL TIPO PREVISTO
IN SEGUITO CONFRONTANO I DUE INPUT
***/
int compareInteger(void* a, void* b, void* parameter){
    if((*((int*)a))==(*((int*)b)))
        return 0;
    if((*((int*)a))<(*((int*)b)))
        return -1;
    return 1;
}

int compareFloat(void* a, void* b, void* parameter){
    if((*((float*)a))==(*((float*)b)))
        return 0;
    if((*((float*)a))<(*((float*)b)))
        return -1;
    return 1;
}

int compareString(void* a, void* b, void* parameter){
    int m=(strcmp((char*)a, (char*)b));
    return m;
}


/***
FUNZIONI PER LA DEALLOCAZIONE
***/
void* deleteString(void* string, void* parameter){
    free(string);
    return NULL;
}

void* deleteInteger(void* n, void* parameter){
    free(n);
    return NULL;
}

void* deleteFloat(void* f, void* parameter){
    free(f);
    return NULL;
}

void* copyString(void* cop, void* original, void* parameter){
    cop=(char*)malloc(sizeof(char)*(strlen(original)+1));
    strcpy((char*)cop, (char*)original);
    return cop;
}

void* copyInteger(void* cop, void* original, void* parameter){
    cop=(int*)malloc(sizeof(int));
    (*(int*)cop)=*((int*)(original));
    return cop;
}

void* copyFloat(void* cop, void* original, void* parameter){
    cop=(float*)malloc(sizeof(float));
    (*(float*)cop)=*((float*)(original));
    return cop;
}


int oddInteger(void* isOdd, int odd, void* parameter){
    return(((*(int*)isOdd)%2)==odd);
}

int oddFloat(void* isOdd, int odd, void* parameter){
    return((((int)((*(float*)isOdd)))%2)==odd);
}

int oddString(void* isOdd, int odd, void* parameter){
    return((strlen((char*)isOdd)%2)==odd);
}




void* collisionString(void* toCollide){
    return NULL;
}


unsigned long int hashingString(void *toHash, void *parameter){{
    unsigned long hash = 5381;
    char* str=(char*)toHash;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
}

unsigned long int hashingInteger(void *toHash, void *parameter){
    return *(unsigned long int*)toHash;
}

void* collisionInteger(void* toCollide){
    return NULL;
}
