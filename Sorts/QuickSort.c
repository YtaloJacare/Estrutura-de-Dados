#include<stdio.h>
#include<stdlib.h>


int partition(int *vetor, int esq, int dir){
    int pivot = vetor[esq];

    //indicador da esquerda
    int i = esq - 1;
    //indicador da  direita
    int j = dir + 1;

    while(1){
        do{
            i += 1;
        } while(vetor[i] < pivot);

        do{
            j -=1;
        } while(vetor[j] > pivot);

        if(i >= j){
            //retornando o pivo para a função quicksort
            return j;
        }

        int tmp = vetor[i];
        vetor[i] = vetor[j];
        vetor[j] = tmp;
    }
}


void quicksort(int*vetor, int esq, int dir){
    if(esq >= 0 && dir >= 0 && esq < dir){
        //selecionar um pivo
        int pivot = partition(vetor, esq, dir);
        //selecionar o pivo
        //chamar o quicksort com elemmentos a esquerda do pivot
        quicksort(vetor, esq, pivot);
        //chamar o quicksort com elemmentos a direita do pivot
        quicksort(vetor, pivot +1, dir);

    }
}


int main(){
    int vetor[] = {5, 1, 2, 10, 8, 7, 6, 3, 9, 4};


    quicksort(vetor, 0, 9);

    for(int i =0 ; i < 10; i++){
        printf("%d", vetor[i]);
    }


}