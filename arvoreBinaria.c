#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int conteudo;
    struct no *esquerdo;
    struct no *direito;
} No;

typedef struct no {
    int conteudo;
    struct no *esquerdo;
    struct no *direito;
} No;

No* criaNo(int chave) {
    No *novo = (No*)malloc(sizeof(No));
    novo->conteudo = chave;
    novo->esquerdo = NULL;
    novo->direito = NULL;
    return novo;
}

char getPosNo(No *pai, No *atual) {
    if (pai->esquerdo == atual)
        return 'e';
    else
        return 'd';
}

No* inserir(No *raiz, int chave, char lado) {
    if (raiz == NULL) {
        return criaNo(chave);
        printf("Raiz criada!\n");
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

No *remover(No *raiz, int chave) {
    if (raiz != NULL) {
        No *aux = NULL;
        if (chave == raiz->conteudo) {
            if (raiz->esquerdo != NULL && raiz->direito != NULL) {
                printf("O no possui 2 filhos, impossivel remover.\n");
                return raiz;
            } else {
                if (raiz->esquerdo != NULL || raiz->direito != NULL) {
                    aux = raiz;
                    aux->esquerdo = NULL;
                    aux->direito = NULL;
                    free(raiz);
                    printf("\nNo que possuia 1 filho foi removido.");
                } else {
                    free(raiz);
                    printf("\nNo folha removido.");
                }
            }
        }
        if (raiz->esquerdo != NULL && raiz->esquerdo->conteudo == chave) {
            raiz->esquerdo = remover(raiz->esquerdo, chave);
            return raiz;
        } else if (raiz->direito != NULL && raiz->direito->conteudo == chave) {
            raiz->direito = remover(raiz->direito, chave);
            return raiz;
        }
        remover(raiz->esquerdo, chave);
        remover(raiz->direito, chave);
    }
    return raiz;
}

No *busca (No *raiz, int chave){
    if(raiz != NULL){
        if(raiz->conteudo == chave){
            return raiz;
        } else {
            No *es = busca(raiz->esquerdo, chave);
            if(es) return es;
            No *di = busca(raiz->direito, chave);
            if(di) return di;
        }
        return NULL;
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
                if(raiz == NULL){
                    if(raiz = inserir(NULL, valor,'r'))
                    printf("\nRaiz inserida com sucesso.");
                    else
                        printf("\nRaiz nao inserida");
                }
                else{
                    printf("\nDigite o pai do no: ");
                    scanf("%d",&valorPai);
                    No *procuraPai = busca(raiz,valorPai);
                    if(procuraPai == NULL)
                        printf("\nPai nao encontrado. Insercao nao feita");
                    else{
                        do{
                        printf("\nDigite se o filho vai ser da esquerda <e> ou da direita <d>:");
                        fflush(stdin);
                        scanf("%c",&lado);
                        }while(lado != 'e' && lado != 'd');
                        if(inserir(procuraPai, valor, lado))
                            printf("\nNo inserido com sucesso.\n");
                        else
                            printf("\nNo nao inserido.\n");
                        }
                }
                break;
            case 2:
                printf("Percurso pre-ordem: ");
                imprimir(raiz);
                printf("\n");
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                remover(raiz, valor);
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
