/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni per la gestione dell'I/O di grafi
  per entrambe le rappresentazioni supportate
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "include\IOGrafo.h"

GRAPH LeggiGrafoDaFile(FILE *fp, GRAPH_FUNC funzioniGrafo, OPERAZIONI *funzioniId)
{
  unsigned int n;
  unsigned int verticiLetti;
  GRAPH grafo;
  //leggo la dimensione del grafo ed inizializzo
  if(fgetc(fp) == '(')
  {
    fscanf(fp, "%d", &n);

    grafo = InizializzaGrafo(n, n, funzioniGrafo, funzioniId);
    if(fgetc(fp) != ')')
      perror("[AVVISO]: carattere ')' mancante nella lettura della dimensione.");
    verticiLetti = LeggiVerticiDaFile(fp, grafo, funzioniGrafo, 0);
    //se ho letto meno vertici di quanto mi aspettavo lo comunico e riduco il numero dei vertici
    if(verticiLetti < n)
    {
      perror("[AVVISO]: l'intestazione del file dichiara più vertici di quanti effettivamente trovati nel file.");
      //inizializzo gli altri vertici
      for(; verticiLetti < grafo.dimensioneArray; verticiLetti++)
        grafo.vertici[verticiLetti] = NULL;
      //controllo la dimensione e se è eccessiva ottimizzo il grafo
      if(grafo.numVertici < MIN_TOL_DIM*grafo.dimensioneArray)
        grafo = OttimizzaGrafo(grafo, funzioniGrafo);
    }
  }
  else
    perror("[ERRORE]: carattere '(' mancante nella lettura della dimensione.");
  return grafo;
}


//Legge i vertici da un file e li memorizza
//input: - FILE *fp: il puntatore al file da cui leggere
//       - GRAPH grafo: il grafo da aggiornare
//       - GRAPH_FUNC funzioniGrafo: le funzioni utilizzate per la rappresentazione
//       - unisgned int ultimoIndice: l'ultimo nodo inserito nell'array di vertiti
//output: la posizione dell'ultimo vertice memorizzato nell'array dei vertici
unsigned int LeggiVerticiDaFile(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo, unsigned int ultimoIndice)
{
  char c;
  CORRESPONDENCE *corr;
  void *id;

  //se ho letto più nodi della dimensione letta nel file
  if(ultimoIndice > grafo.numVertici)
    perror("[ERRORE]:  ecceduto il numero inizialmente specificato di vertici.");
  else
  {
    //salto al primo carattere non bianco
    SaltaCaratteriBianchi(fp);
    c = fgetc(fp);
    //se non incontro un carattere di terminazione
    if(c != '.' && c != EOF)
    {
      UNO_INDIETRO(fp);
      id = (grafo.funzioniId)->LeggiDaInput(fp, grafo.funzioniId);
      //se la corrispondenza non è ancora stata inserita
      if((corr = CercaCorrispondenzaId(grafo.corrisp, id, grafo.funzioniId)) == NULL)
      {
        //inserisco la corrispondenza nella tabella
        corr = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
        corr->id = id;
        corr->indice = ultimoIndice;
        grafo.corrisp = InserisciCorrispondenza(grafo.corrisp, corr, grafo.funzioniId);
        
        //alloco ed aggiorno l'id del vertice
        grafo.vertici[corr->indice] = (GRAPH_NODE *)malloc(sizeof(GRAPH_NODE));
        (grafo.vertici[corr->indice])->id = corr->id;
        
        //aggiorno i parametri dipendenti dalla rappresentazione
        grafo.paramRappresentazione = funzioniGrafo.InizializzaParametroVertice(grafo, corr->indice);
        ultimoIndice++;
      }
      //altrimenti dealloco l'identificatore
      else
        free(id);
      //ora in corr ho la corrispondenza cercata
      //salto al carattere valido successivo
      SaltaCaratteriBianchi(fp);
      //se non trovo l'identificativo per le adiacenze lancio un errore
      if(fgetc(fp) != '-' || fgetc(fp) != '>')
        perror("[ERRORE]:  identificatore '->' per le adiacenze del vertice non trovato.");
      //altrimenti leggo le adiacenze del vertice di indice corr->indice
      else
      {
        SaltaCaratteriBianchi(fp);
        ultimoIndice = LeggiAdiacenzeDaFile(fp, grafo, corr->indice, funzioniGrafo, ultimoIndice);
      }
      //cerco altri vertici
      ultimoIndice = LeggiVerticiDaFile(fp, grafo, funzioniGrafo, ultimoIndice);
    }
  }
  return ultimoIndice;
}



