/* 
   FUNZIONI DI GESTIONE DI TABELLE DI CORRISPONDENZA
   Funzioni per la gestione di corrispondenze del tipo
   intero/generico strutturate mediante una doppia tabella
   hash concatenata per l'indicizzazione su entrambi i valori
   indice/identificatore 
   
   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com                             */

#include "include\Corrispondenze.h"


//Inizializza la tabella delle corrispondenze
//input: - unsigned int dimensione: la dimensione della tabella
//       - OPERAZIONI *funzioniCorrIndice: le funzioni per la corrispondenza degli indici
//       - OPERAZIONI *funzioniCorrId: le funzioni per la corrispondenza degli id
//output: una tabella delle corrispondenze nuova
CORR_TABLE InizializzaCorrispondenze(unsigned int dimensione, OPERAZIONI *funzioniCorrIndice, OPERAZIONI *funzioniCorrId)
{
  CORR_TABLE tabellaCorr;
  int i;
  //modifico le dimensioni delle due sottotabelle hash
  tabellaCorr.corrIndice.dimensione = dimensione;
  tabellaCorr.corrId.dimensione = dimensione;
  
  //memorizzo le funzioni delle due tabelle
  tabellaCorr.corrIndice.funzioniLista = funzioniCorrIndice;
  tabellaCorr.corrId.funzioniLista = funzioniCorrId;
  
  //inizializzo entrambe le tabelle
  tabellaCorr.corrIndice.tabella = (LIST *)malloc(dimensione*sizeof(LIST));
  tabellaCorr.corrId.tabella = (LIST *)malloc(dimensione*sizeof(LIST));
  for(i = 0; i < tabellaCorr.corrId.dimensione; i++)
  {
    if(i < dimensione)
      tabellaCorr.corrIndice.tabella[i] = InizializzaLista();
    tabellaCorr.corrId.tabella[i] = InizializzaLista();
  }

  return tabellaCorr;
}


//Inserisce un elemento nella tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - CORRESPONDENCE *corrispondenza: la corrispondenza da inserire
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE InserisciCorrispondenza(CORR_TABLE tabellaCorr, CORRESPONDENCE *corrispondenza, OPERAZIONI *funzioniId)      
{
  //inserisco l'elemento nella prima tabella
  tabellaCorr.corrId = InserisciElementoTabella(tabellaCorr.corrId, corrispondenza, funzioniId);
  //e lo inserisco nella seconda
  tabellaCorr.corrIndice = InserisciElementoTabella(tabellaCorr.corrIndice, corrispondenza, funzioniId);
  return tabellaCorr;
}


//Cancella un elemento dalla tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - CORRESPONDENCE *corrispondenza: la corrispondenza da eliminare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE CancellaCorrispondenza(CORR_TABLE tabellaCorr, CORRESPONDENCE *corrispondenza, OPERAZIONI *funzioniId)
{
  void *scambio;
  //cambio momentaneamente la funzione di deallocazione della tabella hash degli id
  scambio = (tabellaCorr.corrId.funzioniLista)->DeallocaDato;
  (tabellaCorr.corrId.funzioniLista)->DeallocaDato = &FunzionePigra;
  
  //cancello il primo nodo dalla lista
  CancellaDallaTabella(tabellaCorr.corrId, corrispondenza, funzioniId);
  //ripristino le funzioni così com'erano
  (tabellaCorr.corrId.funzioniLista)->DeallocaDato = scambio;
  
  //adesso cancello il dato dall'altra lista, deallocandolo al solito
  CancellaDallaTabella(tabellaCorr.corrIndice, corrispondenza, funzioniId);
  
  return tabellaCorr;
}


//Cerca un elemento nella tabella delle corrispondenze fornendo l'indice
//input: - CORR_TABLE tabellaCorr: la tabella in cui cercare
//       - unsigned int indice: l'indice da ricercare
//output: un puntatore all'elemento della tabella desiderato o NULL se tale
//        elemento non esiste
CORRESPONDENCE *CercaCorrispondenzaIndice(CORR_TABLE tabellaCorr, unsigned int indice)
{
  //creo una corrispondenza dall'id e la cerco nella tabella ritornando il valore
  CORRESPONDENCE tmp;
  tmp.indice = indice;
  return CercaNellaTabella(tabellaCorr.corrIndice, &tmp, NULL);
}

