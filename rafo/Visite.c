/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni per visite e trasposizioni di grafi
  per entrambe le rappresentazioni supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "include\Visite.h"


//Funzione di interfaccia per la visita BFS
//Chiama la visita BFS utilizzando come parametro l'id del vertice
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - void *sorgente: l'identificatore del vertice sorgente
//output: nessuno
void BFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *id)
{
  CORRESPONDENCE *corr;
  //cerco l'indice del vertice sorgente
  corr = CercaCorrispondenzaId(grafo.corrisp, id, grafo.funzioniId);
  if(corr != NULL)
    BFScore(grafo, funzioniGrafo, corr->indice);
}


//Effettua una visita BFS per calcolare i percorsi minimi da una sorgente
//input: - GRAPH grafo: il grafo da visitare
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - unsigned int indiceSorgente: l'indice del vertice sorgente
//output: nessuno
void BFScore(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int sorgente)
{
  unsigned int analizzato;
  unsigned int adiacente;
  GRAPH_ARC arco;
  QUEUE codaVertici;
  void *iter;
  int i;
  
  //inizializzo i vertici
  for(i = 0; i < grafo.dimensioneArray; i++)
    if(grafo.vertici[i] != NULL)
    {
      (grafo.vertici[i])->colore = BIANCO;
      (grafo.vertici[i])->predecessore = NESSUNO;
      (grafo.vertici[i])->distanza = NON_SCOPERTO;
    }
  
  //comincio ad elaborare la sorgente
  (grafo.vertici[sorgente])->colore = GRIGIO;
  (grafo.vertici[sorgente])->distanza = 0;
  (grafo.vertici[sorgente])->predecessore = NESSUNO;
  
  //inserisco la sorgente nella coda e comincio la visita
  codaVertici = InizializzaCoda(codaVertici);
  codaVertici = Accoda(codaVertici, (void *)/*forzo il cast*/sorgente);
  
  while(!CodaVuota(codaVertici))
  {
    //estraggo un vertice dalla coda
    analizzato = (unsigned int)Decoda(&codaVertici);
    //inizializzo l'iteratore per leggere i vertici adiacenti del nodo
    iter = funzioniGrafo.InizializzaIteratore(grafo, analizzato);
    //finchè ci sono vertici da leggere li elabora
    while(iter != NULL)
    {
      arco = funzioniGrafo.GetArcoSuccessivo(grafo, analizzato, &iter);
      //cerco il vertice a cui l'arco punta
      //se non è ancora stato visitato lo elaboro e lo accodo 
      adiacente = arco.indiceVertice;
      if((grafo.vertici[adiacente])->colore == BIANCO)
      {
        (grafo.vertici[adiacente])->colore = GRIGIO;
        (grafo.vertici[adiacente])->distanza = (grafo.vertici[analizzato])->distanza + 1;
        (grafo.vertici[adiacente])->predecessore = analizzato;
        codaVertici = Accoda(codaVertici, (void *)/*forzo anche qui*/adiacente);
      }
    }
    //completata la visita del vertice
    (grafo.vertici[analizzato])->colore = NERO;
  }
}


//Effettua una DFS sul grafo per calcoare i tempi di scoperta e di completamento
//dei vertici del grafo
//input: - GRAPH grafo: il grafo da visitare
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione
//output: nessuno
void DFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  int i;
  
  //inizializzo i vertici
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      (grafo.vertici[i])->colore = BIANCO;
      (grafo.vertici[i])->predecessore = NESSUNO;
      (grafo.vertici[i])->scoperta = NON_SCOPERTO;
      (grafo.vertici[i])->completamento = NON_SCOPERTO;
    }
  }
  
  //inizializzo la variabile globale del tempo
  tempoDFS = 0;
  
  //scorro tutti i vertici e chiamo la visita DFS su ognuno di essi (che sia ancora bianco)
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      if((grafo.vertici[i])->colore == BIANCO)
        VisitaDFS(grafo, funzioniGrafo, i);
    }
  }
}


