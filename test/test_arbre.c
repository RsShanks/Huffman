#include "test_framework.h"
#include "arbre.h"

int test_creerArbre()
{
  printf("Test creerArbre\n");
  int result = 0;

  printf("Cas d'utilisation normal\n");
  PArbre tree = creerArbre('A', 1);
  result += expectChar("tree->lettre", tree->lettre, 'A');
  result += expectInt("tree->occurence", tree->occurrence, 1);
  result += expectPtr("tree->fg", tree->fg, NULL);
  result += expectPtr("tree->fd", tree->fd, NULL);
  free(tree);

  return result;
}

int test_concatener01()
{
  printf("Test concatener01\n");
  int result = 0;

  printf("Cas d'utilisation normal\n");
  char *str = concatener01("a", "b");
  result += expectStr("str", str, "ab");

  printf("Cas où le premier arg est vide\n");
  char *str2 = concatener01("", "b");
  result += expectStr("str2", str, "b");

  printf("Cas où le 2eme arg est vide\n");
  char *str3 = concatener01("a", "");
  result += expectStr("str3", str, "a");

  return result;
}

int test_rechercheCheminBinaire()
{
  // TODO: Later because the function seems to be a WIP
  printf("Test rechercheCheminBinaire\n");
  int result = 0;

  printf("Cas où l'arbre est vide\n");
  PArbre emptyTree = creerArbre(NULL, 0);
  char *chemin0 = rechercheCheminBinaire(emptyTree, 'A', "");

  free(emptyTree);
  return 0;
}

int testArbre()
{
  return test_creerArbre() + test_concatener01() + test_rechercheCheminBinaire();
}
