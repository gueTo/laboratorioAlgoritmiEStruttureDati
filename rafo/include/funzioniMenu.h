/* PROTOTIPI ED INCLUDE PER LE FUNZIONI DEI MENU RICHIAMATE DAL MAIN
   per la gestione di grafi

   di Francesco Altiero, matr.566/2258
   email: auronisback@hotmail.com                    */

#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "IOGrafo.h"
#include "listastringhe.h"
#include "ListeAdiacenza.h"
#include "MatriceAdiacenza.h"
#include "Visite.h"

#ifndef DIM
#define DIM 128
#endif

//Stampa il menù principale.
//input: - LIST arrayListe[]: il vettore di liste da gestire
//       - OPERAZIONI arrayFun[]: il vettore delle operazioni rispettive di ogni lista
//output: nessuno
void StampaMenuPrincipale(OPERAZIONI *funzioniId);


//Stampa il menù per la gestione dell'I/O del grafo
//input: - GRAPH *grafo: un puntatore al grafo su cui operare
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: un valore intero che determinerà la fine delle operazioni di IO
GRAPH FunzioniIO(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Stampa il menù per le modifiche del grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni da utilizzare con la rappresentazione
//output: il grafo modificato
GRAPH FunzioniModifica(GRAPH grafo, GRAPH_FUNC funzioniGrafo);


//Gestisce il menu per le visite sul grafo
//input: - GRAPH grafo: il grafo
//       - GRAPH_FUNC funzioniGrafo: le funzioni della rappresentazione
//output: il grafo modificato
GRAPH FunzioniVisite(GRAPH grafo, GRAPH_FUNC funzioniGrafo);
