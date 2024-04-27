#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

#define MAX 500

typedef struct Artista{
    char nome[800];
    char tipo[800];
    char nacionalidade[800];
    char albuns[800];

} Artista;


typedef struct listaAB{
    Artista *AB;
    int quantidade;
} listaAB;

typedef struct Menu{
    int opcao;
    char BuscandoPorNome[100];
    char BuscandoPorAlbum[100];
    int ResulradoBusca;
    char NovoNome[100];
    char NovoGenero[200];
    char NovaNacionalidade[800];
    int Busca;

    } Menu;

int Sort(const void *a, const void *b){
    return strcmp(((Artista *)a)->nome, ((Artista *)b)->nome);
}


void Iniciandolistaab(listaAB *listaab){
    listaab->AB = NULL;
    listaab->quantidade = 0;
}


void InserindoArtista(listaAB *listaab, const Artista *artista){
    listaab->quantidade++;
    listaab->AB = (Artista *)realloc(listaab->AB, listaab->quantidade * sizeof(Artista));
    if (listaab->AB == NULL){
        printf("Erro.\n");
        exit(1);
    }
    listaab->AB[listaab->quantidade - 1] = *artista;
}


void imprimirlistaab(listaAB *listaab){
    for (int i = 0; i < listaab->quantidade; i++){
        printf("Nome: %s\n", listaab->AB[i].nome);
        printf("Genero: %s\n", listaab->AB[i].tipo);
        printf("Nacionalidade: %s\n", listaab->AB[i].nacionalidade);
        printf("Albuns:\n%s\n", listaab->AB[i].albuns);
        printf("==================\n");
    }
}

void Liberarlistaab(listaAB *listaab){
    free(listaab->AB);
    listaab->AB = NULL;
    listaab->quantidade = 0;
}

int buscaBinaria(listaAB *listaab, char *nome){
    int esq = 0;
    int dir = listaab->quantidade - 1;

    while (esq <= dir){
        int referencia = esq + (dir - esq) / 2;
        int cmp = strcmp(listaab->AB[referencia].nome, nome);

        if (cmp == 0){
            return referencia;
        }
        else if (cmp < 0){
            esq = referencia + 1;
        }
        else{
            dir = referencia - 1;
        }
    }

    return -1;
}

void Ordenando(listaAB *listaab, const Artista *artista, const char *arquivo){
    int PosInicial = 0;

    while (PosInicial < listaab->quantidade && strcmp(artista->nome, listaab->AB[PosInicial].nome) > 0){
        PosInicial++;
    }

    listaab->quantidade++;
    listaab->AB = (Artista *)realloc(listaab->AB, listaab->quantidade * sizeof(Artista));

    if (listaab->AB == NULL){
        perror("Erro.\n");
        exit(1);
    }

    for (int i = listaab->quantidade - 1; i > PosInicial; i--){
        listaab->AB[i] = listaab->AB[i - 1];
    }

    listaab->AB[PosInicial] = *artista;

    FILE *albumArquivo = fopen(arquivo, "w");
    if (albumArquivo == NULL){
        perror("Erro ao abrir arquivo.\n");
        exit(1);
    }

    for (int i = 0; i < listaab->quantidade; i++){
        fprintf(albumArquivo, "%s\n%s\n%s\n%s\n==========\n", listaab->AB[i].nome, listaab->AB[i].tipo, listaab->AB[i].nacionalidade, listaab->AB[i].albuns);
    }

    fclose(albumArquivo);
}

