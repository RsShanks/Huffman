#include <stdlib.h>
#include <stdio.h>
#include "compression.h"

int main(int argc, char **argv) //pour executer --> ./Huffman "compression" ou "decompression" "nomfichier"
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