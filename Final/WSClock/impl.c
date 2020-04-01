//#include "types.h"
#include <stdio.h>
#include <limits.h>
#include "impl.h"

int MinFrameLRU(int frames,PagePTR IPT){

    int min=IPT[0].stamp;
    int thesis=0;

    for(int i=1; i<frames; i++){

        if ( (IPT[i].stamp)<min ){

            min=IPT[i].stamp;
            thesis=i;
        }
    }

    return thesis;
}

int MinFrameWS(int frames,PagePTR IPT,int* WSTime ){

    bool flag=false;
    int min=INT_MAX;
    int thesis=0;

    while(true){
        
        min=INT_MAX;
        for(int i=0; i<frames; i++){

            if( (IPT[i].stamp)<min ){
                min=IPT[i].stamp;
                thesis=i;
            }
        }   
   
        if( IPT[thesis].valbit==1 ){
            IPT[thesis].valbit=0;
            IPT[thesis].stamp=*WSTime;
            (*WSTime)++;
        }

        else{

            break;
        }
    }

    return thesis;
}
