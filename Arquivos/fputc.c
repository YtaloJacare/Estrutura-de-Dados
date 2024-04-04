#include<stdio.h>
#include<stdlib.h>

int main(){
    /*Para se escrever um caractere em um arquivo
    usamos a função fputc()*/

    //Forma Geral:

   /* int fputc(char c, FILE *fp); */

   FILE *f;
   f = fopen("arquivo.txt", "W");
   if(f==NULL){
    printf("\nErro na Abertura");
    exit(1);
   }
   char texto[20] = "Meu programa em C";
   int i;

   //grava a string caractere por caractere
   
   for(i = 0; i < strlen(texto) /*tamanho da string*/ ; i++)
   {
    fputc(texto[i], f); /*Texto na posição vai ser escrito no aqruivo F*/
   }

   fclose(f);  /*Sempre FECHE o arquivo*/

   return 0;
   
}