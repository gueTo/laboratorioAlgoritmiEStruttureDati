/*  
  GESTIONE DI UNA HASH TABLE CONCATENATA
  Funzioni per la gestione di una tabella hash
  con metodo di risoluzione delle collisioni
  tramite lista
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "include\TabellaHash.h"

//Inizializza la tabella hash
//input: - unsigned int dimensione: la dimensione della tabella
//       - OPERAZIONI *funzioniLista: le funzioni utilizzate dalle liste
//       - unsigned long (*funzioneHash)(void *): la funzione di hashing
//output: la tabella hash inizializzata
HASH_TABLE InizializzaTabella(unsigned int dimensione, OPERAZIONI *funzioniLista)
{
  int i;
  HASH_TABLE tabellaHash;
  //inizializzo tutti i campi della struttura e la ritorno
  tabellaHash.dimensione = dimensione;
  tabellaHash.funzioniLista = funzioniLista;
  tabellaHash.tabella = (LIST *)malloc(dimensione*sizeof(LIST));
  for(i = 0; i < dimensione; i++)
    tabellaHash.tabella[i] = InizializzaLista();
  return tabellaHash;
}


//Inserisce un elemento nella tabella hash
//input: - HASH_TABLE tabellaHash: la tabella in cui inserire
//       - void *key: l'elemento da inserire nella tabella
//       - void *param: altri parametri per la gestione
//output: la tabella modificata
HASH_TABLE InserisciElementoTabella(HASH_TABLE tabellaHash, void *key, void *param)
{
  //calcolo l'indice in cui andrà inserito l'elemento
  int indice = (tabellaHash.funzioniLista)->FunzioneHash(key, param) % tabellaHash.dimensione;
  //aggiungo l'elemento alla lista dell'elemento rispettivo della tabella
  tabellaHash.tabella[indice] = InserisciInLista(tabellaHash.tabella[indice], *tabellaHash.funzioniLista, 
                                                  AllocaNodo(key), param);
  return tabellaHash;
}


//Cerca un elemento nella tabella hash
//input: - HASH_TABLE tabellaHash: la tabella in cui cercare
//       - void *key: la chiave dell'elemento da ricercare
//       - void *param: altri parametri per la gestione
//output: un puntatore all'elemento della tabella
void *CercaNellaTabella(HASH_TABLE tabellaHash, void *key, void *param)
{
  void *ret;
  //calcolo l'indice in cui andrà cercato l'elemento
  int indice = (tabellaHash.funzioniLista)->FunzioneHash(key, param) % tabellaHash.dimensione;
  
  //cerco l'elemento ed aggiorno il valore di ritorno
  ret = CercaNellaLista(tabellaHash.tabella[indice], *tabellaHash.funzioniLista, key, param);
  
  return ret;
}


//Cancella un elemento dalla tabella
//input: - HASH_TABLE tabellaHash: la tabella nella quale cancellare
//       - void *key: l'elemento da cancellare dalla tabella
//       - void *param: altri parametri per la gestione
//output: nessuno
void CancellaDallaTabella(HASH_TABLE tabellaHash, void *key, void *param)
{
  int indice;
   //calcolo l'indice in cui andrà cercato l'elemento
  indice = (tabellaHash.funzioniLista)->FunzioneHash(key, param) % tabellaHash.dimensione;
  //rimuovo l'elemento dalla lista relativa
  tabellaHash.tabella[indice] = CancellaDallaLista(tabellaHash.tabella[indice], *tabellaHash.funzioniLista, 
                                                  key, param);
}


//Stampa la tabella
//input: - FILE *fp: l'output su cui stampare
//       - HASH_TABLE tabellaHash: la tabella da stampare
//       - void *param: altri parametri per la gestione
//output: nessuno
void StampaTabella(FILE *fp, HASH_TABLE tabellaHash, void *param)
{
  int i;
  //di ogni lista stampo il contenuto
  for(i = 0; i < tabellaHash.dimensione; i++)
    if(tabellaHash.tabella[i] != NULL)
    {
      fprintf(fp, "Codice %d: ", i);
      StampaLista(fp, tabellaHash.tabella[i], *tabellaHash.funzioniLista, param);
    }
}

//Ottimizza la tabella hash ricostruendo la tabella per ridurre
//il livello di collisione medio dei dati
//input: - HASH_TABLE tabellaHash: la tabella hash
//       - unsigned int n: il numero degli elementi memorizzati nella tabella
//       - void *param: altri parametri per la gestione dei dati
//output: la tabella hash modificata
HASH_TABLE OttimizzaTabella(HASH_TABLE tabellaHash, unsigned int n, void *param)
{
  HASH_TABLE nuovaTabellaHash;
  int i;
  void *id;
  
  //inizializzo la nuova tabella hash
  nuovaTabellaHash = InizializzaTabella(n, tabellaHash.funzioniLista);
  
  //per tutti i valori della prima tabella estraggo tutti gli elementi
  //indice per indice e li inserisco nella nuova
  for(i = 0; i < tabellaHash.dimensione; i++)
  {
    id = PopLista(&(tabellaHash.tabella[i]));
    while(id != NULL)
    {
      InserisciElementoTabella(nuovaTabellaHash, id, param);
      id = PopLista(&(tabellaHash.tabella[i]));
    }
  }
  //dealloco la vecchia tabella
  free(tabellaHash.tabella);
  return nuovaTabellaHash;
}


//Dealloca le strutture della tabella hash
//input: - HASH_TABLE tabellaHash: la tabella da deallocare
//       - void *param: altri parametri per la gestione
//output: la tabella hash deallocata
HASH_TABLE DeallocaTabella(HASH_TABLE tabellaHash, void *param)
{
  int i;
  //libero lo spazio occupato da tutte le liste
  for(i = 0; i < tabellaHash.dimensione; i++)
    tabellaHash.tabella[i] = DeallocaLista(tabellaHash.tabella[i], *tabellaHash.funzioniLista, param);
  //libero lo spazio occupato dal puntatore alle funzioni
  free(tabellaHash.tabella);
  //azzero la dimensione
  tabellaHash.dimensione = 0;
  return tabellaHash;
}
