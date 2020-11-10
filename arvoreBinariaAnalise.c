#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
int qtdOperacoesInsercao = 0;
int qtdOperacoesBusca = 0;
int qtdOperacoesRemocao = 0;

typedef int bool;
typedef int tipoChave;

typedef struct auxiliar{
    tipoChave chave;
    struct auxiliar *esquerda, *direita;

} NO;

typedef NO* PONT;

PONT iniciar(){
    return NULL;
}

PONT adicionar(PONT raiz, PONT no){
    if(raiz == NULL){
        return no;
    }
    if(no->chave < raiz->chave){
        qtdOperacoesInsercao++;
        raiz->esquerda = adicionar(raiz->esquerda, no);//Descer de nível
    }else{
        qtdOperacoesInsercao++;
        raiz->direita = adicionar(raiz->direita, no);//Descer de nível
    }
    return raiz;
}

PONT criarNovoNo(tipoChave chave){
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esquerda = NULL;
    novoNo->direita = NULL;
    novoNo->chave = chave;
    return novoNo;
}

PONT contem(tipoChave chave, PONT raiz){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->chave == chave){
        return raiz;
    }
    if(raiz->chave > chave){
        qtdOperacoesBusca++;//Descer de nível
        return contem(chave, raiz->esquerda);
    }
    qtdOperacoesBusca++;//Descer de nível
    return contem(chave, raiz->direita);
}

int numeroDeNos(PONT raiz){
    if(!raiz){
        return 0;
    }
    return(numeroDeNos(raiz->esquerda) + 1 + numeroDeNos(raiz->direita));
}

int altura(PONT r){
    if(r == NULL){
        return 0;
    }

    int alturaEsquerda = altura(r->esquerda);
    int alturaDireita = altura(r->direita);

    if(alturaEsquerda > alturaDireita){
        return (alturaEsquerda + 1);
    }

    return (alturaDireita + 1);
}
/*
bool balanceada(PONT r){
    if (r == NULL) {
        return true;
    }else
    if (r->esquerda == NULL && r->direita == NULL) {
        return true;
    }else
    if (r->esquerda != NULL && r->direita != NULL){
        int diferenca = altura(r->esquerda) - altura(r->direita);
        return (balanceada(r->esquerda) && balanceada(r->direita) && ((diferenca ==0) || (diferenca ==1) || (diferenca == -1)));
    }else
    if (r->esquerda != NULL) {
        return (altura(r->esquerda) == 1);
    }else{
        return (altura(r->esquerda) == 1);
    }
}

boolean perfbalanceada(PONT r){
    if (r == NULL)
        return true;
    else
    if (r->esquerda == NULL && r->direita==NULL)
        return true;
    else
    if (r->esquerda!=NULL && r->direita!=NULL)
    {
        int diferenca = numeroDeNos(r->esquerda) - numeroDeNos(r->direita);
        return (balanceada(r->esquerda) && balanceada(r->direita) && ((diferenca ==0)|| (diferenca ==1) || (diferenca == -1)));
    }
    return(perfbalanceada(r->esquerda) && perfbalanceada(r->direita));
    else{
        if (r->esq != NULL){
            return (numeronos(r->esq) == 1);

        }else
            return (numeronos(r->esq) == 1);
    }

}

boolean insere_dir(tree pai, tipo_elem item){
    if (pai == NULL)
        return FALSE;
    if (pai->dir != NULL) {
        printf("já tem filho à direita");
        return FALSE;
    }
    tree no = malloc(sizeof(no));
    no->esq = NULL;
    no->dir = NULL;
    no->info = item;
    pai->dir = no;
    return TRUE;
}

int nivel(tree t, tipo_elem item){
    int n;
    boolean achou = FALSE;
    n = 0;
    travessia(t, &n, item, &achou);
    return n;
}

percorre a árvore com raiz em ptr em Pré-ordem,
procurando pelo item dado e calculando e retornando seu
nível na variável n
void travessia(tree ptr, int *niv, tipo_elem item, boolean *achou){
    if (ptr != NULL){
        (*niv) ++;
        if (ptr->info == item){
            *achou = TRUE;
            return;
        }
        travessia(ptr->esq, niv, item, achou);
        if (!*achou){
            travessia(ptr->dir, niv, item, achou);
            if (!*achou)
                (*niv) --;
        }
    }
    return;
}

void destruir(tree r){
    if (!vazia(r)){
        destruir(r->esq);
        destruir(r->dir);
        free(r);
    }
    r = NULL;
}

*/





void imprimirArvore(PONT raiz){
    if(raiz != NULL){
        printf("%i", raiz->chave);
        printf("[");
        imprimirArvore(raiz->esquerda);
        imprimirArvore(raiz->direita);
        printf("]");
    }
}

