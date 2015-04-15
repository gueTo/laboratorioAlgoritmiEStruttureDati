
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "es1.h"



int menu();
void printMenu();
void* insertString();
ARB* insertNewARB(ARB*);
ARB** creaNuovoAlbero(ARB**, int);
void stampaAlbero(ARB**,int);
ARB** inserisciNuovaStringa(ARB**, int );
ARB** cancellazioneAlbero(ARB**, int);
ARB** cancellazioneStringa(ARB**, int);
ARB** cancellazioneCondizionataStringa(ARB**, int);
ARB** generaAlberoCasuale(ARB**, int);
ARB** duplicaAlbero(ARB**, int);
void verificaIdentici(ARB** , int);
ARB** creaAlberoBilanciato(ARB**, int);
void deallocaTutto(ARB**, int);


int main(){
    ARB** prova;
    int howMany;
    int nMenu;
//    int count;
    int i=0;
    do{
        printf("Quanti alberi si intende inserire?\n");
        scanf("%d", &howMany);
        getchar();
    }while(howMany<1);
    prova=(ARB**)malloc(howMany*sizeof(ARB*));
    for(i=0; i<howMany; i++){
        prova[i]=NULL;
    }
    do{
        nMenu=menu();
        switch(nMenu){
            case 1:
                prova=creaNuovoAlbero(prova, howMany);
                break;
            case 2:
                prova=inserisciNuovaStringa(prova, howMany);
                break;
            case 3:
                stampaAlbero(prova, howMany);
                break;
            case 4:
                prova=cancellazioneAlbero(prova, howMany);
                break;
            case 5:
                prova=cancellazioneStringa(prova, howMany);
                break;
            case 6:
                prova=cancellazioneCondizionataStringa(prova, howMany);
                break;
            case 7:
                prova=generaAlberoCasuale(prova, howMany);
                break;
            case 8:
                prova=duplicaAlbero(prova, howMany);
                break;
            case 9:
                verificaIdentici(prova, howMany);
                break;
            case 10:
                prova=creaAlberoBilanciato(prova, howMany);
                break;
        }
    }while(nMenu!=0);
    deallocaTutto(prova, howMany);
    return 0;
}

int menu(){
    int choiche=0;
    printMenu();
    do{
        if(choiche<0 || choiche>10)
            printf("\ninserito numero non ammesso\nPrego reinserire\n");
        scanf("%d", &choiche);
        getchar();
    }while(choiche<0 || choiche>10);
    return choiche;
}


void printMenu(){
    printf("\n1. Crea un nuovo albero\n");
    printf("2. inserimento di una stringa in un ARB\n");
    printf("3. stampa di un ARB\n");
    printf("4. cancellazione di in un ARB\n");
    printf("5. cancellazione di una stringa da un ARB\n");
    printf("6. cancellazione da un ARB di tutte le stringhe che soddisfano una condizione\n");
    printf("7. costruzione di un ARB contenente un numero n di stringhe casualmente generate\n");
    printf("8. duplicazione di un ARB dato\n");
    printf("9. verifica se due ARB dati sono identici (hanno le stesse chiavi e la stessa forma)\n");
    printf("10. costruzione di un ARB perfettamente bilanciato a partire da un altro ARB\n");
    printf("0. esci\n\n");
}

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

ARB* insertNewARB(ARB* newARB){
    char* toInsert;
    int again=0;
    printf("\nInserire la stringa da immettere\n");
    do{
        toInsert=insertString();
        newARB=insertARBNode(newARB, toInsert);
        printf("Inserire un'altra stringa?\n0)No\n1)Si\n");
        scanf("%d", &again);
        getchar();
    }while(again);
    return newARB;
}

ARB** creaNuovoAlbero(ARB** vARB, int size){
    int count=0;
    while(count<size && vARB[count]!=NULL){
        count++;
    }
    if(count<size){
        vARB[count]=insertNewARB(vARB[count]);
        printf("\nAlbero creato nella posizione %d\n", count);
    }else{
        printf("Impossibile aggiungere nuovi alberi");
    }
    return vARB;
}

void stampaAlbero(ARB** vARB, int size){
    int which;
    printf("\nQuale albero vuoi stampare? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    if(which<size && which>-1){
        printARB(vARB[which]);
    }else{
        printf("\nE' impossibile stampare l'albero richiesto\n");
    }
}

