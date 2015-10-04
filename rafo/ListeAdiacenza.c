/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni per la gestione di rappresentazioni
  di archi mediante liste di adiacenza
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com                       */

#include "include\ListeAdiacenza.h"

//Inizializza le funzioni da utilizzare per le liste di archi
//input: GRAPH grafo: il grafo di cui inizializzare le funzioni (non utilizzato qui)
//output: un puntatore alla struttura con le funzioni per la gestione delle liste di archi
//        e le liste di adiacenza dei vertici
void *InizializzaParametroListaAdj(GRAPH grafo)
{
  LIST_ADJ *listaAdiacenze;
  int i;
  //alloco la struttura
  listaAdiacenze = (LIST_ADJ *)malloc(sizeof(LIST_ADJ));
  
  //alloco ed inserisco le funzioni da utilizzare per gli archi
  listaAdiacenze->fun = (OPERAZIONI *)malloc(sizeof(OPERAZIONI));
  *listaAdiacenze->fun = InserisciFunzioni(&AllocaArco, &StampaArco, &ComparaArchi, &GestisciCollisioneArco, 
                                    &DeallocaArco, &LeggiArcoDaInput, &HashArchi);
  
  //alloco memoria per l'array di liste di adiacenza
  //tale array avrà sempre la dimensione dell'array di vertici del grafo
  listaAdiacenze->liste = (LIST *)malloc(grafo.dimensioneArray*sizeof(LIST));
  
  //inizializzo tutte le liste
  for(i = 0; i < grafo.dimensioneArray; i++)
    listaAdiacenze->liste[i] = InizializzaLista();
  
  return listaAdiacenze;
}

//Inizializza le liste di adiacenza di ogni vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice di cui inizializzare il parametro
//output: la struttura LIST_ADJ modificata
void *InizializzaParametroVerticeListaAdj(GRAPH grafo, unsigned int indiceVertice)
{
  int i;
  //se l'array dei vertici viene modificato lo rialloco ed azzero gli elementi addizionali
  if(ListaVuota(grafo.listaLiberi) && grafo.numVertici < grafo.dimensioneArray)
  {
    ((LIST_ADJ *)grafo.paramRappresentazione)->liste = (LIST *)realloc(((LIST_ADJ *)grafo.paramRappresentazione)->liste, 
                                                         grafo.dimensioneArray*sizeof(LIST));
    for(i = grafo.numVertici; i < grafo.dimensioneArray; i++)
      ((LIST_ADJ *)grafo.paramRappresentazione)->liste[i] = InizializzaLista();
  }
  //inizializzo la lista di adiacenza associata al vertice
  ((LIST_ADJ *)grafo.paramRappresentazione)->liste[indiceVertice] = InizializzaLista();
  return grafo.paramRappresentazione;
}


//Inserisce un arco nella lista di adiacenze del vertice
//input: - GRAPH grafo: il grafo
//       - void *paramRappr: il parametro della rappresentazione
//       - unsigned int indiceVertice: il vertice in cui inserire l'arco
//       - GRAPH_ARC arco: l'arco da inserire
//output: il parametro del nodo (ossia la lista delle adiacenze) modificato
void *InserisciArcoListaAdj(GRAPH grafo, void *paramRappr, unsigned int indiceVertice, GRAPH_ARC arco)
{
  GRAPH_ARC *nuovoArco;
  nuovoArco = (GRAPH_ARC *)malloc(sizeof(GRAPH_ARC));
  nuovoArco->indiceVertice = arco.indiceVertice;
  nuovoArco->peso = arco.peso;
  
  //inserisco il nuovo arco nella lista dei vertici
  ((LIST_ADJ *)paramRappr)->liste[indiceVertice] = 
         InserisciInLista(((LIST_ADJ *)paramRappr)->liste[indiceVertice], *((LIST_ADJ *)paramRappr)->fun,
               AllocaNodo(nuovoArco), NULL);
  return paramRappr;
}


//Inizializza l'iteratore per lo scorrimento degli archi nelle liste di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice a cui inizializzare l'iteratore
//output: l'iteratore che punta al primo elemento della lista di adiacenza del vertice
void *InizializzaIteratoreListaAdj(GRAPH grafo, unsigned int indiceVertice)
{
  LIST iter;
  //l'iteratore punta alla testa della lista di adiacenza del vertice
  iter = ((LIST_ADJ *)grafo.paramRappresentazione)->liste[indiceVertice];
  return iter;
}


