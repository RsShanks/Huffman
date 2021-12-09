#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arb //creation de la structure arbre (plutot considéré comme un neoud de l'arbre) qui prend en element l'occurrence des lettres présentes dans le texte et enregistre la lettre associé
{
  char lettre;
  size_t occurrence;

  struct arb *fg; //on cree un fils droit et un fils gauche pour se retrouver plus tard dans l'arbre d'Huffman
  struct arb *fd;
} Arbre;

typedef Arbre *PArbre; //je pointe pour eviter les oublis de syntaxe a chaque fois

typedef struct List_Element //structure element de la liste chainée contenant la structure arbre et un pointeur vers la structure élement suivante
{
  PArbre arbre;
  struct List_Element *suivant;
} Element;

typedef Element *PElement;

typedef struct Dico_Lettre
{
  char lettre;
  unsigned long codeBinaire;
  unsigned int hauteur; //nombre de bits
} Dico_Lettre;

typedef Dico_Lettre *PDico_Lettre;

typedef struct Liste // structure Liste qui définit la premiere structure de la liste chainée pour se retrouver
{
  Element *premier;
} Liste;

typedef Liste *PListe;

PArbre creerArbre(char lettre, size_t occ)
{
  PArbre tree = malloc(sizeof(tree));
  if (tree == NULL)
  {
    fprintf(stderr, "Erreur allocation mémoire\n");
    exit(EXIT_FAILURE);
  }
  tree->occurrence = occ;
  tree->lettre = lettre;
  tree->fd = NULL;
  tree->fg = NULL;

  return tree;
}

PListe initialisation()
{
  PListe liste = malloc(sizeof(liste));
  liste->premier = NULL; //!!!NE PAS METTRE INITIALISER A NULL
  return liste;
}

void InsertionDebutListe(PListe liste, PArbre nvArbre)
{

  PElement nouveauElement = malloc(sizeof(nouveauElement));
  nouveauElement->arbre = nvArbre;
  nouveauElement->suivant = liste->premier;
  liste->premier = nouveauElement;
}

PElement TrouverLettre(PListe liste, char lettre)
{
  PElement current_element = liste->premier;
  while (current_element != NULL)
  {
    if (current_element->arbre->lettre == lettre)
    {
      return current_element;
    }
    current_element = current_element->suivant;
  }
  return NULL;
}

void AjoutOccurrence(PListe liste, char lettre)
{
  PElement found_element = TrouverLettre(liste, lettre); //verifie si presence de la lettre dans la liste chaine
  if (found_element != NULL)
  {
    found_element->arbre->occurrence += 1; //si oui incrementation si non Insertion au debut de la liste avec occurence 1
  }
  else
  {
    InsertionDebutListe(liste, creerArbre(lettre, 1));
  }
}

PListe triListe(PListe liste)
{
  PElement tmp;
  PElement tmp2;
  PArbre arbrepermute;

  if (liste != NULL)
  {
    for (tmp = liste->premier; tmp->suivant != NULL; tmp = tmp->suivant) //simple comparaison deux a deux avec double boucle for
    {
      for (tmp2 = tmp->suivant; tmp2 != NULL; tmp2 = tmp2->suivant)
      {
        if (tmp2->arbre->occurrence < tmp->arbre->occurrence)
        {
          arbrepermute = tmp2->arbre;
          tmp2->arbre = tmp->arbre;
          tmp->arbre = arbrepermute;
        }
      }
    }
  }
  return liste;
}

PListe Fusion(PListe liste)
{
  PElement fusion2elements;
  if (liste != NULL)
  {
    fusion2elements = liste->premier; //strcat permet de concatener deux caracteres dans la premiere chaine passe en parametre          //malloc de strcat deja defini dans les differentes structures.
    fusion2elements->arbre->occurrence += liste->premier->suivant->arbre->occurrence;
    fusion2elements->arbre->fg = liste->premier->arbre;
    fusion2elements->arbre->fd = liste->premier->suivant->arbre;
    liste->premier = fusion2elements;
    liste->premier->suivant = liste->premier->suivant->suivant;
    free(liste->premier->suivant); //on free tjrs le 2eme element et jamais liste prmeier
    free(fusion2elements);         // on free aussi fusion2elements vu qu'on en a plus besoin.
    liste = triListe(liste);       //on re trie la liste pour remettre l'element fusionne a la bonne place selon son occurrence.
  }
  return liste;
}

int NombreDeFeuilles(PArbre arbreBinaireHuffman)
{
  if (arbreBinaireHuffman != NULL)
  {
    if (arbreBinaireHuffman->fd == NULL && arbreBinaireHuffman->fg == NULL)
    {
      return 1;
    }
    return NombreDeFeuilles(arbreBinaireHuffman->fg) + NombreDeFeuilles(arbreBinaireHuffman->fd);
  }
}

/*int CombienDeFeuille(PArbreHuffman Arbre, int nbFeuille)
{
if(arbre->fg == NULL && arbre->fd == NULL) //vérification si racine feuille
{
    nbFeuille =+1;
    return nbFeuille;
}
else
{ // on doit vérifier pour les 3 possibilité
    if(arbre->fd !=NULL && arbre->fg != NULL) //si les deux cotés on des fils on relance sur les 2
    {
        CombienDeFeuille(PArbreHuffman->fg, nbFeuille);
        CombienDeFeuille(PArbreHuffman->fd, nbFeuille);
    }
    if(arbre->fd !=NULL && arbre->fg == NULL) // sinon sur la droite uniquement
    {
        CombienDeFeuille(PArbreHuffman->fd, nbFeuille);
    }
    if(arbre->fg != NULL && arbre->fd == NULL) //sinon sur la gauche uniquement
    {
        CombienDeFeuille(PArbreHuffman->fg, nbFeuille);
    }
return nbFeuille;
} */

void CodeBinaire(PArbre arbreBinaireHuffman, PDico_Lettre tableau[], unsigned long code, int hauteur, int *PtrPosition) //a retravailler + code demander questions
{

  if (arbreBinaireHuffman->fd == NULL && arbreBinaireHuffman->fg == NULL)
  {
    tableau[*PtrPosition]->lettre = arbreBinaireHuffman->lettre;
    tableau[*PtrPosition]->codeBinaire = code;
    tableau[*PtrPosition]->hauteur = hauteur;
    *PtrPosition += 1;
    return;
  }
  else
  {
    if (arbreBinaireHuffman->fg)
    {
      CodeBinaire(arbreBinaireHuffman->fg, tableau, code * 2, hauteur + 1, PtrPosition);
    }
    if (arbreBinaireHuffman->fd)
    {
      CodeBinaire(arbreBinaireHuffman->fd, tableau, code * 2 + 1, hauteur + 1, PtrPosition);
    }
  }

  // teste params
  // teste si feuille
  //   si oui mise a jour valeur encodage + taille
  // sinon
  //   appel recursif fils gauche avec code décalé sur la gauche par un 0
  //   appel recursif fils droit avec code décalé sur la gauche par un 1
}

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

int main(int argc, char **argv)
{

  char *mode = argv[1];
  char *nomFichier = argv[2];
  char *FichierBinaire = argv[3];

  if (mode == "compression")
  {
    Compression(nomFichier, FichierBinaire);
  }
  // else if (mode == "decompression")
  // {
  //     decompression();
  // }
  else
  {
    printf("Mode %s n'existe pas !", mode);
    return 42;
  }

  return 0;
}