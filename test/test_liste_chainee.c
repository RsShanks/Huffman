#include "test_framework.h"
#include "liste_chainée.h"
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
  PArbre arbre1 = creerArbre("A", 1);
  InsertionDebutListe(liste1, arbre1);
  result += expectPtrNotNull("liste1->premier", liste1->premier);
  result += expectPtrNotNull("liste1->premier->arbre", liste1->premier->arbre);
  result += expectPtr("liste1->premier->arbre", liste1->premier->arbre, arbre1);
  result += expectChar("lettre stockée", liste1->premier->arbre->lettre, "A");
  result += expectInt("Occurence stockée", liste1->premier->arbre->occurrence, 1);
  free(arbre1);
  free(liste1);

  printf("Avec une liste qui contient un élément\n");
  // On crée une liste qui contient déjà un arbre
  PArbre arbreAvant = creerArbre("A", 1);
  PElement premierElt = malloc(sizeof(premierElt));
  premierElt->arbre = arbreAvant;
  premierElt->suivant = NULL;
  PListe liste2 = malloc(sizeof(liste2));
  liste2->premier = premierElt;
  // On crée un autre arbre et on lance la fonction
  PArbre arbre2 = creerArbre("B", 5);
  InsertionDebutListe(liste2, arbre2);
  // On check si tout s'est bien passé
  result += expectPtrNotNull("liste2->premier", liste2->premier);
  result += expectPtr("premier->arbre", liste2->premier->arbre, arbre2);
  result += expectChar("premier->arbre->lettre", liste2->premier->arbre->lettre, "B");
  result += expectPtrNotNull("liste2->suivant", liste2->premier->suivant);
  result += expectPtr("suivant->arbre", liste2->premier->suivant->arbre, arbreAvant);
  result += expectChar("suivant->arbre->lettre", liste2->premier->suivant->arbre->lettre, "A");

  PElement currentElt = liste2->premier;
  PElement tmpCurrentElt = liste2->premier;
  while (currentElt)
  {
    tmpCurrentElt = currentElt->suivant;
    free(currentElt->arbre);
    free(currentElt);
    currentElt = currentElt->suivant;
  }
  free(liste2);

  return result;
}
// TODO Later => dodo
int test_ajoutOccurence() {}

int test_trouverLettre()
{
}

int test_triListe() {}

int test_fusion() {}

int testListeChainee()
{
  return test_initialisation() + test_insertionDebutListe() + test_ajoutOccurence() + test_trouverLettre() + test_triListe() + test_fusion();
}