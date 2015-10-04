#include <stdlib.h>


/**STRUTTURE DATI**/
#ifndef _NODO_LISTA_
#define _NODO_LISTA_

typedef struct NODO_LISTA{
    void* elem;
    struct NODO_LISTA* next;
}NODO_LISTA;

typedef NODO_LISTA * LIST;
#endif // NODO_LISTA

#ifndef _OPERAZIONI_LISTA_
#define _OPERAZIONI_LISTA_
typedef struct OPERAZIONI_LISTA{
    void *(*allocaDato)(void *info, void *param); //funzione di allocazione
    void (*stampaDato)(FILE *fp, void *info, void *param); //funzione di stampa
    int (*comparaDati)(void *x, void *y, void *param); //funzione di confronto, restituisce
                                      //0 se i due parametri sono uguali
                                      //1 se il primo è maggiore del secondo
                                      //-1 altrimenti
    void *(*gestisciCollisione)(void *info, void *param); //funzione per la gestione di collisioni
    void (*deallocaDato)(void *info, void *param); //funzione di deallocazione di un nodo
    void *(*leggiDaInput)(void *source, void *param); //funzione di lettura di un dato da input
    unsigned long (*funzioneHash)(void *info, void *param); //funzione di hash dell'elemento
}OPERAZIONI_LISTA;
#endif // OPERAZIONI_LISTA



/**DICHIARAZIONE FUNZIONI**/
OPERAZIONI_LISTA initFunzioni(void *(*AllocaDato)(void *, void *), void (*StampaDato)(FILE *, void *, void *),
                                  int (*ComparaDati)(void *, void *, void *),  void *(*GestisciCollisione)(void *, void *),
                                  void (*DeallocaDato)(void *, void *), void *(*LeggiDaInput)(void *, void *),
                                  unsigned long (*FunzioneHash)(void *, void *));


OPERAZIONI_LISTA InserisciFunzioni(void *(*AllocaDato)(void *, void *), void (*StampaDato)(FILE *, void *, void *),
                                  int (*ComparaDati)(void *, void *, void *),  void *(*GestisciCollisione)(void *, void *),
                                  void (*DeallocaDato)(void *, void *), void *(*LeggiDaInput)(void *, void *),
                                  unsigned long (*FunzioneHash)(void *, void *));

NODO_LISTA* nuovoNodo(void*);

LIST inserisciNuovoNodo(LIST, OPERAZIONI_LISTA*, NODO_LISTA*, void* );
NODO_LISTA* cercaNodo(LIST, OPERAZIONI_LISTA*, void*, void*);
NODO_LISTA* deallocaNodo(NODO_LISTA*, OPERAZIONI_LISTA*, void*);

LIST cancellaDallaLista(LIST, OPERAZIONI_LISTA* , void* , void* );



void stampaLista(FILE *, LIST, OPERAZIONI_LISTA*, void *);

LIST deallocaLista(LIST, OPERAZIONI_LISTA*, void*);

LIST PushLista(LIST, void *);
void* TopLista(LIST);
LIST PopLista(LIST);


