#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *esquerdo;
    struct no *direito;
} No;

No *inserirABB(No *raiz, int chave){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->conteudo = chave;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        return novo;
    } else {
        if (chave < raiz->conteudo)
            raiz->esquerdo = inserirABB(raiz->esquerdo, chave);
        else if (chave > raiz->conteudo)
            raiz->direito = inserirABB(raiz->direito, chave);
        return raiz;
    }
}

No *buscaABB (No *raiz, int chave){
    if(raiz){
      if(raiz->conteudo == chave){
        return raiz;
      } else {
          if (chave > raiz->conteudo)
            raiz->esquerdo = buscaABB(raiz->esquerdo, chave);
          if (chave > raiz->conteudo)
            raiz->direito = buscaABB(raiz->direito, chave);
      }
    printf("Arvore vazia");
    return NULL;
  }
}

No *removeABB(No *raiz, int chave){
    if(raiz == NULL){
        printf("Arvore vazia\n");
        return NULL;
    }
    
    if(chave < raiz->conteudo)
        raiz->esquerdo = removeABB(raiz->esquerdo, chave);
    else if(chave > raiz->conteudo)
        raiz->direito = removeABB(raiz->direito, chave);
    else { // achou o nó a ser removido
        // caso 1: nó folha
        if(raiz->esquerdo == NULL && raiz->direito == NULL){
            free(raiz);
            printf("\nNo folha removido com sucesso!");
            return NULL;
        }
        // caso 2: nó com um filho
        else if(raiz->esquerdo == NULL){
            No *aux = raiz->direito;
            free(raiz);
            printf("\nNo que possuia 1 filho foi removido com sucesso!");
            return aux;
        }
        else if(raiz->direito == NULL){
            No *aux = raiz->esquerdo;
            free(raiz);
            printf("\nNo que possuia 1 filho foi removido com sucesso!");
            return aux;
        }
        // caso 3: nó com dois filhos
        else {
            No *aux = raiz->direito;
            while(aux->esquerdo != NULL)
                aux = aux->esquerdo;
            
            raiz->conteudo = aux->conteudo;
            aux->conteudo = chave;
            raiz->direito = removeABB(raiz->direito, chave);
            printf("\nNo que possuia 2 filhos foi removido com sucesso!");
            return raiz;
        }
    }
    return raiz;
}

void imprimir(No *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->conteudo);
        imprimir(raiz->esquerdo);
        imprimir(raiz->direito);
    }
}

int main() {
    No *raiz = NULL;
    int valor, opcao, valorPai;
    char lado;

    do {
        printf("\nEscolha uma opcao: 1 - Inserir um valor | 2 - Imprimir | 3 - Remover | 7 - Sair: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o dado que quer incluir na arvore: ");
                scanf("%d",&valor);
                raiz = inserirABB(raiz, valor);
                printf("O valor %d foi inserido com sucesso.  ", valor);
                break;
            case 2:
                printf("Percurso pre-ordem: ");
                imprimir(raiz);
                printf("\n");
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                raiz = removeABB(raiz, valor);
                printf("\nO valor %d foi removido com sucesso. ", valor);
                break;
            case 7:
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    return 0;
}