//Restituisce il primo arco non letto di un nodo
//necessita dell'iteratore
//input: - GRAPH grafo: il grafo, qui non utilizzato
//       - unsigned int indiceVertice: il vertice di cui leggere l'arco successivo, qui
//                                     non utilizzato ed inserito per specifiche
//       - void *iter: un puntatore all'iteratore                      
GRAPH_ARC GetArcoSuccessivoListaAdj(GRAPH grafo, unsigned int indiceVertice, void *iter)
{
  GRAPH_ARC arco;
  //recupero l'arco
  arco = *(GRAPH_ARC *)((*(LIST *)iter)->info);
  *(LIST *)iter = (*(LIST *)iter)->next;
  return arco;
}


//Cerca un arco nella lista di adiacenza
//input: - GRAPH grafo: il grafo in cui cercare
//       - unsigned int indiceVertice: il vertice a cui eliminare l'arco
//       - unsigned int indiceArco: l'identificatore del nodo verso cui l'arco da eliminare punta
//output: 1 se l'arco esiste, 0 altrimenti
int EsisteArcoListaAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice)
{
  GRAPH_ARC arcoTmp;
  int ret;
  //costruisco l'arco temporaneo per ricercare nella lista
  arcoTmp.indiceVertice = alVertice;
  //controllo la presenza dell'arco nella lista
  if(CercaNellaLista(((LIST_ADJ *)grafo.paramRappresentazione)->liste[dalVertice], 
                            *((LIST_ADJ *)grafo.paramRappresentazione)->fun, &arcoTmp, grafo.funzioniId) == NULL)
    ret = 0;
  else
    ret = 1;
  return ret;
}


//Cancella un arco dalla lista di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceNodo: il vertice a cui cancellare l'arco
//       - unsigned int indiceArco: l'indice del nodo a cui l'arco punta
//output: nessuno
void CancellaArcoListaAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice)
{
  GRAPH_ARC arcoTmp;
  //compongo l'arco temporaneo per la ricerca con l'indice del vertice bersaglio
  arcoTmp.indiceVertice = alVertice;
  StampaLista(stdout, ((LIST_ADJ *)grafo.paramRappresentazione)->liste[dalVertice], *((LIST_ADJ *)grafo.paramRappresentazione)->fun, NULL);
  //lo cancello dalla lista
  ((LIST_ADJ *)grafo.paramRappresentazione)->liste[dalVertice] = 
                        CancellaDallaLista(((LIST_ADJ *)grafo.paramRappresentazione)->liste[dalVertice],
                                               *((LIST_ADJ *)grafo.paramRappresentazione)->fun, &arcoTmp, grafo.funzioniId);
}


//Ottimizza le liste di archi, in seguito ad un'ottimizzazione dell'array di vertici
//input: - GRAPH grafo: il grafo
//       - unsigned int vecchioIndice: il valore dell'indice obsoleto
//       - unsigned int nuovoIndice: il valore del nuovo indice del vertice
//output: il grafo modificato (se necessario)
GRAPH OttimizzaArchiListaAdj(GRAPH grafo, unsigned int vecchioIndice, unsigned int nuovoIndice)
{
  int i;
  GRAPH_ARC *arcoTmp;
  GRAPH_ARC arco;

  //scorro tutti i vertici cercando gli archi che hanno come indice del vertice
  //puntato uguale al vecchio indice e li modifico inserendo il nuovo indice
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      //assegno il valore del vecchio indice alla struttura temporanea per la ricerca degli archi e cerco
      arco.indiceVertice = vecchioIndice;
      arcoTmp = CercaNellaLista(((LIST_ADJ *)grafo.paramRappresentazione)->liste[i], *((LIST_ADJ *)grafo.paramRappresentazione)->fun, 
                       &arco, grafo.funzioniId);
      //se il vertice ha un arco verso il nuovo nodo lo rimuovo ed inserisco un nuovo vertice al vertice corretto
      if(arcoTmp != NULL)
      {
        //creo l'arco che inserirò
        arco.peso = arcoTmp->peso;
        arco.indiceVertice = nuovoIndice;
        CancellaArcoListaAdj(grafo, i, vecchioIndice);
        grafo.paramRappresentazione = InserisciArcoListaAdj(grafo, grafo.paramRappresentazione, i, arco);
      }
    }
  }
  return grafo;
}


//Traspone gli archi di un grafo
//input: - GRAPH grafo: il grafo i cui archi vanno trasposti
//       - GRAPH trasposto: il grafo verso cui trasporre gli archi
//output: il grafo trasposto
GRAPH TrasponiArchiListaAdj(GRAPH grafo, GRAPH trasposto)
{
  int i;
  LIST iter;
  GRAPH_ARC arco;
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      //inizializzo il puntatore alla testa della lista di adiacenza del vertice
      iter = ((LIST_ADJ *)grafo.paramRappresentazione)->liste[i];
      while(iter != NULL)
      {
        //compongo l'arco del trasposto
        arco.peso = ((GRAPH_ARC *)iter->info)->peso;
        arco.indiceVertice = i;
        //inserisco il nuovo arco
        trasposto.paramRappresentazione = InserisciArcoListaAdj(trasposto, trasposto.paramRappresentazione, 
                                                                 ((GRAPH_ARC *)iter->info)->indiceVertice, arco);
        iter = iter->next;
      }
    }
  }
  return trasposto;
}


