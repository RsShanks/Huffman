#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void AjoutOccurrence(PListe liste, char lettre)     //a retravailler
{
    if(liste!=NULL)
    {
        if(liste->premier->arbre->lettre==lettre)
        {
            liste->premier->arbre->occurrence+=1;
        }
        else
            InsertionDebutListe(liste, creerArbre(lettre, 0));
            while(liste->premier->suivant==NULL)
            {
                if(liste->premier->suivant==lettre)
                {
                    liste->premier->suivant->arbre->occurrence+=1;
                }
                AjoutOccurrence(liste->premier->suivant, lettre);
            }
    }
}

PListe triListe(PListe liste)
{
    PElement tmp;
    PElement tmp2;
    PArbre arbrepermute;

    if(liste!=NULL)
    {
        for(tmp=liste->premier;tmp->suivant!=NULL;tmp=tmp->suivant)  //simple comparaison deux a deux avec double boucle for
        {
            for(tmp2=tmp->suivant;tmp2!=NULL;tmp2=tmp2->suivant)
            {
                if(tmp2->arbre->occurrence<tmp->arbre->occurrence)
                {
                    arbrepermute=tmp2->arbre;
                    tmp2->arbre=tmp->arbre;
                    tmp->arbre=arbrepermute;
                    triListe(liste);    //appel recursif
                }
            }
        }
    }
    return liste;
}
 
PListe Fusion(PListe liste)
{
    PElement fusion2elements;
    if(liste!=NULL)
    {
        fusion2elements=liste->premier;                                                         //strcat permet de concatener deux caracteres dans la premiere chaine passe en parametre
        strcat(fusion2elements->arbre->lettre,liste->premier->suivant->arbre->lettre);          //malloc de strcat deja defini dans les differentes structures.
        fusion2elements->arbre->occurrence+=liste->premier->suivant->arbre->occurrence;
        fusion2elements->arbre->fg=liste->premier->arbre;
        fusion2elements->arbre->fd=liste->premier->suivant;
        liste->premier=fusion2elements;
        liste->premier->suivant=liste->premier->suivant->suivant;
        free(liste->premier->suivant);                                                           //on free tjrs le 2eme element et jamais liste prmeier
        free(fusion2elements);                                                                   // on free aussi fusion2elements vu qu'on en a plus besoin.
        triListe(liste);                                                                         //on re trie la liste pour remettre l'element fusionne a la bonne place selon son occurrence.
    }
    return liste;
}

char *concatener01(const char *a, const char *b)                                                  //fonction qui concatene les chaines de caracteres (ici c des nombre)
{
    const size_t a=strlen(a);                                                                     //on utilise principalement memcpy qui va nous permettre d'imprimer dans une chaine les deux chaines a concatener
    const size_t b=strlen(b);                                                                     // note a moi meme : NE PAS OUBLIER LE FREE DANS LE MAIN !!!!!
    char *concatener=malloc(strlen(a)+strlen(b)+1);                                               //+1 pour l'element null au cas ou psk strlen peut renvoyer null si a ou b vide donc memcpy va pas marcher
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

int main(int argc, char **argv)
{
    int i,j,k;
    char lettre;
    size_t occurrence=0;                


    FILE *fic=fopen("harry potter.txt", "r");                                                   //on ouvre le fichier avec fopen 
    
    if(fic==NULL)
    {
        exit(1);
    }

    PListe maliste=initialisation(0,0);                                                         //erreur probable ici, j'hesite a appeler creerArbre 
   
    
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

    /*COMPRESSION*/





    

    fclose(fic);

    return 0;        
}
