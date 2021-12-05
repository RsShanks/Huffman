#include <stdio.h>
#include <stdlib.h>

typedef struct arb                      //creation de la structure arbre (plutot considéré comme un neoud de l'arbre) qui prend en element l'occurrence des lettres présentes dans le texte et enregistre la lettre associé
{                                       
    char *lettre;
    size_t occurrence;

    struct arb *fg;                     //on cree un fils droit et un fils gauche pour se retrouver plus tard dans l'arbre d'Huffman 
    struct arb *fd;
}Arbre;

typedef Arbre *PArbre;              //je pointe pour eviter les oublis de syntaxe a chaque fois

typedef struct Element             //structure element de la liste chainée contenant la structure arbre et un pointeur vers la structure élement suivante 
{
    PArbre arbre;
    Element *suivant;
}Element;

typedef Element *PElement;

typedef struct Liste                // structure Liste qui définit la premiere structure de la liste chainée pour se retrouver
{
    Element *premier;
}Liste;

typedef Liste *PListe;


PArbre creerArbre(char lettre, size_t occ)
{
    PArbre tree=malloc(sizeof(tree));
    if(tree==NULL)
    {
        fprintf(stderr,"Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    tree->occurrence=occ;
    tree->lettre=lettre;
    tree->fd=NULL;
    tree->fg=NULL;

    return tree;
}

PListe initialisation(char lettre, size_t occurrence)
{
    PListe liste = malloc(sizeof(liste));
    PElement element = malloc(sizeof(element));
    element->arbre=creerArbre(lettre, occurrence);                //je sais pas du tout si c'est correct de faire ça
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}


void InsertionDebutListe(PListe liste, PArbre nvArbre)
{
    
    PElement nouveauElement = malloc(sizeof(nouveauElement));
    nouveauElement->arbre = nvArbre;
    nouveauElement->suivant = liste->premier;
    liste->premier = nouveauElement;
}

int main(int argc, char **argv)
{
    int i,j,k;
    char lettre;
    size_t occurrence=0;                


    FILE *fic=fopen("harry potter.txt", "r");    //on ouvre le fichier avec fopen 
    
    if(fic==NULL)
        exit(1);


    PListe maliste=initialisation(0,0);     //erreur probable ici, j'hesite a appeler creerArbre 

    
    for(i=0;i<256;i++)
    {
        while((lettre=fgetc(fic)) !=EOF)    // incrementation si presence de la lettre ou non 
        {   
            InsertionDebutListe(maliste,creerArbre(i,0));
            if(lettre==i && )
            {
                                                //aucune idée comment incrementer j'hesite a creer une fonction pour le faire sinon je suis bloqué
            }
            
        }
    }

    

    fclose(fic);

    return 0;        
}
