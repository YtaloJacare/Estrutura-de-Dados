#include<stdio.h>
#include<stdlib.h>

int main(){

/*A Linguagem C trabalha com apenas dois tipos de arquivos:
-Arquivos de Texto: pode ser editado bloco de notas
-Arquivos Binários: NÃO pode ser editado no bloco de Notas*/

/*Arquivos: Biblioteca stdio.h*/

/*A linguagem C usa um tipo especial de ponteiro para manipular
arquivos 

//Forma Geral: FILE *nome_ponteiro; */

FILE *nome_ponteiro;

/*É esse ponteiro que controla o fluxo de leitura
e escrita dentro de um arquivo*/

/*Abrindo Arquivo fopen, se não abrir o arquivo retorna NULL*/

nome_ponteiro = fopen("exemplo.txt", "w");
if(nome_ponteiro==NULL){
    printf("\nErro na Abertura!");
    exit(1); //Encerra o Programa
}

}