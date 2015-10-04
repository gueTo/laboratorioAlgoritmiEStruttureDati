/* 
   FUNZIONI DI GESTIONE DI TABELLE DI CORRISPONDENZA
   Prototipi e tipi per la gestione di corrispondenze del tipo
   intero/generico strutturate mediante una doppia tabella
   hash concatenata per l'indicizzazione su entrambi i valori
   indice/identificatore 
   
   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com                             */

#include "TabellaHash.h"

#ifndef FACT_DIMENSION
#define FACT_DIMENSION 1.20
#endif


#ifndef CORRESPONDENCE
#define CORRESPONDENCE CORRESPONDENCE
typedef struct
{
  unsigned int indice;
  void *id;
} CORRESPONDENCE;
#endif

#ifndef CORR_TABLE
#define CORR_TABLE CORR_TABLE
typedef struct
{
  HASH_TABLE corrIndice; //la tabella delle corrispondenze ordinata per indice
  HASH_TABLE corrId; //la tabella delle corrispondenze ordinata per identificatore
} CORR_TABLE;
#endif


//Inizializza la tabella delle corrispondenze
//input: - unsigned int dimensione: la dimensione della tabella
//       - OPERAZIONI *funzioniCorrIndice: le funzioni per la corrispondenza degli indici
//       - OPERAZIONI *funzioniCorrId: le funzioni per la corrispondenza degli id
//output: una tabella delle corrispondenze nuova
CORR_TABLE InizializzaCorrispondenze(unsigned int dimensione, OPERAZIONI *funzioniCorrIndice, OPERAZIONI *funzioniCorrId);


//Inserisce un elemento nella tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - CORRESPONDENCE *corrispondenza: la corrispondenza da inserire
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE InserisciCorrispondenza(CORR_TABLE tabellaCorr, CORRESPONDENCE *corrispondenza, OPERAZIONI *funzioniId);       


//Cancella un elemento dalla tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - CORRESPONDENCE *corrispondenza: la corrispondenza da eliminare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE CancellaCorrispondenza(CORR_TABLE tabellaCorr, CORRESPONDENCE *corrispondenza, OPERAZIONI *funzioniId);


//Cerca un elemento nella tabella delle corrispondenze fornendo l'indice
//input: - CORR_TABLE tabellaCorr: la tabella in cui cercare
//       - unsigned int indice: l'indice da ricercare
//output: un puntatore all'elemento della tabella desiderato
CORRESPONDENCE *CercaCorrispondenzaIndice(CORR_TABLE tabellaCorr, unsigned int indice);


//Cerca un elemento nella tabella delle corrispondenze fornendo l'identificatore
//input: - CORR_TABLE tabellaCorr: la tabella in cui cercare
//       - void *id: l'identificatore da ricercare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: un puntatore all'elemento della tabella desiderato
CORRESPONDENCE *CercaCorrispondenzaId(CORR_TABLE tabellaCorr, void *id, OPERAZIONI *funzioniId);


//Stampa sull'output fornito la tabella delle corrispondenze
//input: - FILE *fp: l'output su cui stampare
//       - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli id
//output: nessuno
void StampaCorrispondenze(FILE *fp, CORR_TABLE tabellaCorr, OPERAZIONI *funzioniId);


//Modifica l'indice di una corrispondenza e la reinserisce
//input: - CORR_TABLE tabellaCorr: la tabella
//       - unsigned int vecchioIndice: l'indice da modificare
//       - unsigned int nuovoIndice: il nuovo indice
//output: nessuno
void ModificaIndiceCorrispondenza(CORR_TABLE tabellaCorr, unsigned int vecchioIndice, unsigned int nuovoIndice);


//Ottimizza la tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella da ottimizzare
//       - unsigned int nuovaDim: la nuova dimensione della tabella delle
//                                corrispondenze
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE OttimizzaCorrispondenze(CORR_TABLE tabellaCorr, unsigned int nuovaDim, OPERAZIONI *funzioniId);


//Ritorna la dimensione delle tabella hash della corrispondenza
//input: CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//output: la dimensione delle due tabelle hash sottostanti
unsigned int GetDimensioneCorrispondenza(CORR_TABLE tabellaCorr);