PONT buscarNo(PONT raiz, tipoChave chave, PONT *pai) {
    PONT atual = raiz;
    *pai = NULL;
    while (atual) {
        if (atual->chave == chave) {
            return atual;
        }
        if (chave < atual->chave) {
            atual = atual->esquerda; qtdOperacoesRemocao++;
        } else {
            atual = atual->direita; qtdOperacoesRemocao++;
        }
    }
    return NULL;
}

PONT removerNo(PONT raiz, tipoChave chave){
    PONT pai, no, q, p;
    no = buscarNo(raiz, chave, &pai);
    if(no == NULL){
        return raiz;
    }
    if(!no->esquerda || !no->direita){
        if(!no->esquerda){
            qtdOperacoesRemocao++;
            q = no->direita;
        }else{
            qtdOperacoesRemocao++;
            q = no->esquerda;
        }
    }else{
        p = no;
        q = no->esquerda; qtdOperacoesRemocao++;
        while(q->direita){
            p = q;
            q = q->direita; qtdOperacoesRemocao++;
        }
        if(p != no){
            p->direita = q->esquerda;
            q->esquerda = no->esquerda; qtdOperacoesRemocao++;
        }
        q->direita = no->direita; qtdOperacoesRemocao++;
    }
    if(!pai){
        free(no);
        return q;
    }
    if(chave < pai->chave){
        pai->esquerda = q; qtdOperacoesRemocao++;
    }else{
        pai->direita = q; qtdOperacoesRemocao++;
    }
    free(no);
    return raiz;
}

void bubbleSort(int v[], int n){
    int i, j, temp;

    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(v[j] < v[j+1]){
                temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
            }
        }
    }
}

void imprimirPosOrdem(PONT no){
    if(no == NULL){
        return;
    }
    imprimirPosOrdem(no->esquerda);
    imprimirPosOrdem(no->direita);
    printf(" %d", no->chave);
}

void imprimirPreOrdem(PONT no){
    if(no == NULL){
        return;
    }
    printf(" %d", no->chave);
    imprimirPreOrdem(no->esquerda);
    imprimirPreOrdem(no->direita);
}

void imprimirEmOrdem(PONT no){
    if(no == NULL){
        return;
    }
    imprimirEmOrdem(no->esquerda);
    printf(" %d", no->chave);
    imprimirEmOrdem(no->direita);
}

int main(){
    int i, x;
    //clock_t tempo, tempoInicial, tempoFinal, tempoInsercao, tempoBusca, tempoRemocao;
    clock_t tempoInicial, tempoFinal, tempoInsercao, tempoBusca, tempoRemocao;


    int *v, n;
    printf("Digite a quantidade de elementos: ");
    scanf("%d%*c", &n);

    srand(time(NULL));

    for(int j = 0; j < 30; j++){
        PONT r = iniciar();
        v = (int*) malloc(sizeof(int*) * n);
        for(i = 0; i < n; i++){
            v[i] = rand() % n;
        }

        /**
        * Insere os n elementos: n = 100, 1000 e 100000
        */
        for(i = 0; i < n; i++){
            PONT no = criarNovoNo(v[i]);
            r = adicionar(r, no);
        }
        qtdOperacoesInsercao = 0;

        printf("Busca ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Busca
        */
        x = rand() % n;

        //clock_t tempoInicial = clock();
        tempoInicial = clock();

        PONT p = contem(x, r);
        /*if(p){
        printf("valor: %d\n", p->chave);
        }else{
        printf("nao encontrado!\n");
        }*/

        tempoFinal = clock() - tempoInicial;

        printf("tempo de busca do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("Quantidade de operações Busca %d\n", qtdOperacoesBusca);
        qtdOperacoesBusca = 0;

        printf("Insercao------------------------------------------------------------------\n");
        /**
        * Marcação de tempo para a operação de Inserção
        */
        x = rand() % n;

        //clock_t tempoInicial = clock();
        tempoInicial = clock();

        PONT no = criarNovoNo(x);
        r = adicionar(r, no);;
        //printf("valor: %d\n", r->chave);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de insercao do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("Quantidade de operações insercao %d\n",qtdOperacoesInsercao);
        //qtdOperacoesInsercao = 0;



        printf("Remocao------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Remocao
        */
        x = rand() % n;

        //clock_t tempoInicial = clock();
        tempoInicial = clock();

        r = removerNo(r, x);
        /*if(r){
        printf("valor: %d\n", r->chave);
        }else{
        printf("falha");
        }*/

        tempoFinal = clock() - tempoInicial;

        printf("tempo de Remocao do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("Quantidade de operações Remocao %d\n",qtdOperacoesRemocao);
        qtdOperacoesRemocao = 0;

        printf("Teste %d\n\n\n", j+1);
        free(v);
        free(r);
    }





    printf("\n");



    scanf("%*c");
    return 0;
}



