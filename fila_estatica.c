#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANHO_LISTA 5

typedef struct
{
    char nome[128];
    int idade;
}PESSOA;

typedef struct {
    PESSOA fila[TAMANHO_LISTA];
    int totalPessoas;
} FILA;

void LimparBuffer() {
    while (getchar() != '\n');
}

void Pause() {
    printf("\nTecle <ENTER> para continuar...");
    getchar();
}

void LimaparTela() {
    system("cls");
}

 void IniciarFila(FILA *pFila)
 {
    pFila->totalPessoas =0;
 }

 int TotalElementos(FILA *filaPessoa)
 {
    return filaPessoa->totalPessoas;
 }

int Inserir(FILA *filaPessoa, PESSOA pessoa) {
    if (filaPessoa->totalPessoas < TAMANHO_LISTA) {
        filaPessoa->fila[filaPessoa->totalPessoas] = pessoa;
        filaPessoa->totalPessoas++;

        return filaPessoa->totalPessoas - 1;
    }

    return -1;
}

void LeiaPessoa(PESSOA *pessoa)
{
    printf("Entre com o nome: ");
    scanf("%s", &pessoa->nome);
    LimparBuffer();

    printf("Entre com a idade: ");
    scanf("%d", &pessoa->idade);
    LimparBuffer();
}

void MantemInserir(FILA *filaPessoa) {
    if (TotalElementos(filaPessoa) >= TAMANHO_LISTA) {
        printf("\nImpossivel inserir!");
        printf("\nA fila esta cheia.\n\n");

        Pause();
    } else {
        PESSOA pessoa;
        LeiaPessoa(&pessoa);
        Inserir(filaPessoa, pessoa);
        Pause();
    }
}

void FilaAndar(FILA *listaPessoa) {
    int i = 0;

    for (i = 0; i < listaPessoa->totalPessoas; i++)
        listaPessoa->fila[i] = listaPessoa->fila[i + 1];
}

int Retirar(FILA *listaPessoa) {
    if (listaPessoa->totalPessoas > 0) {
        FilaAndar(listaPessoa);
        listaPessoa->totalPessoas--;

        return listaPessoa->totalPessoas;
    }

    return -1;
}

void MantemRetirar(FILA *listaPessoa) {
    LimaparTela();
    int retirouPessoa = Retirar(listaPessoa);

    if (retirouPessoa >= 0)
        printf("\nretirado com sucesso.\n");
    else {
        printf("\nImpossivel retirar!\n");
        printf("\nA fila esta vazia.\n");
    }

    Pause();
}
void ImprimirPessoa(PESSOA pessoa)
{
    printf("NOME...: %s \n", pessoa.nome);
    printf("IDADE..: %d \n\n", pessoa.idade);
}

void Listar(FILA *listaPessoa) {
    LimaparTela();
    printf("\n\nLISTA DE PESSOAS\n\n");

    if (listaPessoa->totalPessoas > 0) {
        int i = 0;
        for (i = 0; i < listaPessoa->totalPessoas; i++) {
            printf("REGISTRO NA POSICAO [%d]\n", i);
            ImprimirPessoa(listaPessoa->fila[i]);
        }
    } else
        printf("\nLista vazia...\n\n");

    Pause();
}

void Menu(int *opcaoSelecionar) {
    LimaparTela();
    printf("MENU   	\n");
    printf("----------------\n");
    printf("[1] - INSERIR	\n");
    printf("[2] - RETIRAR	\n");
    printf("[3] - LISTAR	\n");
    printf("[4] - SAIR		\n");
    printf("----------------\n");
    printf("\n\n");
    printf("OPCAO: ");
    scanf("%d", opcaoSelecionar);
    LimparBuffer();
}

int main() {
    int opcaoSelecionada = 0;
    FILA listaPessoas;
    IniciarFila(&listaPessoas);

    do {
        Menu(&opcaoSelecionada);

        switch (opcaoSelecionada) {
            case 1:
                MantemInserir(&listaPessoas);
                break;
            case 2:
                MantemRetirar(&listaPessoas);
                break;
            case 3:
                Listar(&listaPessoas);
                break;
        }
    } while (opcaoSelecionada != 4);

    return 0;
}