//Dealloca la tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella da deallocare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze deallocata
CORR_TABLE DeallocaCorrispondenze(CORR_TABLE tabellaCorr, OPERAZIONI *funzioniId);

//Questa funzione non fa niente
//utilizzata per sostituire la deallocazione
//nella cancellazione dalla tabella delle corrispondenze
//in modo da non deallocare il dato che dovrà poi essere
//ricercato e deallocato anche nell'altra lista
void FunzionePigra(void *nha, void *bho);


//FUNZIONI PER LA GESTIONE DI LISTE DI CORRISPONDENZE
//utilizzate tra le funzioni della tabella corrispondenze

//Alloca una struttura di tipo CORRISPONDENCE
//input: - void *corrispondenza: la corrispondenza da allocare
//       - void *funzioniId: le funzioni per la gestione dell'identificatore
//output: un puntatore a struttura CORRISPONDENCE allocata
void *AllocaCorrispondenza(void *corrispondenza, void *funzioniId);


//Stampa su output una corrispondenza
//input: - FILE *fp: l'output su cui stampare
//       - void *corrispondenza: la corrispondenza da stampare
//       - void *funzioniId: le funzioni per la gestione degli id
//output: nessuno
void StampaCorrispondenza(FILE *fp, void *corrispondenza, void *funzioniId);


//Confronta due corrispondenze per identificatore
//input: - void *primaCorr: la prima corrispondenza da comparare
//       - void *secondaCorr: la seconda corrispondenza da comparare
//       - void *funzioniId: funzioni per la gestione degli identificatori,
//                           qui non utilizzate
//output: 0 se le corrispondenze hanno lo stesso indice, 1 se il primo indice
//        è maggiore del secondo, -1 altrimenti
int ComparaCorrispondenzeIndice(void *primaCorr, void *secondaCorr, void *funzioniId);


//Confronta due corrispondenze per identificatore
//input: - void *primaCorr: la prima corrispondenza da comparare
//       - void *secondaCorr: la seconda corrispondenza da comparare
//       - void *funzioniId: funzioni per la gestione degli identificatori,
//output: 0 se le corrispondenze hanno lo stesso id, 1 se il primo id è maggiore
//        del secondo, -1 altrimenti
int ComparaCorrispondenzeId(void *primaCorr, void *secondaCorr, void *funzioniId);


//Gestisce collisioni di corrispondenze (indice o id)
//in questo caso ammettiamo ripetizioni di corrispondenze
//e restituiamo l'elemento che ha causato la collisione
//input: - void *corrispondenza: la corrispondenza da gestire
//       - void *funzioniId: le funzioni di gestione dell'identificatore,
//                           qui non utilizzate
//output: restituisce il dato che ha generato la collisione così com'è
void *GestisciCollisioneCorrispondenze(void *corrispondenza, void *funzioniId);


//Dealloca un dato di tipo corrispondenza
//input: - void *vorrispondenza: la corrispondenza da deallocare
//       - void *funzioniId: le funzioni da utilizzare per la gestione di un id
//output: nessuno
void DeallocaCorrispondenza(void *corrispondenza, void *funzioniId);


//Funzione di hash per gli indici di una corrispondenza
//l'hash di un indice di corrispondenza è proprio il suo indice
//input: - void *corrispondenza: la corrispondenza da codificare
//       - void *funzioniId: le funzioni da utilizzare per la gestione
//                           degli identificatori, qui non utilizzate
//output: un intero lungo senza segno con la codifica dell'indice
unsigned long HashIndice(void *corrispondenza, void *funzioniId);


//Funzione di hash per gli identificatori di una corrispondenza
//l'hash di un indice di corrispondenza è proprio il suo indice
//input: - void *corrispondenza: la corrispondenza da codificare
//       - void *funzioniId: le funzioni da utilizzare per la gestione
//                           degli identificatori
//output: un intero lungo senza segno con la codifica dell'indice
unsigned long HashId(void *corrispondenza, void *funzioniId);


//Legge una corrispondenza da un file
//input: - void *fp: il file da cui leggere
//       - void *funzioniId: le funzioni per la gestione degli identificatori
//output: un puntatore alla corrispondenza allocata
void *LeggiCorrispondenzaDaFile(void *fp, void *funzioniId);
