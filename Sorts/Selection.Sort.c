#include<stdio.h>
#include<stdlib.h>

int main(){

/*SelectionSort: um por um aachando o maior valor até o fim */

int vetor [] = {10, 42, 100, 150, 8, 9, 1, 0, 3, 7};
int tmp;
int maior = -1;
int posMaior = -1;

for(int j = 9; j >= 0; j--){
    maior = -1;
    //for para achar o maio valor//
    for(int i = 0; i <= j; i++){
        if(vetor[i] > maior){
            posMaior = i;
            maior = vetor[i];
        }
    }
    //troco ultimo elemento pelo valor encontrado
    tmp = vetor[posMaior];
    vetor[posMaior] = vetor[j];
    vetor[j] = tmp;
}




for (int i = 0; i < 10; i++)
{
    printf("%d ", vetor[i]);
}


}
