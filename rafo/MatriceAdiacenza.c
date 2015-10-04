/*
  LIBRERIA PER LA GESTIONE DI GRAFI
  Funzioni per la gestione di rappresentazioni
  di archi mediante matrice di adiacenza
  
  di Francesco Altiero, matr. 566/2258
  email: auronisback@hotmail.com             */

#include "include\MatriceAdiacenza.h"

//Inizializza la matrice di adiacenza
//input: GRAPH grafo: il grafo di cui inizializzare la matrice
//output: la matrice delle adiacenze
void *InizializzaParametroMatriceAdj(GRAPH grafo)
{
  double **matriceAdj;
  int i, j;

  //inizializzo la matrice
  matriceAdj = (double **)malloc(grafo.dimensioneArray*sizeof(double *));
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    matriceAdj[i] = (double *)malloc(grafo.dimensioneArray*sizeof(double));
    for(j = 0; j < grafo.dimensioneArray; j++)
      matriceAdj[i][j] = NESSUN_ARCO;
  }
  return matriceAdj;
}


//Se nel grafo è stato inserito un vertice di troppo modifico la matrice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice di cui inizializzare il parametro
//output: la matrice (modificata quando necessario)
void *InizializzaParametroVerticeMatriceAdj(GRAPH grafo, unsigned int indiceVertice)
{
  double **nuovaMatrice;
  int i, j;
  //se la lista degli spazi liberi è vuota ed i vertici sono minori degli spazi effettivi
  //(vuol dire che l'array dei vertici è stato reallocato e la lista dei liberi ancora non
  //aggiornata) allora rialloco la matrice inizializzando i nuovi valori a NESSUN_ARCO
  if(ListaVuota(grafo.listaLiberi) && grafo.dimensioneArray > grafo.numVertici)
  {
    nuovaMatrice = (double **)malloc(grafo.dimensioneArray*sizeof(double *));
    for(i = 0; i < grafo.dimensioneArray; i++)
    {
      nuovaMatrice[i] = (double *)malloc(grafo.dimensioneArray*sizeof(double));
      for(j = 0; j < grafo.dimensioneArray; j++)
      {
        //copio le righe valide ed inizializzo a 0 le altre
        if(i < grafo.numVertici-1 && j < grafo.numVertici-1)
          nuovaMatrice[i][j] = ((double **)grafo.paramRappresentazione)[i][j];
        else
          nuovaMatrice[i][j] = NESSUN_ARCO;
      }
    }
    //dealloco la vecchia matrice
    for(i = 0; i < grafo.numVertici; i++)
      free(((double **)grafo.paramRappresentazione)[i]);
    free((double **)grafo.paramRappresentazione);
  }
  //altrimenti il valore da ritornare non è altro che la vecchia matrice
  else
    nuovaMatrice = grafo.paramRappresentazione;
  return nuovaMatrice;
}


//Inserisce un arco nella matrice delle adiacenze relativamente al vertice
//input: - GRAPH grafo: il grafo
//       - void *paramRappr: il parametro della rappresentazione del grafo
//       - unsigned int indiceVertice: il vertice in cui inserire l'arco
//       - GRAPH_ARC arco: l'arco da inserire
//output: il valore NULL
void *InserisciArcoMatriceAdj(GRAPH grafo, void *paramRappr, unsigned int indiceVertice, GRAPH_ARC arco)
{
  if(indiceVertice < grafo.dimensioneArray && arco.indiceVertice < grafo.dimensioneArray)
    ((double **)paramRappr)[indiceVertice][arco.indiceVertice] = arco.peso;
  return paramRappr;
}


//Inizializza l'iteratore per lo scorrimento degli archi nella rappresentazione a matrice
//tale iteratore non è altro che un puntatore ad intero in cui memorizzare l'indice dell'ultimo
//arco letto (ossia dell'ultima colonna) relativa al vertice
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: l'indice del vertice a cui inizializzare l'iteratore
//output: un puntatore all'intero 0
void *InizializzaIteratoreMatriceAdj(GRAPH grafo, unsigned int indiceVertice)
{
  int *iter;
  iter = (int *)malloc(sizeof(int));
  *iter = 0;
    //porto l'iteratore al primo arco
  while(*iter < grafo.dimensioneArray && ((double **)grafo.paramRappresentazione)[indiceVertice][*iter] == NESSUN_ARCO)
    (*iter)++;
  //se non ci sono archi pongo l'iteratore a NULL
  if(*iter == grafo.dimensioneArray)
  {
    free(iter);
    iter = NULL;
  }
  return iter;
}


//Restituisce il primo arco non letto di un vertice
//necessita dell'iteratore
//input: - GRAPH grafo: il grafo, qui non utilizzato
//       - unsigned int indiceVertice: il vertice di cui leggere l'arco successivo, qui
//                                     non utilizzato ed inserito per specifiche
//       - void *iter: un puntatore all'iteratore                  
GRAPH_ARC GetArcoSuccessivoMatriceAdj(GRAPH grafo, unsigned int indiceVertice, void *iter)
{
  //salvo l'arco indicato dall'iteratore
  GRAPH_ARC arco;
  arco.peso = ((double **)grafo.paramRappresentazione)[indiceVertice][**(int **)iter];
  arco.indiceVertice = (**(int **)iter);
  
  //porto l'iteratore al prossimo arco
  (**(int **)iter)++;
  while(**(int **)iter < grafo.dimensioneArray && ((double **)grafo.paramRappresentazione)[indiceVertice][**(int **)iter] == NESSUN_ARCO)
    (**(int **)iter)++;
  //se gli archi sono finiti pongo l'iteratore a NULL
  if(**(int **)iter == grafo.dimensioneArray)
  {
    free(*(int *)iter);
    *(int **)iter = NULL;
  }
  return arco;
}


