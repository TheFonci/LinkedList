/*
Listas encadeadas são estruturas de dados que permitem armazenar uma coleção
 de elementos de um mesmo tipo.

Neste arquivo, temos a implementação de uma lista encadeada simples de inteiros.
*/

#include "lista.h"

struct lista
{
	int info;
	struct lista *prox;
};
//Função para criar uma lista vazia.
Lista *lst_cria(void)
{
	return NULL; //Retorna um ponteiro nulo, indicando que a lista está vazia.
}
//Função para inserir um elemento no início da lista.
Lista *lst_insere(Lista *l, int v)
{
	Lista *novo = (Lista *)malloc(sizeof(Lista)); //Reserva espaço na memorida para a struct Lista.
	if (novo == NULL)
	{
		printf("[ERRO] memoria insuficiente!"); //Informa um erro, e que não há memória sufuceunte no visor.
		exit(1); //Encerra o programa com a mensagem a cima.
	}
	novo->info = v; // Define o valor do novo elemento como 'v'.
	novo->prox = l; // Define o próximo elemento como o antigo primeiro elemento da lista
	return novo; // Retorna o ponteiro para o novo elemento, que agora é o primeiro da lista.

	/* Ou para alterar diretamente

	void lst_insere(Lista** t, int v){
	Lista* novo = (Lista*) malloc(sizeof(Lista));
	novo->info = v;
	novo->prox = *t;
	*t = novo; */
}
// Indica se a lista está vazia.
int lst_vazia(Lista *l)
{
	return (l == NULL);
}
// Imprime no visor o conteudo da lista.
void lst_imprime(Lista *l)
{
	Lista *p;
	for (p = l; p != NULL; p = p->prox) //Percorre os daods da lista com um laço de repetição.
	{
		printf("\tInfo = %d \n", p->info); //Imprime no visor os dados que foram percorridos no laço a cima.
	}
}

Lista *lst_busca(int elemento, Lista *l)
{
	Lista *p;
	for (p = l; p != NULL; p = p->prox)
	{
		if (p->info == elemento)
			return p;
	}

	return NULL;
}

Lista *lst_retira(Lista *l, int v)
{
	Lista *ant = NULL; /* ponteiro para elemento anterior */
	Lista *p = l;	   /* ponteiro para percorrer a lista*/
	/* procura elemento na lista, guardando anterior */
	while (p->info != v)
	{
		if (p == NULL)
			return l; /* n�o achou: retorna lista original */
		ant = p;
		p = p->prox;
		/* verifica se achou elemento */
	}
	/* retira elemento */
	if (ant == NULL)
		/* retira elemento do inicio */
		l = p->prox;
	else
		/* retira elemento do meio da lista */
		ant->prox = p->prox;
	free(p);
	return l;
}

void lst_libera(Lista *l)
{
	Lista *p = l;
	Lista *t;
	while (p != NULL)
	{
		t = p->prox;
		free(p);
		p = t;
	}
}

Lista *lst_insere_ordenada(Lista *l, int v)
{
	Lista *novo; //Novo nó a ser inserido.
	Lista *ant = NULL; //Ponteiro para o elemento anterior.
	Lista *p = l; //Ponteiro para percorrer a lista.
	while (p != NULL && p->info < v) //Enquanto P não for o ultimo nó && A informação do nó atual for menor que a informação a ser inserida.
	{
		ant = p; //Nó anterior recebe nó atual.
		p = p->prox;
	}
	novo = (Lista *)malloc(sizeof(Lista));
	novo->info = v;
	if (ant == NULL)
	{
		novo->prox = l;
		l = novo;
	}
	else
	{
		novo->prox = ant->prox;
		ant->prox = novo;
	}
	return l;
}

Lista *lst_ler_arquivo(char *nome_arquivo)
{
	FILE *arquivo;
	int valor;
	Lista *l = lst_cria();
	arquivo = fopen(nome_arquivo, "r");
	if (arquivo == NULL)
	{
		printf("Erro ao abrir o arquivo!\n");
		exit(1);
	}
	while (fscanf(arquivo, "%d", &valor) != EOF)
	{
		l = lst_insere(l, valor);
	}
	fclose(arquivo);
	return l;
}
