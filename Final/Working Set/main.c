#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "impl.h"

int main(int argc, char* argv[]){

    int frames,q,wscope;
    unsigned int maxreports;
    char* PRA;

    if (argc<5){
        printf("We have INPUT ERROR,not enough arguments!\n");
        return -1;
    }

    else if( argc>6 ){
        printf("We have INPUT ERROR,too many arguments!\n");
        return -1;
    }

    else{

        PRA=argv[1];
        frames=atoi(argv[2]);

        if (frames<1){
            printf("We have INPUT ERROR, frames cannot be zero or less\n");
            return -1;
        }

        q=atoi(argv[3]);

        if (q<1){
            printf("We have INPUT ERROR, arg 'q' cannot be zero or less\n");
            return -1;
        }

        if (  (strcmp("LRU",PRA) )==0 ){
            //printf("You choose LRU algorithm!\n");
            if (argc==6){
                printf("You can't give more than 4 arguments when you choose LRU!\n");
                return -1;
            }
            maxreports=atoi(argv[4]);

            if (maxreports<1 || maxreports>1000000){
                printf("We have INPUT ERROR, Max Reports to be readen must be between 0 and 1.000.000 \n");
                return -1;
            }
        }

        else if (  (strcmp("WS",PRA) )==0 ){
            //printf("You choose LRU algorithm!\n");
            if (argc==5){
                printf("You can't give less than 5 arguments when you choose WS!\n");
                return -1;
            }
            maxreports=atoi(argv[4]);

            if (maxreports<1 || maxreports>1000000){
                printf("We have INPUT ERROR, Max Reports to be readen must be between 0 and 1.000.000 \n");
                return -1;
            }
            wscope=atoi(argv[5]);

            if (wscope<1){
                printf("We have INPUT ERROR, WS Parametre can't be zero or less");
                return -1;
            }
        }

        else {
            printf("We have INPUT ERROR,not a valid Page Replacement Algorithm's name!\n");
            return -1;
        }
    }

    printf("##############################################################################\n");
    printf("                           'Welcome to our virtual memory management'\n ");
    printf("-------------------------------------------------------------------------------\n\n");
    printf("                           Todays Page Replacement Algorithm menu is:\n\n      ");
    printf("                 ################                ################                 \n");
    printf("                       #              #                #              #                 \n");
    printf("                       #              #                #              #                  \n");
    printf("                       #     LRU      #                #      WS      #                  \n");
    printf("                       #              #                #              #                  \n");
    printf("                       ################                ################                  \n\n\n");

    if (  (strcmp("LRU",argv[1]) )==0 ){
        printf("You choose LRU algorithm!\n");
    }

    else{
        printf("You choose WS algorithm!\n");
    }

    /*          Declaring Variables         */

    PagePTR IPT;                //Our Inverted Page Table we gonna use to do our stuff
    ProPTR PRO;                 //Our Process Table to "jump" from on process to another
    WSPtr WSize;                //For Windows Size Algorithm

    FILE* TotalEntries;         //File we gonna write the entries we have "tested"
    FILE* gcc;                  //For gcc file
    FILE* bzip;                 //For bzip file
    FILE* test;                 //for tests

    int Process;                //The each time Process
    int i,j;                    //For the Loops
    int thesis;                 //If we have free frame. (This happens only in the first n frames)
    int repcounter=0;           //Counter for the reports
    int PageFault=0;            //Counter for the page faults
    int RC=0;                   //Read Counter
    int WC=0;                   //Write Counter
    int sw=0;                   //For switching processes
    int WSCounter=0;

    char testpage[10];          //Page that we are going to compare at IPT
    char disk[12];
    char string1[5];
    char c;                     //Needed for copying token!
    char *wstring;

    bool match;                 //If we have a match flag
    bool Free;
    bool LRU=false;             //LRU or WS Algorithm!
    bool empty;                 //For WS Algorithm


    /*          Declaring Variables         */

    if( (strcmp(PRA,"LRU")==0) ){

        LRU=true;

    }

    gcc=fopen("gcc.trace","r");    //Opens and read file trace
    if (gcc==NULL){
        printf("Error opening the file!\n");
        exit(EXIT_FAILURE);
    }

    bzip=fopen("bzip.trace","r");   //OPens and read file trace
    if (bzip==NULL){

        printf("Error opening the file!\n");
        exit(EXIT_FAILURE);
    }

    TotalEntries=fopen("Entries.txt","w+");
    if (TotalEntries==NULL){

        printf("Error creating the file!\n");
        exit(EXIT_FAILURE);
    }

    test=fopen("test.trace","r");
    if (test==NULL){

        printf("Error creating the file!\n");
        exit(EXIT_FAILURE);
    }


    //  Creating the Page Table
    //  Pages==Frames

    IPT=(Page*)malloc(frames*sizeof(Page));
    if (IPT==NULL){
        printf("Problem in allocating memory for IPT\n");
        return -1;
    }

    //Creeating the Process Table

    PRO=(ProPTR)malloc(2*sizeof(process));
    if (PRO==NULL){
        printf("Problem in allocating memory for Process Table\n");
        return -1;
    }

    if(LRU!=true){

        WSize=(WSPtr)malloc(wscope*sizeof(WorkingSet));
        if (WSize==NULL){
            printf("Problem in allocating memory for Working Set Table\n");
            return -1;

        }
    }


    for(i=0; i<frames; i++){

        IPT[i].valbit=0;
        IPT[i].pid=0;
        IPT[i].page=malloc(6*1);

        strcpy(IPT[i].page,"fffff");
        IPT[i].token='N';
        IPT[i].stamp=-1;

    }

    for(i=0; i<2; i++){

        PRO[i].pnum=i+1;
        PRO[i].MaxRep=0;
        PRO[i].flag=false;

        if (i==0){

            PRO[i].file=gcc;
        }

        else{

            PRO[i].file=bzip;
        }
    }

    if(LRU!=true){
        for(i=0; i<wscope; i++){

            WSize[i].page=malloc(6*1);
            strcpy(WSize[i].page,"fffff");
            WSize[i].stamp=0;

        }
    }

    wstring=malloc(6*1);

    /*if( (strcmp(PRA,"LRU")==0) ){

        LRU=true;

    }*/

    //Read from trace files while we don't get over: maxreports


    while(true){

        for(i=0; i<q; i++){                                                 //Read q reports, in each process

            PRO[sw].MaxRep=PRO[sw].MaxRep+1;
            repcounter++;

            if(fgets(testpage,sizeof(testpage),PRO[sw].file)==NULL){        //While we didn't reach the end of file

                printf("Problem copying from file to string\n");
                printf("Probably EOF!\n");
            }

            else{                                                           //If we have traces to read

                strncpy(string1,testpage,5);
                strncpy(disk,testpage,sizeof(disk));

                char c;
                c=getc(PRO[sw].file);
                if (c=='R'){
                    RC++;
                }

                else if (c=='W'){

                    WC++;
                }

                fgets(testpage,sizeof(testpage),PRO[sw].file);

                Process=PRO[sw].pnum;                                       //P1==1
                match=false;                                                //For the matching page
                Free=false;
                thesis=-1;                                                  //For the free frame place to put our next page

                for(j=0; j<frames; j++){                                    //For all the IPT that we have

                    if(IPT[j].pid==0 && Free==false){                       //If we find a free slot,get in there! (Only in the start).
                        thesis=j;
                        Free=true;
                    }

                    if( (strcmp( IPT[j].page,string1 ) )==0 && ( (IPT[j].pid)==Process && LRU==true) ) {         //If we have a match!

                        match=true;

                        IPT[j].valbit=1;

                        if( LRU==true ){
                            IPT[j].stamp=repcounter;
                            IPT[j].valbit=1;                                //No needed(?)
                        }

                        break;
                    }
                }

                if(match==false){                                       //Page FAULT! We don't have this particular page in our memory

                    if(LRU==true){

                        PageFault++;
                    }

                    //WSCounter++;

                    if(thesis!=-1){                                     //Searching for a free frame place to put this page

                        if(LRU==true){

                            strcpy( IPT[thesis].page,string1 );             //Copying the page

                            IPT[thesis].token=c;
                            IPT[thesis].pid=Process;
                            if (LRU==true){
                                IPT[thesis].stamp=repcounter;
                            }

                            else{

                                IPT[thesis].stamp=WSCounter;
                            }

                        }

                        else{

                            empty=isEmpty(frames,IPT);

                            strcpy(wstring,string1);
                            //printf("%s\n",wstring);
                            thesis=MinFrameWS(frames,IPT,&WSCounter,WSize,empty,wscope,wstring,Process,&PageFault);
                            //printf("%d\n",thesis);

                            strcpy( IPT[thesis].page,string1 );
                            IPT[thesis].token=c;
                            IPT[thesis].pid=Process;
                            IPT[thesis].stamp=WSCounter;
                        }

                    }

                    else{                                               //LRU or WS going to be implemented!

                        //printf("%s\n",PRA);


                        /*      LRU Algorithm       */

                        if( strcmp(PRA,"LRU")==0 ){

                            thesis=MinFrameLRU(frames,IPT);
                            //printf("%d\n",thesis);

                            strcpy( IPT[thesis].page,string1 );
                            IPT[thesis].token=c;
                            IPT[thesis].pid=Process;
                            IPT[thesis].stamp=repcounter;

                        }

                        /*      LRU Algorithm       */


                        /*##########################*/


                        /*      WS  Algorithm       */

                        else {

                            empty=isEmpty(frames,IPT);
                            strcpy(wstring,string1);
                            //printf("%s\n",wstring);

                            thesis=MinFrameWS(frames,IPT,&WSCounter,WSize,empty,wscope,wstring,Process,&PageFault);
                            //printf("%d\n",thesis);

                            strcpy( IPT[thesis].page,string1 );
                            IPT[thesis].token=c;
                            IPT[thesis].pid=Process;
                            IPT[thesis].stamp=WSCounter;

                        }

                        /*      WS  Algorithm       */

                    }

                }

                if( PRO[sw].pnum==1){

                    fprintf(TotalEntries,"From gcc: %s %c\n",disk, c);

                }

                else if(PRO[sw].pnum==2){

                    fprintf(TotalEntries,"From bzip:%s %c\n",disk, c);

                }

            }

            if (PRO[sw].MaxRep>=maxreports){

                PRO[sw].flag=true;
                break;
            }

        }


        if (sw==0){
            sw=1;
        }

        else{
            sw=0;
        }


        if( PRO[0].flag==true && PRO[1].flag==true ){

            break;
        }

    }

    printf("\nPrinting the frames\n\n");

    printf("------------------\n");


    for(i=0; i<frames; i++){

        printf("%d ",IPT[i].valbit);
        printf("%d ",IPT[i].pid);
        printf("%d ",IPT[i].stamp);
        printf("%c ",IPT[i].token);
        printf("%s \n\n",IPT[i].page);

    }

    printf("-------------------\n\n");

    if(LRU!=true){
        printf("Printing the Working Set\n\n");

        printf("-------------------\n");

        for(i=0; i<wscope; i++){

            printf("%d ",WSize[i].pid);
            printf("%d ",WSize[i].stamp);
            printf("%s \n\n",WSize[i].page);

        }
    }


    printf("-------------------\n\n");


    printf("Total Reads: %d and Total Writes: %d\n",RC,WC);
    printf("These are the total Page Faults:%d\n",PageFault);
    printf("Frame number that we used was: %d\n",frames);
    printf("Max Reports to be readen are(in each file): %d\n",maxreports);
    printf("*Please remember to check the 'Entries.txt' file*\n");

    //Closing the files

    fclose(gcc);
    fclose(bzip);
    fclose(TotalEntries);
    fclose(test);

    //Freeing the memory

     for(i=0; i<frames; i++){

        free(IPT[i].page);
    }

    if(LRU!=true){
        for(i=0; i<wscope; i++){

            free(WSize[i].page);
        }

        free(WSize);
    }

    free(IPT);
    free(PRO);
    free(wstring);

    return 0;
}
