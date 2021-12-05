#include <stdlib.h>
#include <stdio.h>
#include "compression.h"

int main(int argc, char **argv)    //pour executer --> ./Huffman "compression" ou "decompression" "nomfichier"
{
    char* mode = argv[1];
    char* nomFichier = argv[2];

    if (mode == "compression") 
    {
        compression(nomFichier);
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