#include <stdlib.h>
#include <string.h>
#ifndef _LISTSTRING_H_
    #define _LISTSTRING_H_
    #include "listString.h"
#endif // _LISTSTRING_H_

/*****/


unsigned long HashStringhe(void *str, void *param){
    unsigned long hash;
    int i = 0;
    hash = 5381;
    //legge ogni carattere e calcola il codice della stringa
    while(((char *)str)[i] != '\0')
        hash = (hash << 5) + hash + ((char *)str)[i++];
    return hash;
}

void *AllocaStringa(void *x, void *param){
    char *info;
    info = (char *)malloc((strlen(x)+1)*sizeof(char));
    strcpy(info, x); //creo una nuova stringa in memoria
    return info;
}


int ComparaStringhe(void *x, void *y, void *param){
    return strcmp(x, y);
}


void StampaStringa(FILE *fp, void *x, void *param){
    fprintf(fp, "%s", (char *)x);
}

void *GestisciCollisioneStringa(void *str, void *param){
    return NULL;
}

void DeallocaStringa(void *x, void *param){
    free(x);
}

void *LeggiStringaDaTastiera(void *source, void *param){
    char ret[DIM_STRING];
    printf("Inserisci la stringa: ");
    gets(ret);
    return AllocaStringa(ret, NULL);
}

void *LeggiStringaDaFile(void *fp, void *param){
    char str[DIM_STRING];
    char *ret;
    if(fgetc(fp) != EOF){
        fseek(fp, -1, SEEK_CUR); //fa tornare indietro il puntatore
        fscanf(fp, "%s", str); //effettua la lettura di una stringa
        ret = AllocaStringa(str, NULL); //e la alloca
    }else ret = NULL;
    return  ret;
}


void *LeggiStringaCasuale(void *param1, void *param2){
    int n, i;
    char ret[MAX_RAND_STRING_LENGTH+1];
    n = rand() %MAX_RAND_STRING_LENGTH; //creo la lunghezza della stringa
    ret[0] = 65 + (rand() % 26); //la prima lettera è maiuscola
    for(i = 1; i <= n; i++)
        ret[i] = (char)(97 + (rand() % 26)); //le altre minuscole
    ret[i] = '\0'; //metto il carattere di fine stringa
    return AllocaStringa(ret, NULL);
}
