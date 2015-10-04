/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni fondamentali di gestione dei grafi
  per entrambe le rappresentazioni supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */


#include "include\Grafo.h"


//Inserisce le funzioni della rappresentazione del grafo in una struttura
//input: - void *(*InizializzaParametroGrafo)(GRAPH): inizializza il parametro del grafo
//       - void *(*InizializzaParametroVertice)(): inizializza il parametro del vertice
//       - GRAPH_NODE (*InserisciArco)(GRAPH , void *, unsigned int, GRAPH_ARC): inserisce un arco//     
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
                   void *(*DeallocaParametroVertice)(GRAPH, unsigned int), void *(*DeallocaParametroGrafo)(GRAPH))
{
  GRAPH_FUNC funzioni;
  funzioni.InizializzaParametroGrafo = InizializzaParametroGrafo;
  funzioni.InizializzaParametroVertice = InizializzaParametroVertice;
  funzioni.InserisciArco = InserisciArco;
  funzioni.InizializzaIteratore = InizializzaIteratore;
  funzioni.GetArcoSuccessivo = GetArcoSuccessivo;
  funzioni.EsisteArco = EsisteArco;
  funzioni.OttimizzaArchi = OttimizzaArchi;
  funzioni.CancellaArco = CancellaArco;
  funzioni.TrasponiArchi = TrasponiArchi;
  funzioni.DeallocaParametroVertice = DeallocaParametroVertice;
  funzioni.DeallocaParametroGrafo = DeallocaParametroGrafo;
  return funzioni;
}


//Inizializza il grafo
//input: - unsigned int numVertici: il numero di vertici
//       - unsigned int dimensioneArray: la dimensione di partenza dell'array dei vertici
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - OPERAZIONI funzioniId: le funzioni da utilizzare sull'identificatore
//output: un nuovo grafo inizializzato
GRAPH InizializzaGrafo(unsigned int numVertici, unsigned int dimensioneArray, GRAPH_FUNC funzioniGrafo, OPERAZIONI *funzioniId)
{
  GRAPH grafo;
  OPERAZIONI *funzioniIdCorr;
  OPERAZIONI *funzioniIndiceCorr;
  
  //inserisco il numero di vertici e le funzioni per la gestione degli id
  grafo.numVertici = numVertici;
  grafo.funzioniId = funzioniId;
  
  //inizializzo il vettore di puntatori a nodo e la lista degli spazi liberi associata
  grafo.dimensioneArray = dimensioneArray;
  grafo.vertici = (GRAPH_NODE **)malloc(dimensioneArray*sizeof(GRAPH_NODE *));
  grafo.listaLiberi = InizializzaLista();
  
  //inizializzo le funzioni per la gestione delle corrispondenze da inserire
  //nella tabella delle corrispondenze sia dal lato id che dal lato indici
  funzioniIdCorr = (OPERAZIONI *)malloc(sizeof(OPERAZIONI));
  *funzioniIdCorr = InserisciFunzioni(&AllocaCorrispondenza, &StampaCorrispondenza, &ComparaCorrispondenzeId, 
                                                        &GestisciCollisioneCorrispondenze, &DeallocaCorrispondenza, 
                                                        &LeggiCorrispondenzaDaFile, &HashId);
  funzioniIndiceCorr = (OPERAZIONI *)malloc(sizeof(OPERAZIONI));
  *funzioniIndiceCorr = InserisciFunzioni(&AllocaCorrispondenza, &StampaCorrispondenza, &ComparaCorrispondenzeIndice, 
                                                        &GestisciCollisioneCorrispondenze, &DeallocaCorrispondenza, 
                                                        &LeggiCorrispondenzaDaFile, &HashIndice);
                                                        
  //inizializzo la tabella delle corrispondenze
  grafo.corrisp = InizializzaCorrispondenze(dimensioneArray, funzioniIndiceCorr, funzioniIdCorr);

  //inizializzo il parametro della rappresentazione
  grafo.paramRappresentazione = funzioniGrafo.InizializzaParametroGrafo(grafo);


  //se ci sono meno vertici della dimensione dell'array inserisco gli eccedenti nella lista
  //dei blocchi liberi
  if(dimensioneArray > numVertici)
  {
    for(; numVertici < dimensioneArray; numVertici++)
      grafo.listaLiberi = PushLista(grafo.listaLiberi, (void *)numVertici);
  }
  return grafo;
}


