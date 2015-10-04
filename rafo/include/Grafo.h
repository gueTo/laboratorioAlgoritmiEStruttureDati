/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Header per tipi e prototipi delle funzioni della 
  gestione dei grafi per entrambe le rappresentazioni 
  supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com                       */

#include "Corrispondenze.h"
#include "list.h"


//definiscoi il fattore massimo di tolleranza tra la dimensione della tabella
//delle corrispondenze e quella dell'array di vertici
#ifndef MAX_TOL_CORR
#define MAX_TOL_CORR 2
#endif

//definisco il fattore minimo di tolleranza di dimensione tra la tabella
//delle corrispondenze e l'array di vertici
#ifndef MIN_TOL_DIM
#define MIN_TOL_DIM 0.6
#endif

//defiinsco il fattore di cui incrementare l'array dei vertici quando è pieno
//inoltre aggiungo 1 per avere almeno la possibilità di aggiungere un vertice 
//senza dover rimodificare tutto quando la matrice ha dimensioni esigue
#ifndef INCR_FACT
#define INCR_FACT 1.20 + 1
#endif

//definisco il peso di default quando non leggo alcun peso associato ad una rco
#ifndef PESO_DEFAULT
#define PESO_DEFAULT 1
#endif

//definisco il tipo COLOR da utilizzare per colorare i vertici
#ifndef COLOR
#define COLOR COLOR
typedef enum COLOR {BIANCO, GRIGIO, NERO} COLOR;
#endif


//definisco un generico nodo di un grafo
#ifndef GRAPH_NODE
#define GRAPH_NODE GRAPH_NODE
typedef struct
{
  void *id; //l'identificatore del nodo
  COLOR colore; //il colore del vertice, usato per le visite
  unsigned int predecessore; //l'indice nella tabella delle corrispondenze del predecessore in una visita
  unsigned int scoperta; //il tempo di scoperta del vertice nella DFS
  unsigned int completamento; //il tempo di completamento del vertice nella DFS
  unsigned int distanza; //la distanza minima dalla sorgente in una BFS
} GRAPH_NODE;
#endif


//definisco la struttura che memorizzerà il grafo
#ifndef GRAPH
#define GRAPH GRAPH
typedef struct
{
  unsigned int numVertici; //il nuemro di vertici memorizzati nel grafo
  OPERAZIONI *funzioniId; //le funzioni per la gestione degli identificatori
  GRAPH_NODE **vertici; //un array di puntatori a vertice
  unsigned int dimensioneArray; //la dimensione dell'array di vertici
  LIST listaLiberi; //la lista dei vertici non utilizzati nell'array
  CORR_TABLE corrisp; //la tabella delle corrispondenze tra l'indice dell'array
                      //di nodi e l'identificatore
  void *paramRappresentazione; //i parametri di rappresentazione per i due tipi
                               //di rappresentazione supportati (le funzioni
                               //per la gestione di liste di archi per la rap-
                               //presentazione a liste di adiacenza o la matrice
                               //di adiacenza per la rappresentazione con matrice)
} GRAPH;
#endif


//definisco la struttura di un arco del grafo
#ifndef GRAPH_ARC
#define GRAPH_ARC GRAPH_ARC
typedef struct
{
  unsigned int indiceVertice; //l'indice del nodo puntato
  double peso; //il peso dell'arco
} GRAPH_ARC;
#endif


//definisco le funzioni di callback per la rappresentazione
//del grafo
#ifndef GRAPH_FUNC
#define GRAPH_FUNC GRAPH_FUNC
typedef struct
{
  void *(*InizializzaParametroGrafo)(GRAPH grafo); //inizializza il parametro del grafo
  void *(*InizializzaParametroVertice)(GRAPH grafo, unsigned int indiceNodo); //inizializza il parametro del vertice
  void *(*InserisciArco)(GRAPH grafo, void *, unsigned int indice, GRAPH_ARC arco); //inserisce un arco
  void *(*InizializzaIteratore)(GRAPH grafo, unsigned int indiceNodo); //inizializza un iteratore per la ricerca di archi
  GRAPH_ARC (*GetArcoSuccessivo)(GRAPH grafo, unsigned int indiceNodo, void *iter); //funzione che recupera l'arco 
                                                                                            //successivo del nodo
  GRAPH (*OttimizzaArchi)(GRAPH grafo, unsigned int primoIndice, unsigned int secondoIndice); //ottimizza il parametro
                                                                                       //del grafo (per rappresentazione con matrice)
  int (*EsisteArco)(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice); //funzione di ricerca di un arco in un vertice
  GRAPH (*TrasponiArchi)(GRAPH grafo, GRAPH trasposto); //la funzione per trasporre gli archi
  void (*CancellaArco)(GRAPH grafo, unsigned int indiceNodo, unsigned int indiceArco); //funzione di cancellazione di un arco
  void *(*DeallocaParametroVertice)(GRAPH grafo, unsigned int indiceNodo); //dealloca il parametro rappresentazione del vertice
  void *(*DeallocaParametroGrafo)(GRAPH grafo); //dealloca il parametro rappresentazione del grafo
} GRAPH_FUNC;
#endif


