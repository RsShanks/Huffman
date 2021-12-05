#include <stdlib.h>
#include <stdio.h>
#include "arbre.h"
#include "liste_chainée.h"

void Compresssion(char* nomFichier)
{    
    int i,j,k;
    char lettre;
    size_t occurrence=0;                


    FILE *fic=fopen(nomFichier, "r");                                                   //on ouvre le fichier avec fopen 
    
    if(fic==NULL)
    {
        exit(1);
    }

    PListe maliste=initialisation();    //peut-etre faire NULL NULL ?                        //erreur probable ici, j'hesite a appeler creerArbre 
   
    
    while((lettre=fgetc(fic)) !=EOF)                                                            // incrementation si presence de la lettre ou non 
    {      
        AjoutOccurrence(maliste, lettre);                                                       //aucune idée comment incrementer j'hesite a creer une fonction pour le faire sinon je suis bloqué     
    }

    triListe(maliste);
    
    while(maliste->premier->suivant!=NULL)
    {
        Fusion(maliste);                                                                        //arbre binaire contenu dans liste premier 
    }

    PArbre arbreBinaireHuffman=maliste->premier->arbre;         //lessgoooo
    fclose(fic);
}