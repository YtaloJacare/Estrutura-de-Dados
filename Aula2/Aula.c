#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Aula2.h"

struct Aluno{
    int idade;
    char nome[30];
    float nota;
};

int ultimaPosLivre = 0;

struct Aluno *criarLista(int numAlunos){
    //usando alocação estática
    //struct Aluno alunos[numAlunos];

    //alocação dinamica

    struct Aluno *alunos = (struct Aluno*) malloc(numAlunos*sizeof(Aluno));

    return alunos;
}

void adicionarAluno(Aluno **lista, Aluno aluno){
    strcpy(*lista)([ultimaPosLivre].nome, aluno.nome); 
    (*lista)[ultimaPosLivre].idade = aluno.idade;
    (*lista)[ultimaPosLivre].nota = aluno.nota;
    ultimaPosLivre++;

    printf("\nUltima posicao livre %d", ultimaPosLivre);
}

void listarAlunos(Aluno *lista){
    for(int i = 0; i < ultimaPosLivre; i++){
        printf("\nAluno: %d\n", i + 1);
        printf("\nNome: %s\n", lista[i].nome);
        printf("\nIdade: %d\n", lista[i].idade);
        printf("\nNota: %f\n", lista[i].nota);
    }
}

int main(){
    struct Aluno *alunos;
    alunos = criarLista(10);
    
    struct Aluno aluno1, aluno2;
    strcpy(aluno1.nome, "Joao");
    aluno1.idade = 20;
    aluno1.nota = 9.9;

 
    strcpy(aluno2.nome "Jaca");
    aluno2.idade = 21; 
    aluno2.nota = 9.9;

    adicionarAluno(&alunos, aluno1);
    adicionarAluno(&alunos, aluno2);
    listarAlunos(alunos);

    return 0;
}

