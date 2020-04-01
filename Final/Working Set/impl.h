#include "types.h"
#include <stdio.h>
#include <stdbool.h>

int MinFrameLRU(int,PagePTR);
int MinFrameWS(int,PagePTR,int*,WSPtr,bool,int,char*,int,int*);
bool isEmpty(int,PagePTR);
void Test(PagePTR);
int SameWS(int,WSPtr,char*,int);