void removerArtista(listaAB *listaab, int posicao){
    if (posicao < 0 || posicao >= listaab->quantidade){
        perror("Posicao invalida.\n");
        return;
    }

    FILE *arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL){
        perror("Erro.\n");
        exit(1);
    }

    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL){
        perror("Erro.\n");
        fclose(arquivoTemp);
        exit(1);
    }

    int parametro = 0;
    char parametroTexto[MAX];
    Artista artista;

    while (fgets(parametroTexto, MAX, arquivo)){
        parametroTexto[strcspn(parametroTexto, "\n")] = '\0';

        if (strcmp(parametroTexto, "==========") == 0){
            if (parametro >= 4){
                if (parametro / 4 != posicao){
                    fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n==========\n", artista.nome, artista.tipo, artista.nacionalidade, artista.albuns);
                }
            }
            parametro = 0;
        }
        else{
            switch (parametro){
            case 0:
                strcpy(artista.nome, parametroTexto);
                break;
            case 1:
                strcpy(artista.tipo, parametroTexto);
                break;
            case 2:
                strcpy(artista.nacionalidade, parametroTexto);
                break;
            case 3:
                strcpy(artista.albuns, parametroTexto);
                break;
            }
            parametro++;
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("artistas.txt");
    rename("temp.txt", "artistas.txt");

    for (int i = posicao; i < listaab->quantidade - 1; i++){
        listaab->AB[i] = listaab->AB[i + 1];
    }

    listaab->quantidade--;
    listaab->AB = (Artista *)realloc(listaab->AB, listaab->quantidade * sizeof(Artista));
    if (listaab->quantidade == 0){
        free(listaab->AB);
        listaab->AB = NULL;
    }
}

void editar_Artista(listaAB *listaab, int posicao, const Artista *novoArtista){
    if (posicao < 0 || posicao >= listaab->quantidade){
        perror("Posicao invalida.\n");
        return;
    }

    FILE *arquivoTemp = fopen("temp.txt", "w");
    if (arquivoTemp == NULL){
        perror("Erro.\n");
        exit(1);
    }

    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL){
        perror("Erro.\n");
        fclose(arquivoTemp);
        exit(1);
    }

    int parametro = 0;
    char parametroTexto[MAX];
    Artista artista;

    while (fgets(parametroTexto, MAX, arquivo)){
        parametroTexto[strcspn(parametroTexto, "\n")] = '\0';

        if (strcmp(parametroTexto, "==========") == 0){
            if (parametro >= 4){
                if (parametro / 4 != posicao){
                    fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n==========\n", artista.nome, artista.tipo, artista.nacionalidade, artista.albuns);
                }
                else{
                    fprintf(arquivoTemp, "%s\n%s\n%s\n%s\n==========\n", novoArtista->nome, novoArtista->tipo, novoArtista->nacionalidade, novoArtista->albuns);
                }
            }
            parametro = 0;
        }
        else{
            switch (parametro){
            case 0:
                strcpy(artista.nome, parametroTexto);
                break;
            case 1:
                strcpy(artista.tipo, parametroTexto);
                break;
            case 2:
                strcpy(artista.nacionalidade, parametroTexto);
                break;
            case 3:
                strcpy(artista.albuns, parametroTexto);
                break;
            }
            parametro++;
        }
    }

    fclose(arquivo);
    fclose(arquivoTemp);

    remove("artistas.txt");
    rename("temp.txt", "artistas.txt");

    listaab->AB[posicao] = *novoArtista;
}