//Dealloca la lista di adiacenza di un vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: il vertice di cui deallocare la lista
//output: il nuovo valore della lista (NULL se è tutto andato a buon fine)
void *DeallocaParametroVerticeListaAdj(GRAPH grafo, unsigned int indiceVertice)
{
  ((LIST_ADJ *)grafo.paramRappresentazione)->liste[indiceVertice] = DeallocaLista
                                   (((LIST_ADJ *)grafo.paramRappresentazione)->liste[indiceVertice], 
                                   *((LIST_ADJ *)grafo.paramRappresentazione)->fun, NULL);
  return grafo.paramRappresentazione;
}


//Dealloca la struttura ADJ_LIST del grafo
//input: GRAPH grafo: il grafo
//output: un puntatore a NULL
void *DeallocaParametroListaAdj(GRAPH grafo)
{
  int i;
  //dealloco le liste dell'array di liste
  for(i = 0; i < grafo.dimensioneArray; i++)
    grafo.paramRappresentazione = DeallocaParametroVerticeListaAdj(grafo, i);
    
  free(((LIST_ADJ *)grafo.paramRappresentazione)->fun);
  free(grafo.paramRappresentazione);
  return NULL;
}




/* FUNZIONI PER LA GESTIONE DI LISTE DI ARCHI
 tali strutture sono utilizzate nelle liste di adiacenza */


//Calcola la funzione Hash di un arco, basato sull'indice del
//vertice a cui punta
//input: - void *arco: l'arco da calcolare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: il codice hash dell'arco
unsigned long HashArchi(void *arco, void *param)
{
  return ((GRAPH_ARC *)arco)->indiceVertice;
}


//Alloca memoria per un arco
//input: - void *arco: l'arco da allocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: l'arco allocato
void *AllocaArco(void *arco, void *param)
{
  GRAPH_ARC *ret;
  ret = (GRAPH_ARC *)malloc(sizeof(GRAPH_ARC));
  ret->indiceVertice = ((GRAPH_ARC *)arco)->indiceVertice;
  ret->peso = ((GRAPH_ARC *)arco)->peso;
  return ret;  
}

//Compara due stringhe. Utilizza la funzione strcmp
//input: - void *primoArco: il primo arco
//       - void *secondoArco: il secondo arco
//       - void *param: parametro non utilizzato inserito per specifiche
//output: 0 se gli archi sono uguali, 1 se il primo
//        è maggiore del secondo, -1 altrimenti
int ComparaArchi(void *primoArco, void *secondoArco, void *param)
{
  //confronto gli indici dei due archi
  int ret;
  if(((GRAPH_ARC *)primoArco)->indiceVertice < ((GRAPH_ARC *)secondoArco)->indiceVertice)
    ret = 1;
  else if(((GRAPH_ARC *)primoArco)->indiceVertice == ((GRAPH_ARC *)secondoArco)->indiceVertice)
    ret = 0;
  else
    ret = -1;
  return ret;
}

//Stampa una Arco
//input: - FILE *fp: l'output su cui scrivere
//       - void *arco: l'arco da stampare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void StampaArco(FILE *fp, void *arco, void *param)
{
  //dereferenzio e stampo il peso e l'identificatore del nodo 
  fprintf(fp, "(%.2lf)%u ", ((GRAPH_ARC *)arco)->peso, ((GRAPH_ARC *)arco)->indiceVertice);
}

//Gestisce le collisioni tra archi
//non si ammettono ripetizioni di archi
//e pertanto tale funzione restituirà NULL
//input: - void *arco: l'arco che ha causato la collisione
//       - void *param: parametro non utilizzato inserito per specifiche
//output: il valore NULL
void *GestisciCollisioneArco(void *arco, void *param)
{
  return NULL;
}

//Dealloca un arco
//input: - void *arco: l'arco da deallocare
//       - void *param: parametro non utilizzato inserito per specifiche
//output: nessuno
void DeallocaArco(void *arco, void *param)
{
  free(arco);
}

//Funzione non utilizzata inserita per specifiche
//input: void *fp: un puntatore al file
//       - void *param: parametro non utilizzato inserito per specifiche
//output: un puntatore all'arco letto, oppure NULL in caso di dati non validi
void *LeggiArcoDaInput(void *fp, void *param)
{
  return NULL;
}