//Cerca un elemento nella tabella delle corrispondenze fornendo l'identificatore
//input: - CORR_TABLE tabellaCorr: la tabella in cui cercare
//       - void *id: l'identificatore da ricercare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: un puntatore all'elemento della tabella desiderato o NULL se tale
//        elemento non esiste
CORRESPONDENCE *CercaCorrispondenzaId(CORR_TABLE tabellaCorr, void *id, OPERAZIONI *funzioniId)
{
  //creo una corrispondenza dall'id e la cerco nella tabella ritornando il valore
  CORRESPONDENCE tmp;
  tmp.id = id;
  return CercaNellaTabella(tabellaCorr.corrId, &tmp, funzioniId);
}


//Stampa sull'output fornito la tabella delle corrispondenze
//input: - FILE *fp: l'output su cui stampare
//       - CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli id
//output: nessuno
void StampaCorrispondenze(FILE *fp, CORR_TABLE tabellaCorr, OPERAZIONI *funzioniId)
{
  //stampo solo le due tabelle
  StampaTabella(fp, tabellaCorr.corrIndice, funzioniId);
  fputc('\n', fp);
  StampaTabella(fp, tabellaCorr.corrId, funzioniId);
}


//Modifica l'indice di una corrispondenza e la reinserisce
//input: - CORR_TABLE tabellaCorr: la tabella
//       - unsigned int vecchioIndice: l'indice da modificare
//       - unsigned int nuovoIndice: il nuovo indice
//output: nessuno
void ModificaIndiceCorrispondenza(CORR_TABLE tabellaCorr, unsigned int vecchioIndice, unsigned int nuovoIndice)
{
  CORRESPONDENCE *corr;
  void *scambio;
  
  //cerco la corrispondenza da modificare
  corr = CercaCorrispondenzaIndice(tabellaCorr, vecchioIndice);
  
  //se l'ho trovata
  if(corr != NULL)
  {
    //cambio momentaneamente la funzione di deallocazione della tabella hash degli id
    scambio = (tabellaCorr.corrIndice.funzioniLista)->DeallocaDato;
    (tabellaCorr.corrIndice.funzioniLista)->DeallocaDato = &FunzionePigra;
    
    //rimuovo la corrispondenza dalla tabella degli indici
    CancellaDallaTabella(tabellaCorr.corrIndice, corr, NULL);
    
    //ripristino le funzioni così com'erano
    (tabellaCorr.corrIndice.funzioniLista)->DeallocaDato = scambio;
    
    //modifico la corrispondenza
    corr->indice = nuovoIndice;
    tabellaCorr.corrIndice = InserisciElementoTabella(tabellaCorr.corrIndice, corr, tabellaCorr.corrIndice.funzioniLista);
  }
}


//Ottimizza la tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella da ottimizzare
//       - unsigned int nuovaDim: la nuova dimensione della tabella delle
//                                corrispondenze
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze modificata
CORR_TABLE OttimizzaCorrispondenze(CORR_TABLE tabellaCorr, unsigned int nuovaDim, OPERAZIONI *funzioniId)
{
  tabellaCorr.corrId = OttimizzaTabella(tabellaCorr.corrId, nuovaDim, funzioniId);
  tabellaCorr.corrIndice = OttimizzaTabella(tabellaCorr.corrIndice, nuovaDim, NULL);
  return tabellaCorr;
}