//Inserisce un vertice nel grafo
//input: - GRAPH grafo: il grafo in cui inserire
//       - GRAPH_FUNC funzioniGrafo: le funzioni dipendenti dalla rappresentazione
//       - void *id: l'identificativo del nuovo nodo
//output: il grafo modificato
GRAPH InserisciVertice(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id)
{
  unsigned int nuovoIndice;
  CORRESPONDENCE *nuovaCorr;
  int i;
  
  grafo.numVertici++;
 
  //controllo se posso inserire in una posizione libera
  if(!ListaVuota(grafo.listaLiberi))
  {
    nuovoIndice = (unsigned int)/*forzo il cast ad intero*/PopLista(&grafo.listaLiberi);                                    
    
    //alloco memoria per il nuovo vertice ed assegno l'id
    grafo.vertici[nuovoIndice] = (GRAPH_NODE *)malloc(sizeof(GRAPH_NODE));
    (grafo.vertici[nuovoIndice])->id = id;
    (grafo.vertici[nuovoIndice])->colore = BIANCO;
    
    //alloco il parametro della rappresentazione
    grafo.paramRappresentazione = funzioniGrafo.InizializzaParametroVertice(grafo, nuovoIndice);

  }
  //se l'array è pieno lo ingrandisco e controllo se devo ottimizzare le corrispondenze
  else
  {
    nuovoIndice = grafo.numVertici - 1;
    
    //rialloco l'array dei vertici
    //aggiorno la dimensione dell'array
    grafo.dimensioneArray = (int)(grafo.dimensioneArray*INCR_FACT);
    grafo.vertici = (GRAPH_NODE **)realloc(grafo.vertici, grafo.dimensioneArray*sizeof(GRAPH_NODE *));
    
    //inizializzo tutti gli elementi nuovi 
    grafo.vertici[nuovoIndice] = (GRAPH_NODE *)malloc(sizeof(GRAPH_NODE));
    grafo.vertici[nuovoIndice]->id = id;
    grafo.paramRappresentazione = funzioniGrafo.InizializzaParametroVertice(grafo, nuovoIndice);
    
    for(i = grafo.numVertici; i < grafo.dimensioneArray; i++)
    {
      grafo.vertici[i] = NULL;
      //aggiungo alla lista dei vertici liberi i nuovi archi
      grafo.listaLiberi = PushLista(grafo.listaLiberi, (void *)i);
    }
  }
  //creo la corrispondenza ed inserisco l'elemento
  nuovaCorr = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
  nuovaCorr->id = id;
  nuovaCorr->indice = nuovoIndice;
  grafo.corrisp = InserisciCorrispondenza(grafo.corrisp, nuovaCorr, grafo.funzioniId);
  
  return grafo;
}


//Restituisce il vertice associato partendo dall'identificatore
//input: - GRAPH grafo: il grafo
//       - void *id: l'identificatore del vertice
//output: un puntatore al vertice o NULL se tale vertice non c'è
GRAPH_NODE *RecuperaVertice(GRAPH grafo, void *id)
{
  CORRESPONDENCE *corr;
  GRAPH_NODE *ret;
  //cerco la corrispondenza e ne ricavo il nodo nell'array di vertici
  corr = CercaCorrispondenzaId(grafo.corrisp, id, grafo.funzioniId);
  if(corr == NULL)
    ret = NULL;
  else
    ret = grafo.vertici[corr->indice];
  return ret;
}


