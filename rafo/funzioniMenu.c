/* FUNZIONI DEI MENU RICHIAMATE DAL MAIN
   per la gestione di grafi

   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com     */

#include "include\funzioniMenu.h"

//Stampa il menù principale.
//input: - LIST arrayListe[]: il vettore di liste da gestire
//       - OPERAZIONI arrayFun[]: il vettore delle operazioni rispettive di ogni lista
//output: nessuno
void StampaMenuPrincipale(OPERAZIONI *funzioniId)
{
  char scelta;
  char nomefile[DIM];

  char str1[DIM];
  char str2[DIM];

  GRAPH grafo;
  GRAPH_FUNC funzioniLista;
  GRAPH_FUNC funzioniMatrice;
  GRAPH_FUNC *funzioniAttuali;
  
  FILE *fp;
  
  //inserisco le funzioni per entrambe le rappresentazioni
  funzioniLista = InserisciFunzioniRappresentazione(&InizializzaParametroListaAdj, &InizializzaParametroVerticeListaAdj,
                                                    &InserisciArcoListaAdj, &InizializzaIteratoreListaAdj, &GetArcoSuccessivoListaAdj,
                                                    &EsisteArcoListaAdj, &OttimizzaArchiListaAdj, &CancellaArcoListaAdj,
                                                    &TrasponiArchiListaAdj, &DeallocaParametroVerticeListaAdj, &DeallocaParametroListaAdj);
  funzioniMatrice = InserisciFunzioniRappresentazione(&InizializzaParametroMatriceAdj, &InizializzaParametroVerticeMatriceAdj,
                                                    &InserisciArcoMatriceAdj, &InizializzaIteratoreMatriceAdj, &GetArcoSuccessivoMatriceAdj,
                                                    &EsisteArcoMatriceAdj, &OttimizzaArchiMatriceAdj, &CancellaArcoMatriceAdj,
                                                    &TrasponiArchiMatriceAdj, &DeallocaParametroVerticeMatriceAdj, &DeallocaParametroMatriceAdj);

  //faccio scegliere la rappresentazione iniziale                                                 
  printf("LIBRERIA PER LA GESTIONE DI GRAFI\nfunzioni per identificatori di tipo stringa\n\n");
  printf("Rappresentazioni:\n");
  printf("  1 - Liste di adiacenza\n");
  printf("  2 - Matrice di adiacenza\n");
  printf("\nQuale rappresentazione utilizzare? ");
  scelta = getch();
  while(scelta != '1' && scelta != '2')
  {
    printf("Valore non contemplato. Riprovare...\n");
    scelta = getch();
  }
  
  putchar('\n');
  
  //carico le funzioni
  if(scelta == '1')
    funzioniAttuali = &funzioniLista;
  else
    funzioniAttuali = &funzioniMatrice;
  
  //chiedo di inserire un grafo da file o di crearne uno nuovo
  do
  {
    printf("Inserire il nome del file da cui caricare il grafo (invio per non darne):\n");
    gets(nomefile);
  
    //se non si specificano file
    if(nomefile[0] == '\0')
      fp = stdin;
    else
    {
      fp = fopen(nomefile, "r");
      if(fp == NULL)
        printf("File non trovato!\n");
    }
  } while(fp == NULL);
  
  
  //se necessario carico il grafo da file, altrimenti ne inizializzo uno vuoto
  if(fp == stdin)
    grafo = InizializzaGrafo(0, 1, *funzioniAttuali, funzioniId);
  else
    grafo = LeggiGrafoDaFile(fp, *funzioniAttuali, funzioniId);
  
  //stampo il menù principale
  system("cls");
  while(scelta != '0')
  {
    printf("\nGESTIONE DI GRAFI\nMenu' principale\n\n");
    printf("  1 - I/O Grafo\n");
    printf("  2 - Modifica Grafo\n");
    printf("  3 - Visite ed operazioni\n");
    printf("  4 - Cambia rappresentazione\n");
    printf("  0 - Uscita\n\n");
    printf("Rappresentazione attuale: ");
    if(funzioniAttuali == &funzioniLista)
      printf("Liste di adiacenza\n");
    else
      printf("Matrice di adiacenza\n");
    printf("Scegliere l'operazione da effettuare: \n");
    scelta = getch();

    //a seconda della scelta vengono passate alla funzione di gestione la lista, sue relative funzioni di gestione
    //e le funzioni di input (da tastiera, da file e casuale) per il tipo di dato in questione.
    //la lista selezionata verrà inoltre modificata al ritorno della funzione
    if(scelta == '1')
    {
      //carica il gestore delle funzioni di IO
      grafo = FunzioniIO(grafo, *funzioniAttuali);
    }
    else if(scelta == '2')
    {
      grafo = FunzioniModifica(grafo, *funzioniAttuali);
    }
    else if(scelta == '3')
    {
      grafo = FunzioniVisite(grafo, *funzioniAttuali);
    }
    else if(scelta == '4')
    {
      //controllo le funzioni di rappresentazioni attuali e cambio la rappresentazione
      if(funzioniAttuali == &funzioniLista)
      {
        grafo = CambiaRappresentazione(grafo, *funzioniAttuali, funzioniMatrice);
        funzioniAttuali = &funzioniMatrice;
      }
      else
      {
        grafo = CambiaRappresentazione(grafo, *funzioniAttuali, funzioniLista);
        funzioniAttuali = &funzioniLista;
      }
      system("cls");
    }
    else if(scelta != '0')
    {
      printf("Scelta %c\n", scelta);
      printf("\nValore non contemplato\n");
    }
  }
  grafo = DeallocaGrafo(grafo, *funzioniAttuali);
}