//Inserisce le funzioni della rappresentazione del grafo in una struttura
//input: - void *(*InizializzaParametroGrafo)(GRAPH): inizializza il parametro del grafo
//       - GRAPH (*InizializzaParametroVertice)(): inizializza il parametro del vertice
//       - void *(*InserisciArco)(GRAPH, void *, unsigned int, GRAPH_ARC): inserisce un arco//     
//       - void *(*InizializzaIteratore)(GRAPH, unsigned int): inizializza un iteratore per la ricerca di archi
//       - GRAPH_ARC *(*GetArcoSuccessivo)(GRAPH , unsigned int, void *): funzione che recupera l'arco 
//                                                                      successivo del nodo
//       - int (*EsisteArco)(GRAPH , unsigned int, unsigned int): funzione di ricerca di un arco in un vertice
//       - GRAPH (*OttimizzaArchi)(GRAPH, unsigned int, unsigned int): funzione di ottimizzazione
//       - void (*CancellaArco)(GRAPH , unsigned int, unsigned int): funzione di cancellazione di un arco
//       - GRAPH (*TrasponiArchi)(GRAPH, GRAPH): funzione di trasposizione degli archi
//       - void *(*DeallocaParametroVertice)(GRAPH, unsigned int): dealloca il parametro rappresentazione del vertice
//       - void (*DeallocaParametroGrafo)(GRAPH): dealloca il parametro rappresentazione del grafo
//output: una struttura GRAPH_FUNC che contiene le funzioni in input
GRAPH_FUNC InserisciFunzioniRappresentazione(void *(*InizializzaParametroGrafo)(GRAPH), 
                   void *(*InizializzaParametroVertice)(GRAPH, unsigned int), void *(*InserisciArco)(GRAPH, void *, unsigned int, GRAPH_ARC), 
                   void *(*InizializzaIteratore)(GRAPH, unsigned int), GRAPH_ARC (*GetArcoSuccessivo)(GRAPH, unsigned int, void *), 
                   int (*EsisteArco)(GRAPH, unsigned int, unsigned int), GRAPH (*OttimizzaArchi)(GRAPH, unsigned int, unsigned int),
                   void (*CancellaArco)(GRAPH, unsigned int, unsigned int), GRAPH (*TrasponiArchi)(GRAPH, GRAPH),
                   void *(*DeallocaParametroVertice)(GRAPH, unsigned int), void *(*DeallocaParametroGrafo)(GRAPH));
                   

//Inizializza il grafo
//input: - unsigned int numVertici: il numero di vertici
//       - unsigned int dimensioneArray: la dimensione di partenza dell'array dei vertici
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - OPERAZIONI funzioniId: le funzioni da utilizzare sull'identificatore
//output: un nuovo grafo inizializzato
GRAPH InizializzaGrafo(unsigned int numVertici, unsigned int dimensioneArray, GRAPH_FUNC funzioniGrafo, OPERAZIONI *funzioniId);


//Inserisce un vertice nel grafo
//input: - GRAPH grafo: il grafo in cui inserire
//       - GRAPH_FUNC funzioniGrafo: le funzioni dipendenti dalla rappresentazione
//       - void *id: l'identificativo del nuovo nodo
//output: il grafo modificato
GRAPH InserisciVertice(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id);


//Restituisce il vertice associato partendo dall'identificatore
//input: - GRAPH grafo: il grafo
//       - void *id: l'identificatore del vertice
//output: un puntatore al vertice o NULL se tale vertice non c'è
GRAPH_NODE *RecuperaVertice(GRAPH grafo, void *id);


//Cancella un vertice dal grafo
//input: - GRAPH grafo: il grafo in cui cancellare il vertice
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con la rappresentazione
//       - void *id: l'identificativo del nodo da cancellare
//output: il grafo modificato
GRAPH CancellaVertice(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id);


//Inserisce un arco in un grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione del grafo
//       - void *idVertice: l'id del vertice in cui inserire l'arco
//       - void *idArco: l'id del vertice bersaglio
//       - double peso: il peso dell'arco da inserire
//output: nessuno
void InserisciArco(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idVertice, void *idArco, double peso);


//Cancella un arco
//input - GRAPH grafo: il grafo in cui cancellare l'arco
//      - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//      - void *idVertice: l'identificativo del vertice a cui aggiungere l'arco
//      - void *idArco: l'identificativo del vertice a cui l'arco punta
//output: nessuno
void CancellaArco(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idVertice, void *idArco);


//Ottimizza il grafo, riducendo la dimensione dell'array dei vertici, della
//tabella delle corrispondenze e dei parametri della rappresentazione
//input: - GRAPH grafo: il grafo da ottimizzare
//       - GRAPH_FUNC funzioniGrafo: le funzioni dipendenti dalla rappresentazione
//output: il grafo ottimizzato
GRAPH OttimizzaGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo);

//Dealloca interamente un grafo
//input: - GRAPH grafo: il grafo da deallocare
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione
//                                   del grafo
//output: il grafo deallocato
GRAPH DeallocaGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Cambia la rappresentazione del grafo, consentendo
//di passare dalla rappresentazione a liste di adiacenza
//a quella a matrice e viceversa
//input: - GRAPH grafo: il grafo di cui cambiare la rappresentazione
//       - GRAPH_FUNC vecchiaRappr: le funzioni della vecchia rappresentazione
//       - GRAPH_FUNC nuovaRappr: le funzioni della nuova rappresentazione
//output: il grafo rappresentato alternativamente
GRAPH CambiaRappresentazione(GRAPH grafo, GRAPH_FUNC vecchiaRappr, GRAPH_FUNC nuovaRappr);
