#include<stdio.h> // define the header file

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


void compress(char* string)
{

}

void main()
{
    char* string ="Text to be compressed via huffmancompression";
    compress(string);
}


