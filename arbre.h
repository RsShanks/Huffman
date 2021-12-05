#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//creation de la structure arbre (plutot considéré comme un neoud de l'arbre) qui prend en element l'occurrence des lettres présentes dans le texte et enregistre la lettre associé
typedef struct arb                      
{                                       
    char* lettre;        // pas de pointeur car c'st assez petit pour etre copié
    size_t occurrence;

    struct arb *fg;                     //on cree un fils droit et un fils gauche pour se retrouver plus tard dans l'arbre d'Huffman 
    struct arb *fd;
} Arbre;

typedef Arbre* PArbre;             //je pointe pour eviter les oublis de syntaxe a chaque fois

PArbre creerArbre(char lettre, size_t occ);
char *concatener01(const char *a, const char *b);

char *rechercheCheminBinaire(PArbre arbreHuffman, char lettre, char *chemin);

#endif /* ARBRE_H */