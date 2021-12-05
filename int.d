#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define ARBRENULL NULL

typedef int Element;

typedef struct arb
{
    Element elmt;
    struct arb* fg;
    struct arb* fd;
}Arbre;

typedef Arbre *PArbre;

PArbre creerArbre(Element x)
{
    PArbre tr=malloc(sizeof(tr));
    if(tr==NULL)
    {
        fprintf(stderr,"Erreur allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    tr->elmt=x;
    tr->fd=NULL;
    tr->fg=NULL;
    return tr;
}

int estVide(PArbre tr)
{
    return (tr==ARBRENULL);
}

int estFeuille(PArbre tr)
{
    return !(tr->fd||tr->fg);
}



int ExisterFilsGauche(PArbre tr)
{
    return (tr->fg ? TRUE : FALSE);
}

int ExisterFilsDroit(PArbre tr)
{
    return(tr->fd ? TRUE : FALSE);
}

PArbre FilsGauche(PArbre tr)
{
    ExisterFilsGauche(tr);
    return tr->fg;
}

PArbre FilsDroit(PArbre tr)
{
    ExisterFilsDroit(tr);
    return tr->fd;
}

PArbre AjouterFilsGauche(PArbre tr,Element k )
{
    if(! ExisterFilsGauche(tr))
    tr->fg=creerArbre(k);
    return tr;
}

PArbre AjouterFilsDroit(PArbre tr, Element n)
{
    if(! ExisterFilsDroit(tr))
    tr->fd=creerArbre(n);
    return tr;
}


void traiter(Element p)
{
    printf("%d\n", p);
}



int max(int a, int b)
{
    return(a<b ? b:a);
}


int min(int a, int b)
{
    return(a<b ? a:b);
}


int hauteur(PArbre tr)
{
    if(estVide(tr))
        return -1;
    if(estFeuille(tr))
        return 0;
    return 1+max(hauteur(FilsGauche(tr)), hauteur(FilsDroit(tr)));
}

int taille(PArbre tr)
{
    if(estVide(tr) || estFeuille(tr))
        return 0;
    return 1+taille(FilsDroit(tr))+taille(FilsGauche(tr));
}

int nbFeuilles(PArbre tr)
{
    if(estVide(tr))
        return 0;
    if(estFeuille(tr))
        return 1;
    return nbFeuilles(FilsDroit(tr))+nbFeuilles(FilsGauche(tr));
}

int minTableau(int tab[], int taille)
{
    int i, position;
    int minimum=tab[0];

    for(i=0;i<taille;i++)
        if( minimum > tab[i])
        {
            minimum=tab[i];
            tab[i]=NULL;
        }
    return minimum;
}

int maxTableau(int tab[], int taille)
{
    int i;
    int maximum=tab[0];

    for(i=0;i<taille;i++)
        if( maximum < tab[i])
        {
            maximum=tab[i];
            tab[i]=NULL;
        }
    return maximum;
}





int main()
{
    
    FILE *fic=fopen("harry potter.txt", "r");    //on ouvre le fichier avec fopen 
    
    if(fic==NULL)
        exit(1);

    int tab[256]={0};         // creation d'un tableau de la taille de la table d'ASCII pour contenir l'occurence de tous les caracteres
    int lettre; 
    int i;
    
    
    while((lettre=fgetc(fic)) !=EOF)    // incrementation si presence de la lettre ou non dans le tableau
    {
        tab[lettre]++;
    }

    
    minTableau(tab,256);
    maxTableau(tab,256);

   
    for(i=0; i<256; i++)
    {
        printf("tab[%d] vaut %d\n", i, tab[i]);
    }

    fclose(fic);

    return 0;        
}       
