#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura do nó da árvore AVL
struct NoAVL {
    int dado;
    struct NoAVL *esquerda;
    struct NoAVL *direita;
    int altura;
};

// Função para criar um novo nó na árvore
struct NoAVL *criarNo(int dado) {
    struct NoAVL *novoNo = (struct NoAVL *)malloc(sizeof(struct NoAVL));
    if (novoNo == NULL) {
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    novoNo->dado = dado;
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->altura = 0;
    return novoNo;
}

// Função para calcular a altura de um nó
int altura(struct NoAVL *no) {
    if (no == NULL)
        return -1;
    return no->altura;
}

// Função para calcular o fator de balanceamento de um nó
int fatorBalanceamento(struct NoAVL *no) {
    if (no == NULL)
        return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// Função para realizar rotação à direita
struct NoAVL *rotacaoDireita(struct NoAVL *no) {
    struct NoAVL *novaRaiz = no->esquerda;
    struct NoAVL *subArvore = novaRaiz->direita;

    novaRaiz->direita = no;
    no->esquerda = subArvore;

    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));

    return novaRaiz;
}

// Função para realizar rotação à esquerda
struct NoAVL *rotacaoEsquerda(struct NoAVL *no) {
    struct NoAVL *novaRaiz = no->direita;
    struct NoAVL *subArvore = novaRaiz->esquerda;

    novaRaiz->esquerda = no;
    no->direita = subArvore;

    no->altura = 1 + (altura(no->esquerda) > altura(no->direita) ? altura(no->esquerda) : altura(no->direita));
    novaRaiz->altura = 1 + (altura(novaRaiz->esquerda) > altura(novaRaiz->direita) ? altura(novaRaiz->esquerda) : altura(novaRaiz->direita));

    return novaRaiz;
}

// Função para balancear a árvore
struct NoAVL *balanceamento(struct NoAVL *raiz, int dado) {
    if (raiz == NULL) return raiz;

    raiz->altura = 1 + (altura(raiz->esquerda) > altura(raiz->direita) ? altura(raiz->esquerda) : altura(raiz->direita));
    int balanceamento = fatorBalanceamento(raiz);

    if (balanceamento > 1 && dado < raiz->esquerda->dado) 
        return rotacaoDireita(raiz);

    if (balanceamento < -1 && dado > raiz->direita->dado) 
        return rotacaoEsquerda(raiz);

    if (balanceamento > 1 && dado > raiz->esquerda->dado) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balanceamento < -1 && dado < raiz->direita->dado) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

// Função para inserir um novo nó na árvore AVL
struct NoAVL *inserir(struct NoAVL *raiz, int dado) {
    if (raiz == NULL)
        return criarNo(dado);

    if (dado < raiz->dado)
        raiz->esquerda = inserir(raiz->esquerda, dado);
    else if (dado > raiz->dado)
        raiz->direita = inserir(raiz->direita, dado);
    else
        return raiz;

    return balanceamento(raiz, dado);
}

// Função para percorrer a árvore em ordem
void percorrerEmOrdem(struct NoAVL *raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("%d ", raiz->dado);
        percorrerEmOrdem(raiz->direita);
    }
}

// Função principal para testar o funcionamento da árvore AVL
int main() {
    struct NoAVL *raiz = NULL;

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 20);
    raiz = inserir(raiz, 30);
    raiz = inserir(raiz, 40);
    raiz = inserir(raiz, 50);
    raiz = inserir(raiz, 25);

    printf("Percurso em ordem da árvore AVL: ");
    percorrerEmOrdem(raiz);

    return 0;
}
