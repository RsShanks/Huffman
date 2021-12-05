#include "arbre.h"

PArbre creerArbre(char lettre, size_t occ)
{
    PArbre tree = malloc(sizeof(tree));
    if(tree==NULL)
    {
        fprintf(stderr,"Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    tree->occurrence=occ;
    tree->lettre = (char *) lettre;
    tree->fd=NULL;
    tree->fg=NULL;

    return tree;
}


char *concatener01(const char *a, const char *b)                                                  //fonction qui concatene les chaines de caracteres (ici c des nombre)
{
    const size_t sizeA = strlen(a);                                                                     //on utilise principalement memcpy qui va nous permettre d'imprimer dans une chaine les deux chaines a concatener
    const size_t sizeB = strlen(b);                                                                     // note a moi meme : NE PAS OUBLIER LE FREE DANS LE MAIN !!!!!
    char *concatener = malloc(sizeA + sizeB + 1);                                               //+1 pour l'element null au cas ou psk strlen peut renvoyer null si a ou b vide donc memcpy va pas marcher
    strcpy(concatener, a);                                                                        //malloc pour attribuer l'espace memoire pour strcpy dans la nouvelle chaine qui contient le tout
    strcpy(concatener, b);                                                                        //strcpy tout bete de la chaine a et b dans la chaine concatener
    return concatener;
}

char *rechercheCheminBinaire(PArbre arbreHuffman, char lettre, char *chemin)    //a retravailler
{
    if(arbreHuffman!=NULL)
    {
        if(lettre==arbreHuffman->fg->lettre)
        {
            chemin=0;
        }
        if(lettre==arbreHuffman->fd->lettre)
        {
            chemin=1;
        }
    }
}
