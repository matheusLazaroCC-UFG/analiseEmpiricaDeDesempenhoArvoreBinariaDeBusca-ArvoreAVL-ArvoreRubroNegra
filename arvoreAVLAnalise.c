#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int qtdOperacoesInsercao = 0;
int qtdOperacoesBusca = 0;
int qtdOperacoesRemocao = 0;

/**
    Árvore AVL: árvore de busca binária balanceada,
    com relação à altura de suas subárvores.
*/

typedef struct no{
    int valor;
    struct no* esquerda;
    struct no* direita;
    int altura;
} no;

typedef no* ponteiroNo;

void imprimirArvore(ponteiroNo raiz){
    if(raiz != NULL){
        printf("%i", raiz->valor);
        printf("[");
        imprimirArvore(raiz->esquerda);
        imprimirArvore(raiz->direita);
        printf("]");
    }
}

int altura(ponteiroNo no){
    if(no == NULL){
        return 0;
    }
    return no->altura;
}

//Obter no max 2 inteiros
int max(int a, int b){
    if(a > b){
        return a;
    }else{
        return b;
    }
}

ponteiroNo novoNo(int valor){
    ponteiroNo no = (struct no*)malloc(sizeof(struct no));

    no->valor = valor;
    no->esquerda = NULL;
    no->direita = NULL;
    no->altura = 1;
    return no;
}

ponteiroNo rotacionarDireita(ponteiroNo y){
    ponteiroNo x = y->esquerda;
    ponteiroNo t2 = x->direita;

    x->direita = y;
    y->esquerda = t2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

ponteiroNo rotacionarEsquerda(ponteiroNo x){
    ponteiroNo y = x->direita;
    ponteiroNo t2 = y->esquerda;

    y->esquerda = x;
    x->direita = t2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int obterBalanco(ponteiroNo no){
    if(no == NULL){
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

ponteiroNo inserir(ponteiroNo no, int valor){
    if(no == NULL){
        return(novoNo(valor));
    }
    if(valor < no->valor){
        qtdOperacoesInsercao++;
        no->esquerda = inserir(no->esquerda, valor);
    }else
    if(valor > no->valor){
        qtdOperacoesInsercao++;
        no->direita = inserir(no->direita, valor);
    }else{
        return no;
    }

    no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

    int balanco = obterBalanco(no);

    if(balanco > 1 && valor < no->esquerda->valor){
        qtdOperacoesInsercao++;
        return rotacionarDireita(no);
    }

    if(balanco < -1 && valor > no->direita->valor){
        qtdOperacoesInsercao++;
        return rotacionarEsquerda(no);
    }

    if(balanco > 1 && valor > no->esquerda->valor){
        qtdOperacoesInsercao++;
        qtdOperacoesInsercao++;
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if(balanco < -1 && valor < no->direita->valor){
        qtdOperacoesInsercao++;
        qtdOperacoesInsercao++;
       no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }


    return no;
}

ponteiroNo valorMinimoNo(ponteiroNo no){
    ponteiroNo atual = no;

    while(atual->esquerda != NULL){
        atual = atual->esquerda;
    }

    return atual;
}

ponteiroNo deletarNo(ponteiroNo r, int valor){
    if(r == NULL){
        return r;
    }

    if(valor < r->valor){
        qtdOperacoesRemocao++;
        r->esquerda = deletarNo(r->esquerda, valor);
    }else
    if(valor > r->valor){
        qtdOperacoesRemocao++;
        r->direita = deletarNo(r->direita, valor);
    }else{
        if((r->esquerda == NULL) || (r->direita == NULL)){
            ponteiroNo temp;
            if(r->esquerda != NULL){
                temp = r->esquerda;
            }else{
                temp = r->direita;
            }

            if(temp == NULL){
                temp = r;
                r = NULL;
            }else{
                *r = *temp;
            }

            free(temp);
        }else{
            ponteiroNo temp = valorMinimoNo(r->direita);

            r->valor = temp->valor;

            qtdOperacoesRemocao++;
            r->direita = deletarNo(r->direita, temp->valor);
        }
    }

    if(r == NULL){
        return r;
    }


    r->altura = 1 + max(altura(r->esquerda), altura(r->direita));

    int balanco = obterBalanco(r);

    if(balanco > 1 && obterBalanco(r->esquerda) >= 0){
        qtdOperacoesRemocao++;
        return rotacionarDireita(r);
    }

    if(balanco > 1 && obterBalanco(r->esquerda) < 0){
        qtdOperacoesRemocao++;
        qtdOperacoesRemocao++;
        r->esquerda = rotacionarEsquerda(r->esquerda);
        return rotacionarDireita(r);
    }

    if(balanco < -1 && obterBalanco(r->direita) <= 0){
        qtdOperacoesRemocao++;
        return rotacionarEsquerda(r);
    }

    if(balanco < -1 && obterBalanco(r->direita) > 0){
        qtdOperacoesRemocao++;
        qtdOperacoesRemocao++;
        r->direita = rotacionarDireita(r->direita);
        return rotacionarEsquerda(r);
    }

    return r;
}


void preOrdem(ponteiroNo r){
    if(r != NULL){
        printf("%d ", r->valor);
        preOrdem(r->esquerda);
        preOrdem(r->direita);
    }
}

//Busca: exatamente como na arvore binaria
ponteiroNo contem(int valor, ponteiroNo raiz){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->valor == valor){
        return raiz;
    }
    if(raiz->valor > valor){
        qtdOperacoesBusca++;//Descer de nível
        return contem(valor, raiz->esquerda);
    }
    qtdOperacoesBusca++;//Descer de nível
    return contem(valor, raiz->direita);
}


int main(){
    int *v, n, x;
    clock_t tempoInicial, tempoFinal, tempoInsercao, tempoBusca, tempoRemocao;


    printf("Digite a quantidade de elementos: ");
    scanf("%d%*c", &n);

    srand(time(NULL));

    for(int j = 0; j < 30; j++){
        printf("Arvore %d\n", j+1);
        ponteiroNo r = NULL;
        v = (int*) malloc(sizeof(int*) * n);

        /**
       * Insere os n elementos: n = 100, 1000 e 100000
       */
        for(int i = 0; i < n; i++){
            v[i] = rand() % n;
            r = inserir(r, v[i]);
        }
        qtdOperacoesInsercao = 0;

        printf("Busca ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Busca
        */
        x = rand() % n;

        tempoInicial = clock();

        ponteiroNo p = contem(x, r);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de busca do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - busca do elemento %d: %d\n", x, qtdOperacoesBusca);


        printf("Inserção ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Inserção
        */
        x = rand() % n;

        tempoInicial = clock();

        r = inserir(r, x);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de Inserção do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - insercao do elemento %d: %d\n", x, qtdOperacoesInsercao);

        printf("Remoção ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Remoção
        */
        x = rand() % n;

        tempoInicial = clock();

        r = deletarNo(r, x);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de remocao do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - remocao do elemento %d: %d\n", x, qtdOperacoesRemocao);
        printf("\n\n\n");

        qtdOperacoesRemocao = 0;
        qtdOperacoesBusca = 0;
        //r = deletarNo(r, 10);

        //printf("Travessia da pre-ordem depois de deletar o 10: ");
        //preOrdem(r);
        //imprimirArvore(r);
        free(r);

    }


    scanf("%*c");
    return 0;
}