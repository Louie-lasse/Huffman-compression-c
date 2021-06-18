#include<stdio.h> // define the header file
#include <stdlib.h>

#define leftHasChar     1<<0
#define rightHasChar    1<<1
#define semiNull        1<<2
#define true            1

typedef struct B{
    union {
        struct B* leftSubBranch;
        struct {
            char leftAmount;
            char leftChar;
            char unusedLeft;
        };
    };
    union {
        struct B* rightSubBranch;
        struct {
            short rightAmount;
            char rightChar;
            char unusedRight;
        };
    };
    char code;
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

typedef struct LL{
    Branch* this;
    struct LL* next;
}LinkedList;

void createAndAdd(LinkedList* list, Branch* item){
    LinkedList* newListItem = (LinkedList*) malloc(sizeof(LinkedList));
    newListItem->this = item;
    newListItem->next=0;
    list->next = newListItem;
}

void add(LinkedList* list, Branch* item){
    if (list->next == 0) createAndAdd(list, item);
    else add(list->next, item);
}

LinkedList* newLinkedList(){
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    list->next = 0;
}

char* countChars(char* string){
    char* charCount = (char*) malloc(255);
    for (int i = 0; i < 256; i++) *(charCount+i) = 0;
    while(*string)
    {
        *(charCount+*string++) += 1;
        charCount[*string++]++;
    }
    return charCount;
}

Branch* newSemiNull(unsigned char c, char amount){
    Branch* b = (Branch*) malloc(sizeof(Branch));
    b->leftChar = c;
    b->leftAmount = amount;
    b->rightSubBranch = 0;
    b->code |= semiNull;
    return b;
}

int valueOf(Branch item){
    if (item.code & semiNull) return item.leftAmount;
    int leftValue;
    if (item.code & leftHasChar) leftValue = item.leftAmount;
    else leftValue = valueOf(*item.leftSubBranch);
    int rightValue;
    if (item.code & rightHasChar) rightValue = item.rightAmount;
    else rightValue = valueOf(*item.rightSubBranch);
    return leftValue + rightValue;
}

int compare(Branch* b1, Branch* b2){
    int v1 = valueOf(*b1);
    int v2 = valueOf(*b2);
    if (v1<v2) return -1;
    if (v1>v2) return 1;
    return 0;
}

LinkedList* sort(LinkedList* list){
    LinkedList* first = list;
    LinkedList* twoBack = 0;
    LinkedList* oneBack = first;
    LinkedList* current = oneBack->next;
    while (true){
        int diff = compare(oneBack->this, current->this);
        if (diff <= 0){
            twoBack=oneBack;
            oneBack=current;
            current=current->next;
            if (current==0) break;
        } else {
            if (twoBack == 0){
                first = current;
            } else {
                twoBack->next = current;
            }
            oneBack->next = current->next;
            current->next = oneBack;
            twoBack=0;
            oneBack=first;
            current = oneBack->next;
        }
    }
}

LinkedList* createLinkedList(char* charCount){
    LinkedList* tmp = newLinkedList();
    for (int i = 0; i < 256; i++){
        char c = *(charCount+i);
        if (c) add(tmp, newSemiNull((unsigned char)i, c));
    }
    tmp = tmp->next;        //the first item is a misc
    tmp = sort(tmp);
    return tmp;
}

Branch* combinedBranch(Branch* b1, Branch* b2){
    Branch* result = (Branch*) malloc(sizeof(Branch));
    result->code = 0;
    result->leftSubBranch = b1;
    result->rightSubBranch = b2;
    return result;
}

LinkedList* insert(LinkedList* list, Branch* item){
    LinkedList* newListItem = (LinkedList*) malloc(sizeof(LinkedList));
    newListItem->this = item;
    newListItem->next = 0;
    int branchValue = valueOf(*item);
    if (!compare(item, list->this)<0){
        newListItem->next = list;
        return newListItem;
    }
    LinkedList* previous;
    LinkedList* currentListItem = list;
    do{
        previous = currentListItem;
        currentListItem = currentListItem->next;
        if (previous->next == 0){
            previous->next = newListItem;
            return list;
        }

    } while(compare(item, currentListItem->this)<0);
    previous->next = newListItem;
    newListItem->next = currentListItem;
    return list;
}

Branch* createTree(LinkedList* list){
    LinkedList* thirdLast;
    LinkedList* secondLast;
    LinkedList* last;
    while (list->next != 0){
        thirdLast = list;
        secondLast = list->next;
        if (secondLast->next == 0){
            last = secondLast;
            secondLast = list;
        } else {
            last = secondLast->next;
            while (last->next){
                last = last->next;
                secondLast = secondLast->next;
                thirdLast = thirdLast->next;
            }
        }
        list = insert(list, combinedBranch(secondLast->this, last->this));
        thirdLast->next = 0;
    }
}

Branch* removeSemiNull(Branch* tree){

}

Compressor compress(char* string)
{
    char* charCount = countChars(string);
    LinkedList* list = createLinkedList(charCount);
    Branch* tree = createTree(list);
    tree = removeSemiNull(tree);
}

char* unCompress(Compressor compressor){
    return (char*) malloc(1);
}

void main()
{
    char* string ="ABCDEFGHIJKLMNOPabcdefhijklmnop";
    Compressor compressedString = compress(string);
    //printf(unCompress(compressedString));
}


