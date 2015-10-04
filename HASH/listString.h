#include <stdio.h>

#ifndef DIM_STRING
    #define DIM_STRING 255
#endif


#ifndef MAX_RAND_STRING_LENGTH
    #define MAX_RAND_STRING_LENGTH 15
#endif

unsigned long HashStringhe(void *str, void *param);
void *AllocaStringa(void *x, void *param);
int ComparaStringhe(void *x, void *y, void *param);
void StampaStringa(FILE *fp, void *x, void *param);
void *GestisciCollisioneStringa(void *str, void *param);
void DeallocaStringa(void *x, void *param);
void *LeggiStringaDaTastiera(void *source, void *param);
void *LeggiStringaDaFile(void *fp, void *param);
void *LeggiStringaCasuale(void *param1, void *param2);
