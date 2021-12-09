#include "test_framework.h"
#include "test_liste_chainee.h"
#include "arbre.h"

int test_initialisation()
{
  printf("Test initialisation\n");
  int result = 0;

  printf("Cas normal\n");
  PListe liste = initialisation();
  result += expectPtrNotNull("liste", liste);
  result += expectPtr("liste", liste->premier, NULL);

  free(liste); // Oui faut pas l'oublier lui

  return result;
}

int test_insertionDebutListe()
{
  printf("Test insertionDebutListe\n");
  int result = 0;

  printf("Avec une liste vide\n");
  PListe liste1 = initialisation();
  PArbre arbre1 = creerArbre('A', 1);
  InsertionDebutListe(liste1, arbre1);
  result += expectPtrNotNull("liste1->premier", liste1->premier);
  result += expectPtrNotNull("liste1->premier->arbre", liste1->premier->arbre);
  result += expectPtr("liste1->premier->arbre", liste1->premier->arbre, arbre1);
  result += expectChar("lettre stockée", liste1->premier->arbre->lettre, 'A');
  result += expectInt("Occurence stockée", liste1->premier->arbre->occurrence, 1);
  free(arbre1);
  free(liste1);

  printf("Avec une liste qui contient un élément\n");
  // On crée une liste qui contient déjà un arbre
  PArbre arbreAvant = creerArbre('A', 1);
  PElement premierElt = malloc(sizeof(premierElt));
  premierElt->arbre = arbreAvant;
  premierElt->suivant = NULL;
  PListe liste2 = malloc(sizeof(liste2));
  liste2->premier = premierElt;
  // On crée un autre arbre et on lance la fonction
  PArbre arbre2 = creerArbre('B', 5);
  InsertionDebutListe(liste2, arbre2);
  // On check si tout s'est bien passé
  result += expectPtrNotNull("liste2->premier", liste2->premier);
  result += expectPtr("premier->arbre", liste2->premier->arbre, arbre2);
  result += expectChar("premier->arbre->lettre", liste2->premier->arbre->lettre, 'B');
  result += expectPtrNotNull("liste2->suivant", liste2->premier->suivant);
  result += expectPtr("suivant->arbre", liste2->premier->suivant->arbre, arbreAvant);
  result += expectChar("suivant->arbre->lettre", liste2->premier->suivant->arbre->lettre, 'A');
  // @Rayane : créer une fonction destroyListe qui fait ça
  destroyList(liste2);

  return result;
}

int test_ajoutOccurence()
{
  printf("Test ajoutOccurence\n");
  int result = 0;
  char lettreNull = NULL;
  char lettreA = 'A';
  char lettreB = 'B';

  printf("Cas où on a ni liste ni lettre\n");
  PListe listeNull = NULL;
  AjoutOccurrence(listeNull, lettreNull);
  result += expectPtr("listeNull", listeNull, NULL);

  printf("Cas où on a pas de liste\n");
  PListe listeNull2 = NULL;
  AjoutOccurrence(listeNull2, lettreA);
  result += expectPtr("listeNull2", listeNull2, NULL);

  printf("Cas où on a pas de lettre\n");
  PListe listeVide = initialisation();
  AjoutOccurrence(listeVide, NULL);
  result += expectPtr("listeVide->premier", listeVide->premier, NULL);
  destroyList(listeVide);

  printf("Cas où la liste est vide au départ\n");
  PListe listeVide2 = initialisation();
  AjoutOccurrence(listeVide2, lettreA);
  result += expectPtrNotNull("listeVide2->premier", listeVide2->premier);
  result += expectPtrNotNull("listeVide2->premier->arbre", listeVide2->premier->arbre);
  result += expectChar("premier arbre lettre", listeVide2->premier->arbre->lettre, lettreA);
  result += expectInt("premier arbre occurence", listeVide2->premier->arbre->occurrence, 1);
  result += expectPtr("premier arbre fg", listeVide2->premier->arbre->fg, NULL);
  result += expectPtr("premier arbre fd", listeVide2->premier->arbre->fd, NULL);
  destroyList(listeVide2);

  printf("Cas où la liste contient une autre lettre\n");
  // On crée une liste qui contient une occurence de "A"
  PListe liste1 = initialisation();
  PElement element1 = malloc(sizeof(element1));
  PArbre arbre1 = creerArbre('A', 1);
  element1->arbre = arbre1;
  element1->suivant = liste1->premier;
  liste1->premier = element1;
  // On ajoute une occurence de B
  AjoutOccurrence(liste1, lettreB);
  // On vérifie ce qui doit l'être
  result += expectPtrNotNull("liste1->premier->arbre", liste1->premier->arbre);
  result += expectChar("premiere lettre de liste1", liste1->premier->arbre->lettre, lettreB);
  result += expectInt("occurence de la premiere lettre", liste1->premier->arbre->occurrence, 1);
  result += expectPtr("l'occurence de A n'a pas disparu (element)", liste1->premier->suivant, element1);
  result += expectPtr("l'occurence de A n'a pas disparu (arbre)", liste1->premier->suivant->arbre, arbre1);
  result += expectChar("l'occurence de A n'a pas disparu (lettre)", liste1->premier->suivant->arbre->lettre, lettreA);
  result += expectInt("l'occurence de A n'a pas changé", liste1->premier->suivant->arbre->occurrence, 1);
  // On oublie pas de free les pointeurs
  destroyList(liste1);

  printf("Cas où la liste contient déjà une occurence de la lettre\n");
  // On crée une liste qui contient une occurence de "A"
  PListe liste2 = initialisation();
  PElement element2 = malloc(sizeof(element2));
  PArbre arbre2 = creerArbre('A', 1);
  element2->arbre = arbre2;
  element2->suivant = liste2->premier;
  liste2->premier = element2;
  // On ajoute une occurence de A
  AjoutOccurrence(liste2, lettreB);
  // On vérifie ce qui doit l'être
  result += expectPtr("liste1->premier->arbre", liste2->premier->arbre, arbre2);
  result += expectChar("premiere lettre de liste1", liste2->premier->arbre->lettre, lettreA);
  result += expectInt("occurence de B a été incrémenté", liste2->premier->arbre->occurrence, 2);
  result += expectPtr("on a pas ajouté d'élément dans la liste", liste2->premier->suivant, NULL);
  // On oublie pas de free les pointeurs
  destroyList(liste2);

  return result;
}

