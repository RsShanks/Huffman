#include "arbre.h"

PArbre creerArbre(char lettre, size_t occ)
{
    PArbre tree = malloc(sizeof(tree));
    if (tree == NULL)
    {
        fprintf(stderr, "Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    tree->occurrence = occ;
    tree->lettre = lettre;
    tree->fd = NULL;
    tree->fg = NULL;

    return tree;
}

char *concatener01(const char *a, const char *b) //fonction qui concatene les chaines de caracteres (ici c des nombre)
{
    const size_t sizeA = strlen(a);               //on utilise principalement memcpy qui va nous permettre d'imprimer dans une chaine les deux chaines a concatener
    const size_t sizeB = strlen(b);               // note a moi meme : NE PAS OUBLIER LE FREE DANS LE MAIN !!!!!
    char *concatener = malloc(sizeA + sizeB + 1); //+1 pour l'element null au cas ou psk strlen peut renvoyer null si a ou b vide donc memcpy va pas marcher
    strcpy(concatener, a);                        //malloc pour attribuer l'espace memoire pour strcpy dans la nouvelle chaine qui contient le tout
    strcpy(concatener, b);                        //strcpy tout bete de la chaine a et b dans la chaine concatener
    return concatener;
}

char *rechercheCheminBinaire(PArbre arbreHuffman, char lettre, char *chemin) //a retravailler
{
    if (arbreHuffman != NULL)
    {
        if (lettre == arbreHuffman->fg->lettre)
        {
            chemin = 0;
        }
        if (lettre == arbreHuffman->fd->lettre)
        {
            chemin = 1;
        }
    }
}

int NombreDeFeuilles(PArbre arbreBinaireHuffman)
{
    if (arbreBinaireHuffman != NULL)
    {
        if (arbreBinaireHuffman->fd == NULL && arbreBinaireHuffman->fg == NULL)
        {
            return 1;
        }
        return NombreDeFeuilles(arbreBinaireHuffman->fg) + NombreDeFeuilles(arbreBinaireHuffman->fd);
    }
}

void CodeBinaire(PArbre arbreBinaireHuffman, PDico_Lettre tableau[], unsigned long code, int hauteur, int *PtrPosition) //a retravailler + code demander questions
{

    if (arbreBinaireHuffman->fd == NULL && arbreBinaireHuffman->fg == NULL)
    {
        tableau[*PtrPosition]->lettre = arbreBinaireHuffman->lettre;
        tableau[*PtrPosition]->codeBinaire = code;
        tableau[*PtrPosition]->hauteur = hauteur;
        *PtrPosition += 1;
        return;
    }
    else
    {
        if (arbreBinaireHuffman->fg)
        {
            CodeBinaire(arbreBinaireHuffman->fg, tableau, code * 2, hauteur + 1, PtrPosition);
        }
        if (arbreBinaireHuffman->fd)
        {
            CodeBinaire(arbreBinaireHuffman->fd, tableau, code * 2 + 1, hauteur + 1, PtrPosition);
        }
    }

    // teste params
    // teste si feuille
    //   si oui mise a jour valeur encodage + taille
    // sinon
    //   appel recursif fils gauche avec code décalé sur la gauche par un 0
    //   appel recursif fils droit avec code décalé sur la gauche par un 1
}