//Stampa il menù per la gestione dell'I/O del grafo
//input: - GRAPH *grafo: un puntatore al grafo su cui operare
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: un valore intero che determinerà la fine delle operazioni di IO
GRAPH FunzioniIO(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  char scelta;
  char nomefile[DIM];
  FILE *fp;
  void *param;
  
  scelta = 1;
  while(scelta != '0')
  {
    //stampo il menù di IO
    printf("\nGESTIONE DI GRAFI\nMenu' I\\O\n\n");
    printf("  1 - Stampa Grafo\n");
    printf("  2 - Scrivi Grafo su file\n");
    printf("  3 - Carica un altro Grafo\n");
    printf("  0 - Ritorna al menu principale\n\n");
    printf("Selezionare un'operazione: ");
    scelta = getch();
  
    //elaboro le scelte
    if(scelta == '1')
    {
      system("cls");
      ScriviGrafo(stdout, grafo, funzioniGrafo);
    }
    else if(scelta == '2')
    {
      putchar('\n');
      printf("Inserire il nome del file di output: ");
      gets(nomefile);
      fp = fopen(nomefile, "w");
      if(fp == NULL)
        printf("Errore nell'apertura del file!\n");
      else
        ScriviGrafo(fp, grafo, funzioniGrafo);
    }
    else if(scelta == '3')
    {
      putchar('\n');
      printf("Inserisci il nome del file da cui caricare il nuovo grafo: ");
      gets(nomefile);
      fp = fopen(nomefile, "r");
      if(fp == NULL)
        printf("\nErrore nell'apertura del file!\n");
      else
      {
        param = grafo.funzioniId;
        grafo = DeallocaGrafo(grafo, funzioniGrafo);
        grafo = LeggiGrafoDaFile(fp, funzioniGrafo, param);
      }
    }
    else if(scelta != 0)
      printf("Scelta non contemplata\n");
  }
  return grafo;
}

