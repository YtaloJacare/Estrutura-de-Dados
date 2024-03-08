#include<stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    
int valor = 1;
int *ponteiro;  // vair armazenar endereço
int valores[2];

ponteiro = &valor; //ponteiros armazenam endereços de memoria, pra usar essa função utilize o '&' na variavel

  
setlocale(LC_ALL, "Portuguese");
printf("Endereço do número: %p", &valor); //-> Diz o valor do endereço
printf("\nValor do número: %d", valor); //-> Diz o valor da variavel

printf("\nValor de ponteiro: %p", ponteiro); // mostrar oq o ponteiro guardou
printf("\nValor por meio da variavel ponteiro: %d", *ponteiro); // segunda função do '*'


return 0;

}

 