int buscaSequencial(listaAB *listaab, char *album){
    for (int i = 0; i < listaab->quantidade; i++)
    {
        if (strstr(listaab->AB[i].albuns, album) != NULL)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    listaAB listaab;
    Menu Menu;
    Iniciandolistaab(&listaab);

    FILE *arquivo = fopen("artistas.txt", "r");
    if (arquivo == NULL)
    {
        perror("Erro ao abrir o arquivo\n");
        exit(1);
    }

    char parametroTexto[MAX];
    Artista artista;
    int parametro = 0;

    while (fgets(parametroTexto, MAX, arquivo)){
        parametroTexto[strcspn(parametroTexto, "\n")] = '\0';

        if (strcmp(parametroTexto, "==========") == 0){
            if (parametro >= 4){
                InserindoArtista(&listaab, &artista);
            }
            parametro = 0;
        }
        else{
            switch (parametro){
            case 0:
                strcpy(artista.nome, parametroTexto);
                break;
            case 1:
                strcpy(artista.tipo, parametroTexto);
                break;
            case 2:
                strcpy(artista.nacionalidade, parametroTexto);
                break;
            case 3:
                strcpy(artista.albuns, parametroTexto);
                break;
            default:
                strcat(artista.albuns, "\n");
                strcat(artista.albuns, parametroTexto);
                break;
            }
            parametro++;
        }
    }
    fclose(arquivo);


    do{
        printf("\nMenu de Interacao :\n");
        printf("(1) - Buscar Artistas ou Bandas por nome\n");
        printf("(2) - Buscar Artistas ou Bandas por álbum\n");
        printf("(3) - Adicionar Artistas ou Bandas\n");
        printf("(4) - Editar Artistas ou Bandas\n");
        printf("(5) - Remover Artistas ou Bandas\n");
        printf("(6) - Mostrar Lista de Artistas e Bandas\n");
        printf("(7) - Sair\n");
        printf("\nEscolha uma das opcoes(Informe o valor): ");
        scanf("%d", &Menu.opcao);

        switch (Menu.opcao){
        case 1:
            printf("\n\nInforme o Artista ao Banda para pesquisa: ");
            getchar();
            fgets(Menu.BuscandoPorNome, sizeof(Menu.BuscandoPorNome), stdin);
            Menu.BuscandoPorNome[strcspn(Menu.BuscandoPorNome, "\n")] = '\0';

            Menu.Busca = buscaBinaria(&listaab, Menu.BuscandoPorNome);

            if (Menu.Busca != -1){
                printf("\nArtista ou Bandaencontrado\n");
                printf("Nome: %s\n", listaab.AB[Menu.Busca].nome);
                printf("Gênero Musical: %s\n", listaab.AB[Menu.Busca].tipo);
                printf("Local de Nascimento: %s\n", listaab.AB[Menu.Busca].nacionalidade);
                printf("Álbuns:\n%s\n", listaab.AB[Menu.Busca].albuns);
            }
            else{
                printf("Artista ou Banda nao encontrado\n");
            }
            break;

        case 2:
            printf("\n\nInforme o nome do album que você deseja encontrar: ");
            getchar();
            fgets(Menu.BuscandoPorAlbum, sizeof(Menu.BuscandoPorAlbum), stdin);
            Menu.BuscandoPorAlbum[strcspn(Menu.BuscandoPorAlbum, "\n")] = '\0';

            Menu.ResulradoBusca = buscaSequencial(&listaab, Menu.BuscandoPorAlbum);

            if (Menu.ResulradoBusca != -1)
            {
                printf("\nAlbum encontrado\n Especicacoes do Criador do Album:\n");
                printf("Nome: %s\n", listaab.AB[Menu.ResulradoBusca].nome);
                printf("Albuns:\n%s\n", listaab.AB[Menu.ResulradoBusca].albuns);
            }
            else
            {
                printf("\nalbum nao encontrado. \n");
            }
            break;

        case 3:
            printf("\nInfomre o nome do Artista ou Banda: ");
            getchar();
            fgets(artista.nome, sizeof(artista.nome), stdin);
            artista.nome[strcspn(artista.nome, "\n")] = '\0';

            printf("Informe o Genero Musical: ");
            fgets(artista.tipo, sizeof(artista.tipo), stdin);
            artista.tipo[strcspn(artista.tipo, "\n")] = '\0';

            printf("Informe a Nacionalidade: ");
            fgets(artista.nacionalidade, sizeof(artista.nacionalidade), stdin);
            artista.nacionalidade[strcspn(artista.nacionalidade, "\n")] = '\0';

            printf("Informe os Albuns (Separe com Virgula): ");
            fgets(artista.albuns, sizeof(artista.albuns), stdin);
            artista.albuns[strcspn(artista.albuns, "\n")] = '\0';

            Ordenando(&listaab, &artista, "artistas.txt");
            printf("\nArtista adicionado.\n");
        break;

        case 4:
            printf("\n\nInforme o nome do Artista ou Banda: ");
            getchar();
            fgets(Menu.BuscandoPorNome, sizeof(Menu.BuscandoPorNome), stdin);
            Menu.BuscandoPorNome[strcspn(Menu.BuscandoPorNome, "\n")] = '\0';

           Menu.Busca = buscaBinaria(&listaab, Menu.BuscandoPorNome);

            if (Menu.Busca != -1){
                printf("\nInforme o novo Nome do Artisa ou Banda: ");
                fgets(Menu.NovoNome, sizeof(Menu.NovoNome), stdin);
                Menu.NovoNome[strcspn(Menu.NovoNome, "\n")] = '\0';

                printf("Informe o novo genero musical: ");
                fgets(Menu.NovoGenero, sizeof(Menu.NovoGenero), stdin);
                Menu.NovoGenero[strcspn(Menu.NovoGenero, "\n")] = '\0';

                printf("Informe a nova nacionalidade: ");
                fgets(Menu.NovaNacionalidade, sizeof(Menu.NovaNacionalidade), stdin);
                Menu.NovaNacionalidade[strcspn(Menu.NovaNacionalidade, "\n")] = '\0';

                strcpy(artista.nome, Menu.NovoNome);
                strcpy(artista.tipo, Menu.NovoGenero);
                strcpy(artista.nacionalidade, Menu.NovaNacionalidade);

                editar_Artista(&listaab, Menu.Busca, &artista);
                printf("\nArtista editado.\n");
            }
            else{
                printf("\nArtista nao encontrado para ser editado.\n");
            }
        break;

        case 5:
            printf("\n\nInforme o nome do artista a ser removido: ");
            getchar();
            fgets(Menu.BuscandoPorNome, sizeof(Menu.BuscandoPorNome), stdin);
            Menu.BuscandoPorNome[strcspn(Menu.BuscandoPorNome, "\n")] = '\0';

            Menu.Busca = buscaBinaria(&listaab, Menu.BuscandoPorNome);

            if (Menu.Busca != -1){
                removerArtista(&listaab, Menu.Busca);
                printf("\nArtista removido.\n");
            }
            else{
                printf("\nArtista nao encontrado.\n");
            }
        break;


        case 6:
            printf("\nLista de Artista e Bandas \n\n");
            qsort(listaab.AB, listaab.quantidade, sizeof(Artista), Sort);
            imprimirlistaab(&listaab);
            break;

        case 7:
            printf("Obrigado!!\n");
            break;

        default:
            printf("\nOpcao invalida. \nEscolha uma opçao de 1 a 7.\n");
            break;
        }

    } while (Menu.opcao != 7);

    Liberarlistaab(&listaab);

    return 0;
}