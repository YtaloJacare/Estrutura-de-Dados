#include<stdio.h>
#include<stdlib.h>

int main(){

/*BubbleSort: trocas entre duplas até o fim */

int vetor [] = {75, 96, 87, 14, 2, 1 ,30, 20, 5};
int tmp;

for(int j = 0; j < 9; j++){
    for (int i = 0; i < 9 - j; i++)
    {
        if (vetor[i] > vetor[i+1])
        {
            tmp = vetor[i];
            vetor[i] = vetor[i+1];
            vetor[i+1] = tmp;
        }
        
    }
    
}

for (int i = 0; i < 10; i++)
{
    printf("%d ", vetor[i]);
}


}
