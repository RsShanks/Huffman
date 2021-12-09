#include <stdio.h>
#include "test_arbre.h"
#include "test_liste_chainee.h"

int main(int argc, char **argv)
{
  printf("\n========== TESTS ==========\n");
  int result = 0;
  printf("TEST LES ARBRES\n");
  if (testArbre() > 0)
  {
    result += 1;
    printf("TEST FAILED : ARBRE\n");
  }
  else
  {
    printf("TEST SUCCESS : ARBRE\n");
  }

  printf("TEST LES LISTES CHAINEES\n");
  if (testListeChainee())
  {
    result += 1;
    printf("TEST FAILED : LISTE CHAINEE\n");
  }
  else
  {
    printf("TEST SUCCESS : LISTE CHAINEE\n");
  }
  printf("\n========== FIN DES TESTS ==========\n");
  return result;
}