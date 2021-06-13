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
    char numberOfChars;
}Bitfield;


Bitfield compress(char* string)
{

}

char* uncompress(Bitfield bitfield){
    return (char*) malloc(1);
}

void main()
{
    char* string ="Text to be compressed via huffmancompression";
    Bitfield bf = compress(string);
    printf(unCompress(bf));
}


