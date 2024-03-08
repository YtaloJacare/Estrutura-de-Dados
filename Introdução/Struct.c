#include<stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct Pessoa{
    int idade;
    char nome[30];
    float altura;
    
} Pessoa;

int main(){
    
    struct Pessoa pessoa1;
 
    pessoa1.idade = 20;
    pessoa1.altura = 1.8;
    strcpy(pessoa1.nome, "meuovokk");

    return 0;
}