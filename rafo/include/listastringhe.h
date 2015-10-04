/* 
   GESTIONE DI LISTE ORDINATE
   Prototipi e definizioni per la gestione
   di stringhe da utilizzare in una lista ordinata
   Comprende funzioni di hashing, allocazione
   comparazione, stampa su output, deallocazione
   lettura da input e gestione collisioni 
   
   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com              */
#include <stdio.h>

#ifndef MAX_LENGTH
#define MAX_LENGTH 15
#endif 
 
 
//Calcola la funzione Hash di una stringa
//input: - void *str: la stringa da calcolare
//       - void *param: parametro inserito per specifiche e non utilizzato
//output: il codice hash della stringa
unsigned long HashStringhe(void *str, void *param);


//Alloca memoria per una stringa
//input: - void *x: la stringa da allocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: la stringa allocata
void *AllocaStringa(void *x, void *param);

//Compara due stringhe. Utilizza la funzione strcmp
//input: - void *x: la prima stringa
//       - void *y: la seconda stringa
///      - void *param: parametro non utilizzato inserito per specifiche
//output: 0 se le stringhe sono uguali, -1 se la prima
//        è maggiore della seconda, 1 altrimenti
int ComparaStringhe(void *x, void *y, void *param);

//Stampa una stringa
//input: - FILE *fp: l'output su cui stampare
//       - void *x: la stringa da stampare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void StampaStringa(FILE *fp, void *x, void *param);

//Gestisce le collisioni tra stringhe
//non si ammettono ripetizioni di stringhe
//e pertanto tale funzione restituirà NULL
//input: - void *str: la stringa che ha causato la collisione
//       - void *param: parametro non utilizzato
//output: il valore NULL
void *GestisciCollisioneStringa(void *str, void *param);

//Dealloca una stringa
//input: - void *x: la stringa da deallocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void DeallocaStringa(void *x, void *param);

//Legge un input dalla tastiera
//input: - void *source: parametro non utilizzato, inserito per specifiche di funzione
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista 
void *LeggiStringaDaTastiera(void *source, void *param);

//Legge un valore stringa da file
//input: void *fp: un puntatore al file
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista 
void *LeggiStringaDaFile(void *fp, void *param);

//Restituisce valori pseudocasuali
//input: - void *param1: parametro non utilizzato, inserito per specifiche di funzione
//       - void *param2: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista
void *LeggiStringaCasuale(void *param1, void *param2);
