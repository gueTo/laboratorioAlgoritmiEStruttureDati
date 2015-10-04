/* MAIN DI PROVA PER LA LIBRERIA DI GRAFI
   
   di Francesco Altiero, matr.566/2258  
   email: auronisback@hotmail.com      */

#include <stdio.h>
#include <stdlib.h>
#include "include\Grafo.h"
#include "include\IOGrafo.h"
#include "include\funzioniMenu.h"
#include "include\listastringhe.h"
#include "include\ListeAdiacenza.h"
#include "include\MatriceAdiacenza.h"
#include "include\Visite.h"


int main(int argc, char *argv[])
{
  OPERAZIONI funzioniId; //le funzioni per gli identificatori

  GRAPH_FUNC funzioniLista;
  GRAPH_FUNC funzioniMatrice;
  GRAPH_ARC arco;
  GRAPH grafo;
  GRAPH trasposto;
  FILE *fp;
  int i, j;
  funzioniId = InserisciFunzioni(&AllocaStringa, &StampaStringa, &ComparaStringhe, &GestisciCollisioneStringa, 
                                    &DeallocaStringa, &LeggiStringaDaFile, &HashStringhe);
  
  StampaMenuPrincipale(&funzioniId);
  system("PAUSE");	
  return 0;
}
