#include <stdio.h>
#include <stdlib.h>

struct NoArvore 
{
    int dado;
    struct NoArvore *esq;
    struct NoArvore *dir;

};

struct NoArvore *criarNo(int dado)
{

     struct NoArvore *novoNo = (struct NoArvore *)malloc(sizeof(struct NoArvore));
    if (novoNo == NULL)
    {
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    novoNo->dado = dado;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}

//inspirado no professor gustavo
struct NoArvore *inserirNo( struct NoArvore *raiz ,int dado)
{

    if(raiz == NULL)
    {

        raiz = criarNo(dado);

    }
    else
    {
        if(dado <= raiz->dado)
        {
            raiz->esq = inserirNo(raiz->esq, dado);
        }
        else
        {
            raiz->dir = inserirNo(raiz->dir, dado);
        }
        
        return raiz;
    }


};

struct NoArvore *retirarNo( struct NoArvore *raiz ,int dado)
{


    if( raiz == NULL)
    {
        return raiz;
    };
    if( raiz->dado < dado)
    {
        retirarNo( raiz->dir, dado);
    }else if( raiz->dado > dado)
    {
        retirarNo( raiz->esq, dado);
    }else
    {
        if(raiz->esq == NULL)
        { 
            struct NoArvore *temp = raiz->dir;
            free(raiz);
            return temp;
            }
    
        if(raiz->dir == NULL)
        {
            struct NoArvore *temp = raiz->esq;
            free(raiz);
            return temp;
        }
    }

};


// Função para exibir a árvore no formato esquerda-raiz-direita segundo Sedgewick
void mostraArvore(struct NoArvore *a, int b)
{
    if (a == NULL)
    {
        return;
    }
    mostraArvore(a->dir, b + 1);
    imprimeNo(a->dado, b); // Convertendo para caractere para imprimir
    mostraArvore(a->esq, b + 1);
}



int main()
{
    struct NoArvore *raiz = NULL;

    // Inserindo elementos na árvore
    raiz = inserir(raiz, 1);
    raiz = inserir(raiz, 2);
    raiz = inserir(raiz, 4);
    raiz = inserir(raiz, 3);

     mostraArvore(raiz, 3);

};