//Effettua la visita in profondità su un vertice. Chiamata dalla funzione DFS
//input: - GRAPH grafo: il grafo che si sta visitando
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - unsigned int indiceSorgente: l'indice della sorgente
//output: nessuno
void VisitaDFS(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int indiceSorgente)
{
  void *iter;
  GRAPH_ARC arco;
  unsigned int adiacente;
  
  //inizializzo l'iteratore
  iter = funzioniGrafo.InizializzaIteratore(grafo, indiceSorgente);

  //incremento il tempo
  tempoDFS++;
  
  //inizializzo la sorgente
  (grafo.vertici[indiceSorgente])->scoperta = tempoDFS;
  (grafo.vertici[indiceSorgente])->colore = GRIGIO;
  
  //se ci sono altri elementi adiacenti da leggere
  while(iter != NULL)
  {
    //leggo l'arco successivo
    arco = funzioniGrafo.GetArcoSuccessivo(grafo, indiceSorgente, &iter);
    //cerco il vertice a cui punta l'arco letto
    adiacente = arco.indiceVertice;
    //se non è stato ancora visitato, lo visito
    if((grafo.vertici[adiacente])->colore == BIANCO)
    {
      (grafo.vertici[adiacente])->predecessore = indiceSorgente;
      //chiamo ricorsivamente la visita in profondità
      VisitaDFS(grafo, funzioniGrafo, adiacente);
    }
  }
  //completo la sorgente e ne aggiorno il tempo
  (grafo.vertici[indiceSorgente])->colore = NERO;
  tempoDFS++;
  (grafo.vertici[indiceSorgente])->completamento = tempoDFS;
}


//Calcola il grafo trasposto
//input: - GRAPH grafo: il grafo da trasporre
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con il grafo
//output: il grafo trasposto
GRAPH TrasponiGrafo(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  GRAPH trasposto;
  CORRESPONDENCE *corr, *corrTrasposto;
  int i;
  
  //inizializzo il grafo trasposto ed aggiorno il numero di vertici
  trasposto = InizializzaGrafo(grafo.numVertici, grafo.dimensioneArray, funzioniGrafo, grafo.funzioniId);
  trasposto.numVertici = grafo.numVertici;
  
  //estraggo gli elementi delle corrispondenze ricalcolando i codici ed inserendoli nella nuova
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
      //cerco progressivamente le corrispondenze con il loro indice
      corr = CercaCorrispondenzaIndice(grafo.corrisp, i);
      if(corr != NULL)
      {
        //ogni volta che ne trovo una alloco la nuova corrispondenza, le alloco un nuovo identificatore,
        //le assegno l'indice e la inserisco nella tabella delle corrispondenze
        corrTrasposto = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
        corrTrasposto->id = (trasposto.funzioniId)->AllocaDato(corr->id, trasposto.funzioniId);
        corrTrasposto->indice = i;
        trasposto.corrisp = InserisciCorrispondenza(trasposto.corrisp, corrTrasposto, trasposto.funzioniId);
        
        //alloco la memoria per il nodo corrispondente ed inizializzo il parametro del vertice
        trasposto.vertici[i] = (GRAPH_NODE *)malloc(sizeof(GRAPH_NODE));
        (trasposto.vertici[i])->id = corrTrasposto->id;
        trasposto.paramRappresentazione = funzioniGrafo.InizializzaParametroVertice(trasposto, i);
      }
      //altrimenti azzero il nodo corrispondente
      else
        trasposto.vertici[i] = NULL;
  }
  //chiamo il gestore della trasposizione degli archi dipendente dalla rappresentazione
  trasposto = funzioniGrafo.TrasponiArchi(grafo, trasposto);
  
  //alfine ritorno il grafo trasposto
  return trasposto;
}


//Cerca cicli nel grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: 1 se il grafo contiene cicli, 0 altrimenti
int ContieneCicli(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  int i;
  int ret;
  ret = 0;
  //inizializzo i vertici
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    if(grafo.vertici[i] != NULL)
    {
      (grafo.vertici[i])->colore = BIANCO;
      (grafo.vertici[i])->predecessore = NESSUNO;
      (grafo.vertici[i])->scoperta = NON_SCOPERTO;
      (grafo.vertici[i])->completamento = NON_SCOPERTO;
    }
  }
  
  i = 0;
  //scorro i vertici del grafo fino ad esaurimento o fino a trovare un ciclo
  while(i < grafo.dimensioneArray && ret == 0)
  {
    if(grafo.vertici[i] != NULL)
      //visito il successivo vertice bianco e vedo se ci sono cicli
      if((grafo.vertici[i])->colore == BIANCO)
        ret = VisitaContieneCicli(grafo, funzioniGrafo, i);
    
    //leggiamo l'elemento successivo
    i++;
  }
  return ret;
}