//Cancella un vertice dal grafo
//input: - GRAPH grafo: il grafo in cui cancellare il vertice
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con la rappresentazione
//       - void *id: l'identificativo del nodo da cancellare
//output: il grafo modificato
GRAPH CancellaVertice(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id)
{
  CORRESPONDENCE *corr;
  unsigned int indice;
  int i;
  //se esiste un vertice con tale id lo si cancella
  if((corr = CercaCorrispondenzaId(grafo.corrisp, id, grafo.funzioniId)) != NULL)
  {
    //memorizzo l'indice ed elimino l'elemento dalla tabella corrispondenze
    indice = corr->indice;
    grafo.corrisp = CancellaCorrispondenza(grafo.corrisp, corr, grafo.funzioniId);
    
    //dealloco il parametro del vertice e la memoria da esso occupata
    grafo.paramRappresentazione = funzioniGrafo.DeallocaParametroVertice(grafo, indice);
    free(grafo.vertici[indice]);
    grafo.vertici[indice] = NULL;
    
    //inserisco l'indice nella lista degli elementi liberi
    grafo.listaLiberi = PushLista(grafo.listaLiberi, (void *)indice/*forzo la conversione a puntatore*/);
    
    //elimino l'arco di quell'indice da tutti i vertici rimasti
    for(i = 0; i < grafo.dimensioneArray; i++)
      if(grafo.vertici[i] != NULL)
        funzioniGrafo.CancellaArco(grafo, i, indice);
    //riduco il numer di vertici
    grafo.numVertici--;
    
    
    //se necessario riorganizzo i dati
    if(grafo.numVertici < (int)(MIN_TOL_DIM*grafo.dimensioneArray))
    {
      grafo = OttimizzaGrafo(grafo, funzioniGrafo);
    }
  }
  return grafo;
}


//Inserisce un arco in un grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione del grafo
//       - void *idVertice: l'id del vertice in cui inserire l'arco
//       - void *idArco: l'id del vertice bersaglio
//       - double peso: il peso dell'arco da inserire
//output: nessuno
void InserisciArco(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idVertice, void *idArco, double peso)
{
  CORRESPONDENCE *corr;
  GRAPH_ARC arco;
  //cerco l'id del vertice a cui l'arco punta
  corr = CercaCorrispondenzaId(grafo.corrisp, idArco, grafo.funzioniId);
  //se ho trovato la corrispondenza proseguo altrimenti nisba
  if(corr != NULL)
  {
    arco.indiceVertice = corr->indice;
    arco.peso = peso;
    //cerco l'indice del vertice a cui inserire
    corr = CercaCorrispondenzaId(grafo.corrisp, idVertice, grafo.funzioniId);
    //se anche quest'altro vertice esiste inserisco l'arco
    if(corr != NULL)
      grafo.paramRappresentazione = funzioniGrafo.InserisciArco(grafo, grafo.paramRappresentazione, corr->indice, arco);
  }
}


//Cancella un arco
//input - GRAPH grafo: il grafo in cui cancellare l'arco
//      - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//      - void *idVertice: l'identificativo del vertice a cui aggiungere l'arco
//      - void *idArco: l'identificativo del vertice a cui l'arco punta
//output: nessuno
void CancellaArco(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idVertice, void *idArco)
{
  CORRESPONDENCE *corr;
  unsigned int indiceVertice;
  //cerco l'id del vertice a cui aggiungere l'arco
  corr = CercaCorrispondenzaId(grafo.corrisp, idVertice, grafo.funzioniId);
  //se ho trovato la corrispondenza proseguo altrimenti nisba
  if(corr != NULL)
  {
    indiceVertice = corr->indice;
    //cerco l'indice del vertice bersaglio
    corr = CercaCorrispondenzaId(grafo.corrisp, idArco, grafo.funzioniId);
    //se anche quest'altro vertice esiste cancello l'arco
    if(corr != NULL)
      funzioniGrafo.CancellaArco(grafo, indiceVertice, corr->indice);
  }
}


