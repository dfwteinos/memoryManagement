#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "impl.h"

#define GAY 4096

int main(void){



   //FILE* fp1=fopen("Files.txt","r");
   //FILE* fp2=fp1;

   //fclose(fp1);

   int x=5;
   int y=2;

   Test(&x,&y);
   printf("x is: %d\n",x);
   printf("y is: %d\n",y);


   /*//printf("%d",GAY);
   //printf("%lu",sizeof("05e06600 W"));
   char* string1;
   char string2[12];

   //string1="05e06600 W";
   //printf("%c\n",string1[9]);

   FILE* fp=fopen("test.txt","r");
     
   if(fgets(string2,sizeof(string2),fp)!=NULL){
      
      //printf("Can't copy the string to the file");
      printf("%s\n",string2);
   }
    
   while(fgets(string2,sizeof(string2),fp)!=NULL){

      printf("%s\n",string2);
      //rewind(fp);
   
   }

   printf("End of file!\n");
   printf("Not anymore!\n");

   rewind(fp);

   while(fgets(string2,sizeof(string2),fp)!=NULL){


      printf("%s\n",string2);

   }

   char test[5];
   strncpy(test,string2,5);
   printf("%s\n",test);

   char okay;
   //okay=(char*)malloc(5*1);

   //strcpy(okay,test);
   rewind(fp);
   okay=getc(fp);
   printf("%c\n",okay);

   char c='N';
   printf("%c",c);

   if (c=='N'){
      printf("OKEI");
   }

   /*
   char testing[3];
   strcpy(testing,"W\n");
   printf("%s\n",testing);
   char* testing1=malloc(2*1);
   testing1=strtok(testing,"\n");
   printf("%s\n",testing1);

   strcpy(testing,"R\n");
   printf("%s\n",testing1);*/

   


   //char token[1];

   //strcpy(token,string2);
   //printf("%s\n",token);

   //char token[6];
   //char token2[5];

   //strcpy(token,"okd84");
   //strcpy(token2,token);
   //printf("%s\n",token);
   //printf("%s\n",token);


   //strcpy(token,string2[11]);

   //char string3[5];
   //char* gay="W";
   //char* str;
   //str=gay;
   //printf("%s\n",str);

   //strcpy(string3,gay);
   //printf("%s\n",string3);


   /*

   if(fgets(string2,sizeof(string2),fp)!=NULL){

      printf("%s\n",string2);
   
   }
   
   else{

      printf("End of file!\n");
   } 

   //printf("%s\n",string2);

   fclose(fp);
   return 0;




    /*
   FILE *fp;
   char str[60];

   /* opening file for reading 
   fp = fopen("file.txt" , "r");
   if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   }
   if( fgets (str, sizeof(str), fp)!=NULL ) {
      /* writing content to stdout 
      puts(str);
   }
   fclose(fp);
   
   return(0); */ 

}