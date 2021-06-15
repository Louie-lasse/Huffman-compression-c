#include<stdio.h> // define the header file
#include <stdlib.h>

typedef struct B{
    union {
        struct B* leftSubBranch;
        struct {
            short leftAmount0;
            char leftAmount1;
            char leftChar;
        };
    };
    union {
        struct B* rightSubBranch;
        struct {
            short rightAmount0;
            char rightAmount1;
            char rightChar;
        };
    };
} Branch;

typedef struct Bitfield{
    char* bits;
    char bitInChar;
    char endOfLastChar;
    short numberOfChars;
}Bitfield;

typedef struct Compressor{
    Bitfield* bits;
    Branch* branch;
}Compressor;

Compressor compress(char* string)
{

}

char* unCompress(Compressor compressor){
    return (char*) malloc(1);
}

void main()
{
    char* string ="Text to be compressed via huffmancompression";
    Compressor compressedString = compress(string);
    printf(unCompress(compressedString));
}


