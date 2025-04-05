#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *esquerdo;
    struct no *direito;
} No;

No* criaNo(int chave) {
    No *novo = malloc(sizeof(No));
    novo->conteudo = chave;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

No* inserir(No *raiz, int chave, char lado) {
    if (raiz == NULL) {
        return criaNo(chave);
    } else {
        if (lado == 'e') {
            if (raiz->esquerdo != NULL) {
                printf("Lado esquerdo ja possui um no!\n");
                return NULL;
            }
            raiz->esquerdo = criaNo(chave);
            return raiz->esquerdo;
        } else if (lado == 'd') {
            if (raiz->direito != NULL) {
                printf("Lado direito ja possui um no!\n");
                return NULL;
            }
            raiz->direito = criaNo(chave);
            return raiz->direito;
        } else {
            printf("Lado invalido! Use 'e' ou 'd'.\n");
            return NULL;
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
    int valor, opcao;
    char lado;

    do {
        printf("\nEscolha uma opcao: 1 - Inserir um valor | 2 - Imprimir | 7 - Sair: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);

                if (raiz == NULL) {
                    raiz = inserir(raiz, valor, 'e'); 
                    printf("Raiz inserida com valor %d\n", valor);
                } else {
                    printf("Inserir a esquerda ou direita do no raiz? (e/d): ");
                    scanf(" %c", &lado);

                    inserir(raiz, valor, lado);
                    printf("Valor %d inserido no lado %c\n", valor, lado);
                }
                break;

            case 2:
                printf("Percurso pre-ordem: ");
                imprimir(raiz);
                printf("\n");
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