ARB** inserisciNuovaStringa(ARB** vARB, int size){
    int which;
    char* strIns;
    printf("\nIn che albero vuoi inserire la stringa? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    getchar();
    if(which<size && which>-1){
        strIns=insertString();
        vARB[which]=insertARBNode(vARB[which], strIns);
    }else{
        printf("\nE' impossibile aggiungere una stringa all'albero richiesto\n");
    }
    return vARB;
}

ARB** cancellazioneAlbero(ARB** vARB, int size){
    int which;
    printf("\nIn che albero vuoi inserire la stringa? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    if(which<size && which>-1){
        vARB[which]=deleteAllKey(vARB[which]);
        vARB[which]=NULL;
    }else{
        printf("\nE' impossibile cancellare l'albero richiesto\n");
    }
    return vARB;
}

ARB** cancellazioneStringa(ARB** vARB, int size){
    int which;
    char* strIns;
    printf("\nDa quale albero vuoi cancellare la stringa? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    getchar();
    if(which<size && which>-1){
        printf("Inserire stringa che si vuole cancellare: ");
        strIns=insertString();
        vARB[which]=searchStringAndDelete(vARB[which], strIns);
    }else{
        printf("\nE' impossibile aggiungere una stringa all'albero richiesto\n");
    }
    return vARB;
}


ARB** cancellazioneCondizionataStringa(ARB** vARB, int size){
    int which;
    int odd;
    char* strIns, *strIns2;
    printf("\nDa quale albero vuoi cancellare la stringhe? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    getchar();
    if(which<size && which>-1){
        printf("\nInserire gli estremi dell'intervallo: ");
        strIns=insertString();
        strIns2=insertString();
        printf("\nCancellare\n0)pari\n1)dispari\n");
        scanf("%d", &odd);
        vARB[which]=searchConditionAndDeleteARB(vARB[which], strIns, strIns2, odd);
    }else{
        printf("\nE' impossibile cancellare dall'albero richiesto\n");
    }
    return vARB;
}

ARB** generaAlberoCasuale(ARB** vARB, int size){
    int count=0;
    int numStr;
    while(count<size && vARB[count]!=NULL){
        count++;
    }
    if(count<size){
        printf("Di quanti elementi è composto quest'albero? ");
        scanf("%d", &numStr);
        vARB[count]=casualARB(vARB[count], numStr);
    }else{
        printf("Impossibile aggiungere nuovi alberi");
    }
    return vARB;
}

ARB** duplicaAlbero(ARB** vARB, int size){
    int which;
    int count=0;
    printf("\nQuale albero vuoi duplicare? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    if(which<size && which>-1){
        while(count<size && vARB[count]!=NULL){
            count++;
        }
        if(count<size){
            vARB[count]=duplicateARB(vARB[which]);
            printf("\nAlbero duplicato nella posizione %d\n", count);
        }else{
            printf("Impossibile aggiungere nuovi alberi\n");
        }
    }else{
        printf("\nE' impossibile duplicare l'albero richiesto\n");
    }
    return vARB;
}

void verificaIdentici(ARB** vARB, int size){
    int whichOne, whichTwo;
    printf("Quali alberi si vogliono confrontare? ");
    scanf("%d", &whichOne);
    scanf("%d", &whichTwo);
    if(whichOne<size-1 && whichTwo<size-1){
        if(controlSameARB(vARB[whichOne], vARB[whichTwo])==1){
            printf("I due alberi sono identici\n");
        }else printf("I due alberi sono diversi\n");
    }else printf("Impossibile confrontare gli alberi richiesti\n");
}


ARB** creaAlberoBilanciato(ARB** vARB, int size){
    int which;
    int count=0;
    printf("\nQuale albero vuoi bilanciare? (da 0 a %d) ", size-1);
    scanf("%d", &which);
    if(which<size && which>-1){
        while(count<size && vARB[count]!=NULL){
            count++;
        }
        if(count<size){
            vARB[count]=balanceARB(vARB[which]);
            printf("\nAlbero creato nella posizione %d\n", count);
        }else{
            printf("Impossibile aggiungere nuovi alberi\n");
        }
    }else{
        printf("\nE' impossibile bilanciare l'albero richiesto\n");
    }
    return vARB;
}


void deallocaTutto(ARB** vARB, int size){
    int i;
    for(i=0; i<size; i++){
        vARB[i]=deleteAllKey(vARB[i]);
        vARB[i]=NULL;
    }
    free(vARB);
}
