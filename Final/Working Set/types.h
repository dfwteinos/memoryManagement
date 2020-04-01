#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define PAGESZ 4096
#define FRAMESZ 4096

struct SinglePage{

    int pid;
    int valbit;             // valid=1 | invalid=0
    char* page;
    char token;
    int stamp;
};

struct Process{

    int pnum;               //Process number
    FILE* file;
    int MaxRep;             //MaxRep counter
    bool flag;              //flag for max rep

};

struct WS{

    char* page;
    int stamp;
    int pid;

};

typedef struct Process process;
typedef struct Process* ProPTR;

typedef struct SinglePage Page;
typedef struct SinglePage* PagePTR;

typedef struct WS WorkingSet;
typedef struct WS* WSPtr;