//Cerca un arco nella matrice delle adiacenze
//input: - GRAPH grafo: il grafo in cui cercare
//       - unsigned int indiceVertice: il vertice a cui eliminare l'arco
//       - unsigned int indiceArco: l'identificatore del nodo verso cui l'arco da eliminare punta
int EsisteArcoMatriceAdj(GRAPH grafo, unsigned int indiceVertice, unsigned int indiceArco)
{
  int ret;
  if(((double **)grafo.paramRappresentazione)[indiceVertice][indiceArco] == NESSUN_ARCO)
    ret = 0;
  else
    ret = 1;
  return ret;
}


//Ottimizza il parametro della rappresentazione
//utilizzato in caso di eccessiva disparità tra dimensione dell'array di vertici e
//dell'effettivo numero di vertici. Sposta la riga e la colonna di primoIndice sulla
//riga e sulla colonna secondoIndice
//input: - GRAPH grafo: il grafo
//       - unsigned int da: l'indice da cui stpostare
//       - unsigned int verso: l'indice verso cui spostare
//output: il grafo modificato
GRAPH OttimizzaArchiMatriceAdj(GRAPH grafo, unsigned int da, unsigned int verso)
{
  int i;
  //copio la riga
  ((double **)grafo.paramRappresentazione)[verso] = ((double **)grafo.paramRappresentazione)[da];
  //copio la colonna(fino al valore 'da' escluso)
  for(i = 0; i < da; i++)
    ((double **)grafo.paramRappresentazione)[i][verso] = ((double **)grafo.paramRappresentazione)[i][da];
  //copio l'elemento nella diagonale (che ora ha indici [verso][da])
  ((double **)grafo.paramRappresentazione)[verso][verso] = ((double **)grafo.paramRappresentazione)[verso][da];
  
  //rialloco la matrice
  grafo.paramRappresentazione = (double **)realloc(grafo.paramRappresentazione, grafo.dimensioneArray*sizeof(double *));
  for(i = 0; i < grafo.dimensioneArray; i++)
    ((double **)grafo.paramRappresentazione)[i] = 
                        (double *)realloc(((double **)grafo.paramRappresentazione)[i], grafo.dimensioneArray*sizeof(double));
  return grafo;
}


//Cancella un arco dalla matrice di adiacenza
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceNodo: il vertice a cui cancellare l'arco
//       - unsigned int indiceArco: l'indice del nodo a cui l'arco punta
//output: nessuno
void CancellaArcoMatriceAdj(GRAPH grafo, unsigned int dalVertice, unsigned int alVertice)
{
  //basta porre il rispettivo elemento della matrice al valore di nessun arco
  ((double **)grafo.paramRappresentazione)[dalVertice][alVertice] = NESSUN_ARCO;
}


//Traspone gli archi di un grafo
//input: - GRAPH grafo: il grafo i cui archi vanno trasposti
//       - GRAPH trasposto: il grafo verso cui trasporre gli archi
//output: il grafo trasposto
GRAPH TrasponiArchiMatriceAdj(GRAPH grafo, GRAPH trasposto)
{
  //basta trasporre la matrice
  int i, j;
  for(i = 0; i < grafo.dimensioneArray; i++)
  {
    for(j = i; j < grafo.dimensioneArray; j++)
    {
      ((double **)trasposto.paramRappresentazione)[j][i] = ((double **)grafo.paramRappresentazione)[i][j];
      ((double **)trasposto.paramRappresentazione)[i][j] = ((double **)grafo.paramRappresentazione)[j][i];
    }
  }
  return trasposto;
}


//Dealloca il parametro rappresentativo del nodo
//non fa niente
//input: - GRAPH grafo: il grafo
//       - unsigned int indiceVertice: il vertice di cui deallocare la lista
//output: la matrice modificata
void *DeallocaParametroVerticeMatriceAdj(GRAPH grafo, unsigned int indiceVertice)
{
  //cancello tutti gli archi che portano al vertice eliminato
  int i;
  for(i = 0; i < grafo.dimensioneArray; i++)
    ((double **)grafo.paramRappresentazione)[i][indiceVertice] = NESSUN_ARCO;
  //ritorno la matrice
  return grafo.paramRappresentazione;
}


//Dealloca la matrice delle adiacenze
//input: - GRAPH grafo: il grafo
//output: un puntatore a NULL
void *DeallocaParametroMatriceAdj(GRAPH grafo)
{
  int i;
  //dealloco tutte le righe della matrice
  for(i = 0; i < grafo.dimensioneArray; i++)
    free(((double **)grafo.paramRappresentazione)[i]);
  //dealloco l'array di puntatori alle precedenti righe
  free(grafo.paramRappresentazione);
  return NULL;
}
