#ifndef LISTE_CHAINEE_H
#define LISTE_CHAINEE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbre.h"

typedef struct List_Element             //structure element de la liste chainée contenant la structure arbre et un pointeur vers la structure élement suivante 
{
    PArbre arbre;
    struct List_Element* suivant;
} Element;

typedef Element* PElement;

typedef struct Liste                // structure Liste qui définit la premiere structure de la liste chainée pour se retrouver
{
    Element *premier;
}Liste;

typedef Liste *PListe;
PListe initialisation();
void InsertionDebutListe(PListe liste, PArbre nvArbre);
void AjoutOccurrence(PListe liste, char lettre)  ;
PElement TrouverLettre(PListe liste, char lettre);
PListe triListe(PListe liste);
PListe Fusion(PListe liste);

#endif /* LISTE_CHAINEE_H */