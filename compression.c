#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "liste_chainée.h"

void Compression(char *nomFichier, char *fichierBinaire)
{
    int i, j, k;
    char lettre;
    int nbFeuilles = 0;
    int Position;
    int *PtrPosition = &Position;
    unsigned long code = 0;
    unsigned long nombre_octet;
    int hauteur = 0;

    FILE *fic = fopen(nomFichier, "r");
    FILE *ficBinaire = fopen(fichierBinaire, "w"); //on ouvre le fichier avec fopen

    if (fic == NULL)
    {
        exit(1);
    }

    fseek(fic, 0, SEEK_END);
    nombre_octet = ftell(fic);
    fwrite((char *)&nombre_octet, 4, 1, ficBinaire);

    PListe maliste = initialisation(); //erreur probable ici, j'hesite a appeler creerArbre

    while ((lettre = fgetc(fic)) != EOF) // incrementation si presence de la lettre ou non
    {
        AjoutOccurrence(maliste, lettre); //aucune idée comment incrementer j'hesite a creer une fonction pour le faire sinon je suis bloqué
    }

    maliste = triListe(maliste);

    while (maliste->premier != NULL)
    {
        maliste = Fusion(maliste); //arbre binaire contenu dans liste premier
    }

    PArbre arbreBinaireHuffman = maliste->premier->arbre;

    nbFeuilles = NombreDeFeuilles(arbreBinaireHuffman);

    PDico_Lettre tableau[nbFeuilles];

    for (Position = 0; Position < nbFeuilles; Position++)
    {
        CodeBinaire(arbreBinaireHuffman, tableau, code, hauteur, PtrPosition);
    }

    fclose(ficBinaire);
    fclose(fic);
}