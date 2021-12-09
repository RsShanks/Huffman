#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arb //creation de la structure arbre (plutot considéré comme un neoud de l'arbre) qui prend en element l'occurrence des lettres présentes dans le texte et enregistre la lettre associé
{
    char lettre;
    size_t occurrence;

    struct arb *fg; //on cree un fils droit et un fils gauche pour se retrouver plus tard dans l'arbre d'Huffman
    struct arb *fd;
} Arbre;

typedef Arbre *PArbre; //je pointe pour eviter les oublis de syntaxe a chaque fois

typedef struct Dico_Lettre
{
    char lettre;
    unsigned long codeBinaire;
    unsigned int hauteur; //nombre de bits
} Dico_Lettre;

typedef Dico_Lettre *PDico_Lettre;
PArbre creerArbre(char lettre, size_t occ);
char *concatener01(const char *a, const char *b);
char *rechercheCheminBinaire(PArbre arbreHuffman, char lettre, char *chemin);
int NombreDeFeuilles(PArbre arbreBinaireHuffman);
void CodeBinaire(PArbre arbreBinaireHuffman, PDico_Lettre tableau[], unsigned long code, int hauteur, int *PtrPosition); //a retravailler + code demander questions

#endif /* ARBRE_H */