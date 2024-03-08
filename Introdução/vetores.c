#include<stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(){
    
    int valores[2];

    valores[0] = 1;
    valores[1] = 2;

    setlocale(LC_ALL, "Portuguese");
    printf("Valores[0]: %d", valores[0]);

    printf("\nValores[01]: %d", valores[1]);

    printf("\nValores na [0]: %p", valores);

    printf("\nValores na [1]: %p", valores +1);

    printf("\nValores: %d", *valores);
    
    printf("\nValores[0]: %d", *valores + 1);



    return 0;
}