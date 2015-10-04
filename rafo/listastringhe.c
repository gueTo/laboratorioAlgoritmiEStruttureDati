/* 
   GESTIONE DI LISTE ORDINATE
   Funzioni per la gestione di stringhe
   da utilizzare in una lista ordinata
   Comprende funzioni di hashing, allocazione
   comparazione, stampa su output, deallocazione
   lettura da input e gestione collisioni 
   
   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com              */
 
#include "include\listastringhe.h"
#ifndef DIM
#define DIM 255
#endif

#ifndef MAX_RAND_STRING_LENGTH
#define MAX_RAND_STRING_LENGTH 15
#endif


//Calcola la funzione Hash di una stringa
//input: - void *str: la stringa da calcolare
//       - void *param: parametro inserito per specifiche e non utilizzato
//output: il codice hash della stringa
unsigned long HashStringhe(void *str, void *param)
{
  unsigned long hash;
  int i = 0;
  hash = 5381;
  //legge ogni carattere e calcola il codice della stringa
  while(((char *)str)[i] != '\0')
    hash = (hash << 5) + hash + ((char *)str)[i++];
  return hash;
}

//Alloca memoria per una stringa
//input: - void *x: la stringa da allocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: la stringa allocata
void *AllocaStringa(void *x, void *param)
{
  char *info;
  info = (char *)malloc((strlen(x)+1)*sizeof(char));
  strcpy(info, x); //creo una nuova stringa in memoria
  return info;
}


//Compara due stringhe. Utilizza la funzione strcmp
//input: - void *x: la prima stringa
//       - void *y: la seconda stringa
///      - void *param: parametro non utilizzato inserito per specifiche
//output: 0 se le stringhe sono uguali, -1 se la prima
//        è maggiore della seconda, 1 altrimenti
int ComparaStringhe(void *x, void *y, void *param)
{
  return strcmp(x, y);
}

//Stampa una stringa
//input: - FILE *fp: l'output su cui stampare
//       - void *x: la stringa da stampare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void StampaStringa(FILE *fp, void *x, void *param)
{
  fprintf(fp, "%s", (char *)x); 
}


//Gestisce le collisioni tra stringhe
//non si ammettono ripetizioni di stringhe
//e pertanto tale funzione restituirà NULL
//input: - void *str: la stringa che ha causato la collisione
//       - void *param: parametro non utilizzato
//output: il valore NULL
void *GestisciCollisioneStringa(void *str, void *param)
{
  return NULL;
}


//Dealloca una stringa
//input: - void *x: la stringa da deallocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void DeallocaStringa(void *x, void *param)
{
  free(x);
}


//Legge un input dalla tastiera
//input: - void *source: parametro non utilizzato, inserito per specifiche di funzione
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista 
void *LeggiStringaDaTastiera(void *source, void *param)
{
  char ret[DIM];
  printf("Inserisci la stringa: ");
  gets(ret);
  return AllocaStringa(ret, NULL);
}


//Legge un valore stringa da file
//input: void *fp: un puntatore al file
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista 
void *LeggiStringaDaFile(void *fp, void *param)
{
  char str[DIM];
  char *ret;
  if(fgetc(fp) != EOF) //se il file non è finito
  {
    fseek(fp, -1, SEEK_CUR); //fa tornare indietro il puntatore
    fscanf(fp, "%s", str); //effettua la lettura di una stringa
    ret = AllocaStringa(str, NULL); //e la alloca
  }
  else
    ret = NULL;
  return  ret;
}


//Restituisce valori pseudocasuali
//input: - void *param1: parametro non utilizzato, inserito per specifiche di funzione
//       - void *param2: parametro non utilizzato inserito per specifiche
//output: un puntatore ad un dato da inserire nella lista
void *LeggiStringaCasuale(void *param1, void *param2)
{
  int n, i;
  char ret[MAX_RAND_STRING_LENGTH+1];
  n = rand() %MAX_RAND_STRING_LENGTH; //creo la lunghezza della stringa
  ret[0] = 65 + (rand() % 26); //la prima lettera è maiuscola
  for(i = 1; i <= n; i++)
    ret[i] = (char)(97 + (rand() % 26)); //le altre minuscole
  ret[i] = '\0'; //metto il carattere di fine stringa
  return AllocaStringa(ret, NULL);
}