//Dealloca la tabella delle corrispondenze
//input: - CORR_TABLE tabellaCorr: la tabella da deallocare
//       - OPERAZIONI *funzioniId: le funzioni per la gestione degli identificatori
//output: la tabella delle corrispondenze deallocata
CORR_TABLE DeallocaCorrispondenze(CORR_TABLE tabellaCorr, OPERAZIONI *funzioniId)
{
  //sostituisco la funzione di deallocazione di una corrispondenza con la funzione pigra
  //nella tabella degli identificatori
  (tabellaCorr.corrId.funzioniLista)->DeallocaDato = &FunzionePigra;
  
  //chiamo la funzione di deallocazione della tabella degli identificatori(senza deallocare
  //effettivamente le corrispondenze)
  tabellaCorr.corrId = DeallocaTabella(tabellaCorr.corrId, funzioniId);
  
  //dealloco la tabella degli indici (stavolta rimuovendo fisicamente le corrispondenze)
  tabellaCorr.corrIndice = DeallocaTabella(tabellaCorr.corrIndice, funzioniId);
  
  return tabellaCorr;
}


//Ritorna la dimensione delle tabella hash della corrispondenza
//input: CORR_TABLE tabellaCorr: la tabella delle corrispondenze
//output: la dimensione delle due tabelle hash sottostanti
unsigned int GetDimensioneCorrispondenza(CORR_TABLE tabellaCorr)
{
  return tabellaCorr.corrIndice.dimensione;
}

//Questa funzione non fa niente
//utilizzata per sostituire la deallocazione
//nella cancellazione dalla tabella delle corrispondenze
//in modo da non deallocare il dato che dovrà poi essere
//ricercato e deallocato anche nell'altra lista
void FunzionePigra(void *nha, void *bho)
{}


/*FUNZIONI PER LA GESTIONE DI LISTE DI CORRISPONDENZE 
  le operazioni da utilizzare per gestire strutture dati CORRESPONDENCE */


//Alloca una struttura di tipo CORRISPONDENCE
//input: - void *corrispondenza: la corrispondenza da allocare
//       - void *funzioniId: le funzioni per la gestione dell'identificatore
//output: un puntatore a struttura CORRISPONDENCE allocata
void *AllocaCorrispondenza(void *corrispondenza, void *funzioniId)
{
  //creo una nuova corrispondenza, la alloco, alloco l'identificatore
  //e la restituisco
  CORRESPONDENCE *ret;
  ret = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
  ret->indice = ((CORRESPONDENCE *)corrispondenza)->indice;
  ret->id = ((OPERAZIONI *)funzioniId)->AllocaDato(((CORRESPONDENCE *)corrispondenza)->id, funzioniId + sizeof(OPERAZIONI *));
  return ret;
}


//Stampa su output una corrispondenza
//input: - FILE *fp: l'output su cui stampare
//       - void *corrispondenza: la corrispondenza da stampare
//       - void *funzioniId: le funzioni per la gestione degli id
//output: nessuno
void StampaCorrispondenza(FILE *fp, void *corrispondenza, void *funzioniId)
{
  fprintf(fp, "| %d ", ((CORRESPONDENCE *)corrispondenza)->indice);
  ((OPERAZIONI *)funzioniId)->StampaDato(fp, ((CORRESPONDENCE *)corrispondenza)->id, funzioniId + sizeof(OPERAZIONI *));
}


//Confronta due corrispondenze per identificatore
//input: - void *primaCorr: la prima corrispondenza da comparare
//       - void *secondaCorr: la seconda corrispondenza da comparare
//       - void *funzioniId: funzioni per la gestione degli identificatori,
//                           qui non utilizzate
//output: 0 se le corrispondenze hanno lo stesso indice, 1 se il primo indice
//        è maggiore del secondo, -1 altrimenti
int ComparaCorrispondenzeIndice(void *primaCorr, void *secondaCorr, void *funzioniId)
{
  int ret;
  //confronto gli interi e restituisco il valore del caso
  if(((CORRESPONDENCE *)primaCorr)->indice == ((CORRESPONDENCE *)secondaCorr)->indice)
    ret = 0;
  else if(((CORRESPONDENCE *)primaCorr)->indice > ((CORRESPONDENCE *)secondaCorr)->indice)
    ret = 1;
  else
    ret = -1;
  return ret;
}


