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

bool isEmpty(int frames,PagePTR IPT){

    bool empty=false;

    for(int i=0; i<frames; i++){

        if( IPT[i].pid==0 ){
            empty=true;
        }
    }

    return empty;
}

int SameWS(int wscope,WSPtr WSize,char* page,int pid){

    int thesis=-1;

    for(int i=0; i<wscope; i++){

        if( (  strcmp(WSize[i].page,page))==0 && WSize[i].pid==pid ){

            thesis=i;
        }

    }

    return thesis;

}

int WSReplace(int wscope,WSPtr WSize){

    int thesis=0;
    int min=INT_MAX;

    for(int i=0; i<wscope; i++){

        if(WSize[i].stamp<min){

            min=WSize[i].stamp;
            thesis=i;
        }
    }

    return thesis;

}

//This functions,returns the number of the page in IPT, if it finds the same page in the IPT
int SameIPT(int frames,PagePTR IPT,char* page,int pid){

    int thesis=-1;

    for(int i=0; i<frames; i++){

        if ( strcmp(IPT[i].page,page)==0 && IPT[i].pid==pid ){

            thesis=i;
            break;
        }
    }

    return thesis;
}


int MinFrameWS(int frames,PagePTR IPT,int* WSTime,WSPtr WSize,bool empty,int wscope,char* page,int pid,int* PF){

    (*WSTime)++;
    int thesis;
    int thesisIPT;
    int i;
    int same;
    int same1;
    bool WSEmpty=false;

    if(*WSTime<=wscope){
        WSEmpty=true;
    }

    if(empty==true){                                //If IPT is empty

        same1=SameIPT(frames,IPT,page,pid);
        if (same1!=-1){

            printf("%d\n",thesisIPT);
            thesisIPT=same1;

        }

        else{

            for(i=0; i<frames; i++){

                if(IPT[i].pid==0){

                    thesisIPT=i;                        //This page we are going to return when the IPT is empty!
                    break;
                }
            }
        }

        if(WSEmpty==true){                          //If WS is empty when IPT was empty

            for(i=0; i<wscope; i++){

                same=SameWS(wscope,WSize,page,pid);
                if(same!=-1 ){   //If we have the same page again in WS

                    WSize[same].stamp=*WSTime;
                    break;
                }

                else if(WSize[i].stamp==0){                         
                    
                    (*PF)++;
                    strcpy(WSize[i].page,page);
                    WSize[i].stamp=*WSTime;
                    WSize[i].pid=pid;
                    break;
                }
            }
        }

        else{                                       //If WS is not empty when IPT was not empty

            same=SameWS(wscope,WSize,page,pid);     
            if (same!=-1){                          //if we have the page in the WS

                WSize[same].stamp=*WSTime;
            }

            else{                                   //else

                thesis=WSReplace(wscope,WSize);
                (*PF)++;
                strcpy(WSize[thesis].page,page);
                WSize[thesis].stamp=*WSTime;
                WSize[thesis].pid=pid;
                
            }
        }
    }

    else{                                           //If IPT is full,then delete all the pages who are not in the Working Set!

        for(i=0; i<frames; i++){

            same=SameWS(wscope,WSize,IPT[i].page,IPT[i].pid);
            
            if(same==-1){                           //If we have not a match in IPT,then (delete) overwrite this page with NULL Page

                IPT[i].valbit=0;
                IPT[i].pid=0;
                strcpy(IPT[i].page,"fffff");
                IPT[i].token='N';
                IPT[i].stamp=-1;
            }

        }

        empty=isEmpty(frames,IPT);

        if(empty==true){                                //If IPT is empty

            same=SameIPT(frames,IPT,page,pid);

            if (same!=-1){

                thesisIPT=same;
            }

            else{

                for(i=0; i<frames; i++){

                    if(IPT[i].pid==0){

                        thesisIPT=i;
                        break;
                    }
                }
            }   

        }

        if(WSEmpty!=true){                                       //If WS is not empty when IPT was not empty

            same=SameWS(wscope,WSize,page,pid);     
            if (same!=-1){                          //if we have the page in the WS

                WSize[same].stamp=*WSTime;
            }

            else{//else
                                   
                thesis=WSReplace(wscope,WSize);

                strcpy(WSize[thesis].page,page);
                WSize[thesis].stamp=*WSTime;
                WSize[thesis].pid=pid;
                
            }

        }

    }

    return thesisIPT;
}