//Legge gli archi da un file e li memorizza
//input: - FILE *fp: il puntatore al file da cui leggere
//       - GRAPH grafo: il grafo da cui leggere gli archi
//       - unsigned int indiceVertice: il vertice a cui aggiungere gli archi
//       - GRAPH_FUNC: le funzioni da utilizzare con la rappresentazione del grafo
//       - unsigned int ultimoIndice: l'ultimo nodo inserito nell'array
//output: la posizione dell'ultimo vertice memorizzato nell'array dei vertici
unsigned int LeggiAdiacenzeDaFile(FILE *fp, GRAPH grafo, unsigned int indiceVertice, GRAPH_FUNC funzioniGrafo, unsigned int ultimoIndice)
{
  char c;
  GRAPH_ARC arco;
  CORRESPONDENCE *corr;
  void *id;
  
  c = fgetc(fp);
  //se il grafo o il file sono terminati riavvolge il puntatore
  //e fa gestire la cosa alla funzione di lettura dei vertici
  if(c == '.' || c == EOF)
    UNO_INDIETRO(fp);
  //altrimenti se ho delle adiacenze da leggere
  else if(c != ';')
  {
    UNO_INDIETRO(fp);
    if(fgetc(fp) == '(')
    {    
    //leggo il peso
      SaltaCaratteriBianchi(fp);
      fscanf(fp, "%lf", &arco.peso);
      SaltaCaratteriBianchi(fp);
      //cerco la parentesi chiusa
      if(fgetc(fp) != ')')
      {
        perror("[AVVISO]: carattere di chiusura peso ')' non letto.");
        UNO_INDIETRO(fp);
      }
    }
    //se non leggo alcun peso assegno il peso di default
    else
    {
      arco.peso = PESO_DEFAULT;
      UNO_INDIETRO(fp);
    }
    //leggo l'id e cerco una corrispondenza già inserita in tabella a quel nome
    id = (grafo.funzioniId)->LeggiDaInput(fp, grafo.funzioniId);
    if((corr = CercaCorrispondenzaId(grafo.corrisp, id, grafo.funzioniId)) == NULL)
    {
      //se non trovo la corrispondenza ne creo una e la inserisco
      corr = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
      corr->id = id;
      corr->indice = ultimoIndice;
      
      grafo.corrisp = InserisciCorrispondenza(grafo.corrisp, corr, grafo.funzioniId);
      
      grafo.vertici[corr->indice] = (GRAPH_NODE *)malloc(sizeof(GRAPH_NODE));
      (grafo.vertici[corr->indice])->id = corr->id;
      
      grafo.paramRappresentazione = funzioniGrafo.InizializzaParametroVertice(grafo, corr->indice);
      ultimoIndice++;
    }
    //altrimenti dealloco l'identificatore letto
    else 
      free(id);
    //ora in corr ho la corrispondenza cercata
    //completo l'arco e lo inserisco
    arco.indiceVertice = corr->indice;
    grafo.paramRappresentazione = funzioniGrafo.InserisciArco(grafo, grafo.paramRappresentazione, indiceVertice, arco);
    
    //leggo la prossima adiacenza
    SaltaCaratteriBianchi(fp);
    ultimoIndice = LeggiAdiacenzeDaFile(fp, grafo, indiceVertice, funzioniGrafo, ultimoIndice);
  }
  return ultimoIndice;
}



//Stampa il grafo
//input: - GRAPH grafo: il grafo da stampare
//       - GRAPH_FUNC funzioniGrafo: le funzioni per la gestione della rappresentazione
//output: nessuno
void ScriviGrafo(FILE *fp, GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  int i;
  void *iter; //l'iteratore per scorrere gli archi, dipendente dalla rappresentazione
  GRAPH_ARC arco;
  CORRESPONDENCE *corr;
  //scrivo la dimensione
  fprintf(fp, "(%u) ", grafo.numVertici);
  //per tutti i vertici del grafo
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    //controllo se il nodo è valido
    if(grafo.vertici[i] != NULL)
    {
      //stampo l'id del vertice
      (grafo.funzioniId)->StampaDato(fp, (grafo.vertici[i])->id, grafo.funzioniId);
      fprintf(fp, " -> ");
      //leggo tutti gli archi del vertice e li stampo
      iter = funzioniGrafo.InizializzaIteratore(grafo, i);
      while(iter != NULL)
      {
        arco = funzioniGrafo.GetArcoSuccessivo(grafo, i, &iter);
        if(arco.peso != PESO_DEFAULT)
          fprintf(fp, "(%.2lf)", arco.peso);
        (grafo.funzioniId)->StampaDato(fp, (grafo.vertici[arco.indiceVertice])->id, grafo.funzioniId);
        fputc(' ', fp);
      }
      fprintf(fp, ";\n");
    }
  }
  //alla fine scrivo un bel punto ed un newline
  fputc('.', fp);
  fputc('\n', fp);
}


//Salta caratteri nel file fino al primo non bianco
//in modo che il successivo carattere letto nel file sia
//diverso da ' ' e da una newline
//input: FILE *fp: il file da cui leggere
//output: nessuno
void SaltaCaratteriBianchi(FILE *fp)
{
  char c;
  //salto tutti i caratteri bianchi fino a trovarne uno differente
  c = fgetc(fp);
  while(c == ' ' || c == '\n')
    c = fgetc(fp);
  //riavvolgo di un carattere il puntatore al file
  UNO_INDIETRO(fp);
}