//Cerca cicli da un vertice sorgente
//effettua una visita in profondità sul vertice per cercare vertici grigi
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//       - unsigned int indiceSorgente: la sorgente della visita
//output: 1 se il grafo contiene cicli, 0 altrimenti
int VisitaContieneCicli(GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int indiceSorgente)
{
  int ret;
  void *iter;
  GRAPH_ARC arco;
  unsigned int adiacente;
  ret = 0;
  //inizializzo l'iteratore
  iter = funzioniGrafo.InizializzaIteratore(grafo, indiceSorgente);
  
  //inizializzo la sorgente
  (grafo.vertici[indiceSorgente])->scoperta = tempoDFS;
  (grafo.vertici[indiceSorgente])->colore = GRIGIO;
  
  //se ci sono altri elementi adiacenti da leggere ed il ciclo non
  //è stato finora trovato
  while(iter != NULL && ret == 0)
  {
    //leggo l'arco successivo
    arco = funzioniGrafo.GetArcoSuccessivo(grafo, indiceSorgente, &iter);
    //cerco il vertice a cui punta l'arco letto
    adiacente = arco.indiceVertice;
    //se non è stato ancora visitato, lo visito
    if((grafo.vertici[adiacente])->colore == BIANCO)
    {
      (grafo.vertici[adiacente])->predecessore = indiceSorgente;
      //chiamo ricorsivamente la visita in profondità
      ret = VisitaContieneCicli(grafo, funzioniGrafo, adiacente);
    }
    //se invece il colore del vertice è grigio, allora è un arco di
    //ritorno e c'è un ciclo nel grafo
    else if((grafo.vertici[adiacente])->colore == GRIGIO)
      ret = 1;
  }
  //completo la sorgente
  (grafo.vertici[indiceSorgente])->colore = NERO;
  return ret;
}


//Funzione di interfaccia per stampare un cammino tra vertici fornendo due identificatori
//chiama la funzione ScriviCamminoCore che effettua tale verifica
//input: - FILE *fp: l'output su cui scrivere
//       - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - void *idPartenza: l'identificatore del nodo da cui partire
//       - void *idArrivo: l'identificatore del nodo di arrivo
//output: nessuno
void ScriviCammino(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, void *idPartenza, void *idArrivo)
{
  int indicePartenza;
  CORRESPONDENCE *corr;
  
  //cerco il vertice di partenza
  corr = CercaCorrispondenzaId(grafo.corrisp, idPartenza, grafo.funzioniId);
  if(corr != NULL)
  {
    indicePartenza = corr->indice;
    //cerco il vertice di arrivo
    corr = CercaCorrispondenzaId(grafo.corrisp, idArrivo, grafo.funzioniId);
    if(corr != NULL)
      //se ho trovato anche il secondo vertice chiamo la funzione per scrivere
      ScriviCamminoCore(fp, grafo, funzioniGrafo, indicePartenza, corr->indice);
    else
      perror("[ERRORE]: Vertice di arrivo non trovato.\n");
  }
  else
    perror("[ERRORE]: Vertice di partenza non trovato.\n");
}

//Scrive un cammino da due vertici del grafo
//input: - FILE *fp: l'output su cui scrivere
//       - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni di rappresentazione del grafo
//       - unsigned int partenza: il vertice da cui partire
//       - unsigned int arrivo: il vertice finale
//output: nessuno
void ScriviCamminoCore(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int partenza, unsigned int arrivo)
{
  CORRESPONDENCE *corr;
  //se non è stata chiamata una visita con il vertice di partenza come sorgente chiamo una BFS sul vertice
  if((grafo.vertici[partenza])->distanza != 0)
    BFScore(grafo, funzioniGrafo, partenza);
    
  //se siamo arrivati al vertice finale lo si stampa
  if(partenza == arrivo)
    (grafo.funzioniId)->StampaDato(fp, (grafo.vertici[partenza])->id, grafo.funzioniId);
  //se siamo arrivati alla sorgente stampa un messaggio di errore
  else if((grafo.vertici[arrivo])->predecessore == NESSUNO)
    fprintf(fp, "Nessun percorso tra i due vertici\n");
  //altrimenti continua a scorrere ricorsivamente l'albero dei predecessori
  else
  {
    ScriviCamminoCore(fp, grafo, funzioniGrafo, partenza, (grafo.vertici[arrivo])->predecessore);
    fputc(' ', fp);
    (grafo.funzioniId)->StampaDato(fp, (grafo.vertici[arrivo])->id, grafo.funzioniId);
  }
}