//Ottimizza il grafo, riducendo la dimensione dell'array dei vertici, della
//tabella delle corrispondenze e dei parametri della rappresentazione
//input: - GRAPH grafo: il grafo da ottimizzare
//       - GRAPH_FUNC funzioniGrafo: le funzioni dipendenti dalla rappresentazione
//output: il grafo ottimizzato
GRAPH OttimizzaGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  int i, j;
  CORRESPONDENCE *corr;
  //inizializzo i due contatori ai due estremi
  i = -1;
  j = grafo.dimensioneArray;
  //finchè non si sono sovrapposti continuo a scambiare i valori
  while(i < j)
  {
    //cerco il primo elemento dell'array vuoto a sinistra dell'array
    do
    {
      i++;
    } while(grafo.vertici[i] != NULL && i < j);
    //una volta trovato cerco il primo elemento dell'array pieno a destra dell'array
    do
    {
      //decremento la dimensione dell'array in quanto dopo j ci sono valori insignificanti
      (grafo.dimensioneArray)--;
      j--;
    } while(grafo.vertici[j] == NULL && i < j);
    //controllo se gli indici sono ancora validi
    if(i < j)
    {
      //nel qual caso sposto il vertice j in posizione i e riduco il valore dimensioneArray
      grafo.vertici[i] = grafo.vertici[j];
      //modifico la corrispondenza dell'indice j assegnandole l'indice i
      //e rinserendola nella tabella
      ModificaIndiceCorrispondenza(grafo.corrisp, j, i);
      //ricalcolo i valori degli archi
      grafo = funzioniGrafo.OttimizzaArchi(grafo, j, i);
    }
  }
  (grafo.dimensioneArray)++;
  //realloco l'array (ora numVertici e dimensioneArray hanno lo stesso valore)
  grafo.vertici = (GRAPH_NODE **)realloc(grafo.vertici, grafo.dimensioneArray*sizeof(GRAPH_NODE *));
  //ottimizzo la tabella delle corrispondenze
  grafo.corrisp = OttimizzaCorrispondenze(grafo.corrisp, grafo.numVertici, grafo.funzioniId);

  //svuoto la lista degli indici liberi
  while(grafo.listaLiberi != NULL)
    PopLista(&grafo.listaLiberi);
  return grafo;
}


//Dealloca interamente un grafo
//input: - GRAPH grafo: il grafo da deallocare
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione
//                                   del grafo
//output: il grafo deallocato
GRAPH DeallocaGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  int i;
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    //dealloco la memoria occupata dal nodo
    if(grafo.vertici[i] != NULL)
      free(grafo.vertici[i]);
  }
  //libero la memoria dell'array di vertici ed azzero il puntatore nel grafo
  free(grafo.vertici);
  grafo.vertici = NULL;
  
  //dealloco la tabella delle corrispondenze
  grafo.corrisp = DeallocaCorrispondenze(grafo.corrisp, grafo.funzioniId);
  //dealloco il parametro della rappresentazione
  grafo.paramRappresentazione = funzioniGrafo.DeallocaParametroGrafo(grafo);
  //azzero le dimensioni
  grafo.numVertici = 0;
  grafo.dimensioneArray = 0;
  
  return grafo;
}


//Cambia la rappresentazione del grafo, consentendo
//di passare dalla rappresentazione a liste di adiacenza
//a quella a matrice e viceversa
//input: - GRAPH grafo: il grafo di cui cambiare la rappresentazione
//       - GRAPH_FUNC vecchiaRappr: le funzioni della vecchia rappresentazione
//       - GRAPH_FUNC nuovaRappr: le funzioni della nuova rappresentazione
//output: il grafo rappresentato alternativamente
GRAPH CambiaRappresentazione(GRAPH grafo, GRAPH_FUNC vecchiaRappr, GRAPH_FUNC nuovaRappr)
{
  void *nuovoParam;
  void *iter;
  GRAPH_ARC arco;
  int i;
  //inizializzo il nuovo parametro
  nuovoParam = nuovaRappr.InizializzaParametroGrafo(grafo);
  
  //scorro tutti i vertici e per ogni arco inserisco un arco nella nuova rappresentazione
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      //inizializzo l'iteratore per scorrere gli archi del vertice
      iter = vecchiaRappr.InizializzaIteratore(grafo, i);
      while(iter != NULL)
      {
        arco = vecchiaRappr.GetArcoSuccessivo(grafo, i, &iter);
        nuovoParam = nuovaRappr.InserisciArco(grafo, nuovoParam, i, arco);
      }
    }
  }
  //dealloco il vecchio parametro e carico il nuovo
  grafo.paramRappresentazione = vecchiaRappr.DeallocaParametroGrafo(grafo);
  grafo.paramRappresentazione = nuovoParam;
  
  return grafo;
}