//Stampa il menù per le modifiche del grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con la rappresentazione
//output: il grafo modificato
GRAPH FunzioniModifica(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  char str1[DIM];
  char str2[DIM];
  char scelta;
  double peso;
  
  scelta = '1';
  while(scelta != '0')
  {
    printf("\nGESTIONE DI GRAFI\nMenu' Modifiche\n\n");
    printf("  1 - Aggiungi Vertice\n");
    printf("  2 - Aggiungi Arco\n");
    printf("  3 - Cancella Vertice\n");
    printf("  4 - Cancella Arco\n");
    printf("  0 - Ritorna al menu principale\n\n");
    printf("Selezionare un'operazione: ");
    scelta = getch();
    
    //elaboro le scelte
    if(scelta == '1')
    {
      putchar('\n');
      printf("Inserisci l'identificatore del nuovo vertice: ");
      scanf("%s", str1);
      grafo = InserisciVertice(grafo, funzioniGrafo, AllocaStringa(str1, NULL));
    }
    else if(scelta == '2')
    {
      putchar('\n');
      printf("Inserire l'identificatore del vertice da cui parte l'arco: ");
      scanf("%s", str1);
      printf("Inserire l'identificatore del vertice a cui l'arco punta: ");
      scanf("%s", str2);
      printf("Inserisci il peso dell'arco: ");
      scanf("%lf", &peso);
      InserisciArco(grafo, funzioniGrafo, str1, str2, peso);
    }
    else if(scelta == '3')
    {
      putchar('\n');
      printf("Inserire l'identificatore del vertice da cancellare: ");
      scanf("%s", str1);
      grafo = CancellaVertice(grafo, funzioniGrafo, str1);
    }
    else if(scelta == '4')
    {
      putchar('\n');
      printf("Inserire l'identificatore del vertice da cui parte l'arco: ");
      scanf("%s", str1);
      printf("Inserire l'identificatore del vertice a cui l'arco punta: ");
      scanf("%s", str2);
      CancellaArco(grafo, funzioniGrafo, str1, str2);
    }
    else if(scelta != 0)
      printf("Scelta non contemplata\n");
  }
  return grafo;
}


//Gestisce il menu per le visite sul grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: il grafo modificato
GRAPH FunzioniVisite(GRAPH grafo, GRAPH_FUNC funzioniGrafo)
{
  char str1[DIM];
  char str2[DIM];
  char scelta;
  GRAPH trasposto;
  CORRESPONDENCE *corr;
  int tmp;
  
  scelta = '1';
  while(scelta != '0')
  {
    printf("\nGESTIONE DI GRAFI\nMenu' Modifiche\n\n");
    printf("  1 - Visita BFS\n");
    printf("  2 - Visita DFS\n");
    printf("  3 - Stampa percoso tra vertici\n");
    printf("  4 - Calcola e stampa Grafo Trasposto\n");
    printf("  5 - Controlla la presenza di cicli\n");
    printf("  0 - Ritorna al menu principale\n\n");
    printf("Selezionare un'operazione: ");
    scelta = getch();
    
    //elaboro le scelte
    if(scelta == '1')
    {
      putchar('\n');
      printf("Inserisci l'identificativo della sorgente: ");
      gets(str1);
      //cerco la corrispondenza ed effettuo la visita
      BFS(grafo, funzioniGrafo, str1);
    }
    else if(scelta == '2')
    {
      DFS(grafo, funzioniGrafo);
      printf("DFS effettuata\n");
      system("PAUSE");
    }
    else if(scelta == '3')
    {
      putchar('\n');
      printf("Inserire l'identificatore del vertice di partenza: ");
      scanf("%s", str1);
      printf("Inserire l'identificatore del vertice di arrivo: ");
      scanf("%s", str2);
      ScriviCammino(stdout, grafo, funzioniGrafo, str1, str2);
      putchar('\n');
    }
    else if(scelta == '4')
    {
      putchar('\n');
      trasposto = TrasponiGrafo(grafo, funzioniGrafo);
      ScriviGrafo(stdout, trasposto, funzioniGrafo);
    }
    else if(scelta == '5')
    {
      putchar('\n');
      if(ContieneCicli(grafo, funzioniGrafo))
        printf("Il grafo presenta cicli.\n");
      else
        printf("Non ci sono cicli nel grafo.\n");
    }
    else if(scelta != 0)
      printf("Scelta non contemplata\n");
  }
  return grafo;
}