int test_trouverLettre()
{
  int result = 0;
  char lettreA = 'A';
  char lettreB = 'B';

  printf("Cas où on a ni liste, ni lettre\n");
  PElement element1 = TrouverLettre(NULL, NULL);
  result += expectPtr("element1", element1, NULL);

  printf("Cas où on a pas de liste\n");
  PElement element2 = TrouverLettre(NULL, lettreA);
  result += expectPtr("element2", element2, NULL);

  printf("Cas où on a une liste vide et pas de lettre\n");
  PListe liste3 = initialisation();
  PElement element3 = TrouverLettre(liste3, NULL);
  result += expectPtr("element3", element3, NULL);
  result += expectPtr("la liste n'a pas changé", liste3->premier, NULL);
  destroyList(liste3);

  printf("Cas où on a une liste vide\n");
  PListe liste4 = initialisation();
  PElement element4 = TrouverLettre(liste4, lettreA);
  result += expectPtr("element4", element4, NULL);
  result += expectPtr("liste n'a pas changé", liste4->premier, NULL);
  destroyList(liste4);

  printf("Cas où on a pas de lettre\n");
  // On init une liste où il y'a déjà une occurence de A
  PListe liste5 = initialisation();
  PElement elt5 = malloc(sizeof(elt5));
  PArbre arbre5 = creerArbre(lettreA, 1);
  elt5->arbre = arbre5;
  elt5->suivant = liste5->premier;
  liste5->premier = elt5;
  // On lance TrouverLettre
  PElement element5 = TrouverLettre(liste5, NULL);
  // On vérifie
  result += expectPtr("element5", element5, NULL);
  result += expectPtr("la liste n'a pas changé", liste5->premier, elt5);
  // On detruit la liste
  destroyList(liste5);

  printf("Cas où on a une liste qui contient la lettre\n");
  // On init une liste où il y'a déjà une occurence de A et de B
  PListe liste6 = initialisation();
  PArbre arbre6A = creerArbre(lettreA, 5);
  PArbre arbre6B = creerArbre(lettreB, 2);
  InsertionDebutListe(liste6, arbre6B);
  InsertionDebutListe(liste6, arbre6A);
  // On lance TrouverLettre pour A
  PElement element6A = TrouverLettre(liste6, lettreA);
  result += expectPtr("element6A->arbre", element6A->arbre, arbre6A);
  result += expectChar("element6A->lettre", element6A->arbre->lettre, lettreA);
  result += expectInt("element6A->occurence", element6A->arbre->occurrence, 5);
  // On lance TrouverLettre pour B
  PElement element6B = TrouverLettre(liste6, lettreB);
  result += expectPtr("element6B->arbre", element6B->arbre, arbre6B);
  result += expectChar("element6B->lettre", element6B->arbre->lettre, lettreB);
  result += expectInt("element6B->occurence", element6B->arbre->occurrence, 2);

  printf("Cas où on a une liste qui ne contient pas la lettre\n");
  // On reprend la même liste que précédemment (flemme d'en faire une nouvelle)
  PElement element6C = TrouverLettre(liste6, 'C');
  result += expectPtr("element6C", element6C, NULL);
  // On oublie pas de destroy
  destroyList(liste6);

  return result;
}

int test_triListe()
{
  int result = 0;
  // @Rayane à toi d'écrire les tests :p
  return result;
}

int test_fusion()
{
  int result = 0;
  // @Rayane à toi d'écrire les tests :p
  return result;
}

void destroyList(PListe liste)
{
  PElement currentElt = liste->premier;
  PElement tmpCurrentElt = liste->premier;
  while (currentElt)
  {
    tmpCurrentElt = currentElt->suivant;
    free(currentElt->arbre);
    free(currentElt);
    currentElt = currentElt->suivant;
  }
  free(liste);
}

int testListeChainee()
{
  return test_initialisation() + test_insertionDebutListe() + test_ajoutOccurence() + test_trouverLettre() + test_triListe() + test_fusion();
}