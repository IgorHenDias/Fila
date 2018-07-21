#include <stdio.h>
#include <stdlib.h>
#define TAMANHO_STR 128

typedef struct
{
	char nome[TAMANHO_STR];
	int idade;
} PESSOA;

typedef struct
{
	PESSOA elemento;
	PESSOA *proximo;
} PESSOA_ENCADEADA;

typedef struct
{
	PESSOA_ENCADEADA *fim;
	PESSOA *inicio;
	int totalElementos;
} FILA;

FILA *CriaFila()
{
	FILA *pFila = (FILA *)malloc(sizeof(FILA));
	pFila->inicio = NULL;
	pFila->fim = NULL;
	pFila->totalElementos = 0;

	return pFila;
}

void LiberarFila(FILA *pFila)
{
	PESSOA_ENCADEADA *pessoaAux = NULL;

	for (pessoaAux = pFila->inicio; pessoaAux != NULL; pessoaAux = pessoaAux->proximo)
		free(pessoaAux);

	free(pFila);
}

int FilaVazia(FILA *pFila)
{
	return (pFila->inicio == NULL);
}

void Inserir(FILA *pFila, PESSOA pessoa)
{
	PESSOA_ENCADEADA *novaPessoa = (PESSOA_ENCADEADA *)malloc(sizeof(PESSOA_ENCADEADA));
	novaPessoa->elemento = pessoa;
	novaPessoa->proximo = NULL;

	// SE FOR O PRIMEIRO ELEMENTO
	if (FilaVazia(pFila))
	{
		pFila->inicio = &(novaPessoa->elemento); // O INICIO APONTA PARA ELE
		pFila->fim = &(novaPessoa->elemento);   // O FIM DA FILA APONTA PARA ELE
	}
	else
		pFila->fim->proximo = &(novaPessoa->elemento); // O ElEMENTO ANTERIOR, APONTA PARA O NOVO ELEMENTO

	pFila->fim = &(novaPessoa->elemento); // FIM APONTA PARA O NOVO ELEMENTO
	pFila->totalElementos++;
}

void Remover(FILA *pFila)
{
	if (!FilaVazia(pFila))
	{
		// PESSOA A SER REMOVIDA
		PESSOA_ENCADEADA *pessoaRemover = pFila->inicio;
		pFila->inicio = pessoaRemover->proximo; // INICIO APONTA PARA O PROXIMO DO PRIMEIRO ELEMENTO 

		free(pessoaRemover);
	}
	pFila->totalElementos--;
}

void ImprimirPessoa(PESSOA pessoa)
{
	printf("NOME...: %s \n", pessoa.nome);
	printf("IDADE..: %d \n\n", pessoa.idade);
}

void Listar(FILA *pFila)
{
	PESSOA_ENCADEADA *pessoaAux = NULL;

	for (pessoaAux = pFila->inicio; pessoaAux != NULL; pessoaAux = pessoaAux->proximo)
		ImprimirPessoa(pessoaAux->elemento);
}

int TotalDeElementos(FILA *pFila)
{
	return pFila->totalElementos;
}


// FUNCOES DO DE MENU DO CONSOLE

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

void LeiaPessoa(PESSOA *pessoa)
{
	LimaparTela();
	printf("Entre com o nome...: ");
	scanf(" %s", &pessoa->nome);
	LimparBuffer();

	printf("Entre com a idade..: ");
	scanf(" %d", &pessoa->idade);
	LimparBuffer();
}

void MantemInserir(FILA *pFila) 
{
	PESSOA pessoa;
	LeiaPessoa(&pessoa);
	Inserir(pFila, pessoa);
	Pause();
}

void MantemRetirar(FILA *pFila) {
	Remover(pFila);
	printf("\nRetirado com sucesso.\n");
	Pause();
}

void Menu(int *opcaoSelecionar) {
	LimaparTela();

	printf("***********************************\n");
	printf("***             MENU            ***\n");
	printf("***********************************\n");
	printf("***   [1] - INSERIR             ***\n");
	printf("***   [2] - RETIRAR             ***\n");
	printf("***   [3] - LISTAR              ***\n");
	printf("***   [4] - TOTAL DE ELEMENTO   ***\n");
	printf("***   [5] - SAIR                ***\n");
	printf("***********************************\n");
	printf("\n\n");
	printf("OPCAO: ");
	scanf("%d", opcaoSelecionar);
	LimparBuffer();
}

int main() {
	int opcaoSelecionada = 0;
	FILA *pFila = CriaFila();

	do {
		Menu(&opcaoSelecionada);

		switch (opcaoSelecionada) {
		case 1:
			MantemInserir(pFila);
			break;
		case 2:
			MantemRetirar(pFila);
			break;
		case 3:
			Listar(pFila);
			Pause();
			break;
		case 4:
			LimaparTela();
			printf("\nTotal de Elementos: %d \n", TotalDeElementos(pFila));
			Pause();
			break;
		}
	} while (opcaoSelecionada != 5);


	return 0;
}