//Confronta due corrispondenze per identificatore
//input: - void *primaCorr: la prima corrispondenza da comparare
//       - void *secondaCorr: la seconda corrispondenza da comparare
//       - void *funzioniId: funzioni per la gestione degli identificatori,
//output: 0 se le corrispondenze hanno lo stesso id, 1 se il primo id è maggiore
//        del secondo, -1 altrimenti
int ComparaCorrispondenzeId(void *primaCorr, void *secondaCorr, void *funzioniId)
{
  //ritorno il valore risultante dalla comparazione dei due identificatori
  return ((OPERAZIONI *)funzioniId)->ComparaDati(((CORRESPONDENCE *)primaCorr)->id, 
                                            ((CORRESPONDENCE *)secondaCorr)->id, funzioniId + sizeof(OPERAZIONI *));
}


//Gestisce collisioni di corrispondenze (indice o id)
//in questo caso ammettiamo ripetizioni di corrispondenze
//e restituiamo l'elemento che ha causato la collisione
//input: - void *corrispondenza: la corrispondenza da gestire
//       - void *funzioniId: le funzioni di gestione dell'identificatore,
//                           qui non utilizzate
//output: restituisce il dato che ha generato la collisione così com'è
void *GestisciCollisioneCorrispondenze(void *corrispondenza, void *funzioniId)
{
  //ammetto le collisioni, quindi ritorno il valore
  return corrispondenza;
}


//Dealloca un dato di tipo corrispondenza
//input: - void *corrispondenza: la corrispondenza da deallocare
//       - void *funzioniId: le funzioni da utilizzare per la gestione di un id
//output: nessuno
void DeallocaCorrispondenza(void *corrispondenza, void *funzioniId)
{
  //dealloco prima il dato e poi la corrispondenza
  ((OPERAZIONI *)funzioniId)->DeallocaDato(((CORRESPONDENCE *)corrispondenza)->id, funzioniId + sizeof(OPERAZIONI *));
  free(corrispondenza);
}


//Funzione di hash per gli indici di una corrispondenza
//l'hash di un indice di corrispondenza è proprio il suo indice
//input: - void *corrispondenza: la corrispondenza da codificare
//       - void *funzioniId: le funzioni da utilizzare per la gestione
//                           degli identificatori, qui non utilizzate
//output: un intero lungo senza segno con la codifica dell'indice
unsigned long HashIndice(void *corrispondenza, void *funzioniId)
{
  return ((CORRESPONDENCE *)corrispondenza)->indice;
}


//Funzione di hash per gli identificatori di una corrispondenza
//l'hash di un indice di corrispondenza è proprio il suo indice
//input: - void *corrispondenza: la corrispondenza da codificare
//       - void *funzioniId: le funzioni da utilizzare per la gestione
//                           degli identificatori
//output: un intero lungo senza segno con la codifica dell'indice
unsigned long HashId(void *corrispondenza, void *funzioniId)
{
  //chiamo la funzione hash del gestore degli identificatori e ne ritorno il valore
  return ((OPERAZIONI *)funzioniId)->FunzioneHash(((CORRESPONDENCE *)corrispondenza)->id, funzioniId + sizeof(OPERAZIONI *));
}


//Legge una corrispondenza da un file
//input: - void *fp: il file da cui leggere
//       - void *funzioniId: le funzioni per la gestione degli identificatori
//output: un puntatore alla corrispondenza allocata
void *LeggiCorrispondenzaDaFile(void *fp, void *funzioniId)
{
  CORRESPONDENCE *ret;
  //se è possibile, leggo dal file
  if(fgetc(fp) != EOF)
  {
    ret = (CORRESPONDENCE *)malloc(sizeof(CORRESPONDENCE));
    fseek(fp, -1, SEEK_CUR);
    fscanf(fp, "%d", &ret->indice);
    if(fgetc(fp) != EOF)
    {
      fseek(fp, -1, SEEK_CUR);
      ret->id = ((OPERAZIONI *)funzioniId)->LeggiDaInput(fp, funzioniId + sizeof(OPERAZIONI *));
    }
    else
      ret = NULL;
  }
  else
    ret = NULL;
  return ret;
}
