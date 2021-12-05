#include "liste_chainée.h"
#include "arbre.h"


PListe initialisation()
{
    PListe liste = malloc(sizeof(liste)); // Alloc memory pour la liste 
    liste->premier = NULL; // Premier element existe pas => NULL
    return liste; // Self explanatory
}

/*PListe initialisation_FALSE(char lettre, size_t occurrence)  ancienne fonction
{
    PListe liste = malloc(sizeof(liste));
    PElement element = malloc(sizeof(element));
    element->arbre=creerArbre(lettre, occurrence);                //je sais pas du tout si c'est correct de faire ça
    element->suivant = NULL;
    liste->premier = element;

    return liste;
}*/

void InsertionDebutListe(PListe liste, PArbre nvArbre)
{
    PElement nouveauElement = malloc(sizeof(nouveauElement));
    nouveauElement->arbre = nvArbre;
    nouveauElement->suivant = liste->premier;
    liste->premier = nouveauElement;
}

/*void AjoutOccurrence(PListe liste, char lettre)     //a retravailler ancienne fonction
{
    vérifier si liste est nulle
    vérifier si présence de la lettre dans la liste chainée
        si non ajouter la lettre dans la liste et occ +1
        si oui occ +1
    
    if(liste!=NULL)
    {
        if(liste->premier->arbre->lettre==lettre)
        {
            liste->premier->arbre->occurrence+=1;
        }
        else
            InsertionDebutListe(liste, creerArbre(lettre, 1));
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
*/

void AjoutOccurrence(PListe liste, char lettre)
{
    /*vérifier si liste est nulle
    vérifier si présence de la lettre dans la liste chainée
        si non ajouter la lettre dans la liste et occ +1
        si oui occ +1
    */
    if(liste!=NULL)
    {
        PElement found_element = TrouverLettre(liste, lettre);
        if(found_element != NULL)
        {
            found_element->arbre->occurrence = found_element->arbre->occurrence +1;
        }
        else
        {
            InsertionDebutListe(liste, creerArbre(lettre, 1));
        }
    }      
}

PElement TrouverLettre(PListe liste, char lettre)
{
    PElement current_elmt= liste->premier;
    while(current_elmt != NULL)
    {
        if(current_elmt->arbre->lettre == lettre)
        {
            return current_elmt;
        }
        current_elmt = current_elmt->suivant; 
    }  
    return NULL;
}



PListe triListe(PListe liste)
{
    PElement tmp;
    PElement tmp2;
    PArbre arbrepermute;

    if(liste!=NULL)
    {
        for(tmp = liste->premier; tmp->suivant != NULL; tmp = tmp->suivant)  //simple comparaison deux a deux avec double boucle for
        {
            for(tmp2 = tmp->suivant ; tmp2 != NULL; tmp2 = tmp2->suivant)
            {
                if(tmp2->arbre->occurrence < tmp->arbre->occurrence)
                {
                    arbrepermute = tmp2->arbre;
                    tmp2->arbre = tmp->arbre;
                    tmp->arbre = arbrepermute;
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
        strcat(fusion2elements->arbre->lettre, liste->premier->suivant->arbre->lettre);          //malloc de strcat deja defini dans les differentes structures.
        fusion2elements->arbre->occurrence += liste->premier->suivant->arbre->occurrence;
        fusion2elements->arbre->fg=liste->premier->arbre;
        fusion2elements->arbre->fd=liste->premier->suivant;
        liste->premier = fusion2elements;
        liste->premier->suivant=liste->premier->suivant->suivant;
        free(liste->premier->suivant);                                                           //on free tjrs le 2eme element et jamais liste prmeier
        free(fusion2elements);                                                                   // on free aussi fusion2elements vu qu'on en a plus besoin.
        
        triListe(liste);                                                                         //on re trie la liste pour remettre l'element fusionne a la bonne place selon son occurrence.
    }
    return liste;
}

