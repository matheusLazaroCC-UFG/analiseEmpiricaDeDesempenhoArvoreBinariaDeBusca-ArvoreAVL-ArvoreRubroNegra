#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define sucesso 0
#define falha 1
#define elementoDuplicado 2

int qtdOperacoesInsercao = 0;
int qtdOperacoesBusca = 0;
int qtdOperacoesRemocao = 0;

//(1)
typedef enum {
    vermelho,
    preto,
    invalido
}cor;

//(2)
typedef struct no {
    int valor;
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    cor cor;

} structNo;


/**
** Cria e retorna o nó
**/
int criarStructNo(structNo** noCriado, int valor);

/**
** Pesquisar a chave na arvore
** Se um no com mesmo valor for encontrado, o retorna.
** Senão, retorna o último no visitado
**/
structNo* buscarNoValor(structNo* no, int chave);
structNo* buscarNoValor2(structNo* no, int chave);

/**
** Insere o novo no na posição apropriada
** Retorna sucesso ou falha
 * O algoritmo de inserção tem 2 principais casos, que dependem
    da cor do nó tio.
**/
int inserirNo(structNo* no, structNo* novoNo);

/**
    - Caso 1: Se o nó tio for NULL ou a cor do nó tio for preto,
    recolorimos e rotacionamos.
 */
void inserirCaso1 (structNo* avo, structNo* noPai, structNo* chaveNo);

/**
 * - Caso 2: Caso contrário, recolorimos e repetimos o ciclo até obtermos
    o equilíbrio.
 */
void inserirCaso2 (structNo* avo, structNo* tio, structNo* noPai, structNo* chaveNo);


/**
** Retorna a altura do no fornecido
**/
int alturaNo(structNo* no);


/**
** Retorna a altura preta da arvore
**/
int alturaPreto(structNo* no);

/**
** Retorna o no anterior, se existente
**/
structNo* noAnterior(structNo* no);

/**
** Retorna o no sucessor, se existente
**/
structNo* noSucessor(structNo* no);

/**
** Rotações da arvore: utiliza o mecanismo de rotação local
 * da árvore rubro negra
**/
void rotacionarDireita (structNo* raiz, structNo* pivo);

void rotacionarEsquerda (structNo* raiz, structNo* pivo);

/**
** Casos de Rotação
**/
void casoEsquerdaEsquerda(structNo* raiz, structNo* pivo);

void casoDireitaDireita(structNo* raiz, structNo* pivo);

void casoEsquerdaDireita(structNo* raiz, structNo* pivo);

void casoDireitaEsquerda(structNo* raiz, structNo* pivo);




/**
** Retorna o valor maximo, dado dois valores
**/
int max(int valor1, int valor2);

/**
 * Atualiza a quantidade de nós da subárvore do nó passado por referência,
 * com o valor a ser atualizado.
 */
void atualizarContagemNo(structNo* no, int valorAtualizar);

/**
 * Atualiza a quantidade de nós varmelhos da subárvore do nó passado
 * por referência, com o valor a ser atualizado.
 */
void atualizarContagemNoVermelho(structNo* no, int valorAtualizar);

/**
** Imprimir a arvore transversal
** 1. Inorder
** 2. Preorder
** 3. Postorder
**/
void imprimirEmOrdem(structNo* no);
void imprimirPreOrdem(structNo* no);
void imprimirPosOrdem(structNo* no);

void imprimirArvore(structNo* no);


/**
** Recebe como entrada o no a ser excluido
** Dividido em subcasos
**/
int removerNo(structNo* no);

void removerCasos(structNo* noPai, structNo* irmao);

void removerCaso1_1(structNo* noPai, structNo* irmao);

void removerCaso1_2(structNo* noPai, structNo* irmao);

void removerCaso2_1_1(structNo* noPai, structNo* irmao);

void removerCaso2_1_2(structNo* noPai, structNo* irmao);

void removerCaso2_2_1(structNo* noPai, structNo* irmao);

void removerCaso2_2_2(structNo* noPai, structNo* irmao);

structNo *inserir(struct no* pai, struct no* no, int valor);


structNo* noRaiz;


int main() {
    int opType, valor, n, x;
    structNo* resultado;
    int status;
    clock_t tempoInicial, tempoFinal;
    
    printf("Digite a quantidade de nós da árvore: ");
    scanf("%d%*c", &n);

    srand(time(NULL));

    double media = 0;
    double media2 = 0;

    for(int i = 0; i < 30; i++){
        printf("Arvore %d\n", i+1);
        noRaiz = NULL;
        
        for(int j = 0; j < n; j++){
            x = rand() % n;
            status = criarStructNo (&resultado, x);
            status = inserirNo(noRaiz, resultado);
        }
        qtdOperacoesInsercao = 0;

        printf("Busca ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Busca
        */
        x = rand() % n;

        tempoInicial = clock();

        resultado = buscarNoValor2(noRaiz, x);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de busca do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - busca do elemento %d: %d\n", x, qtdOperacoesBusca);


        printf("Inserção ------------------------------------------------------------------\n");

        /**
        * Marcação de tempo para a operação de Inserção
        */
        x = rand() % n;

        tempoInicial = clock();


        status = criarStructNo (&resultado, x);
        status = inserirNo(noRaiz, resultado);

        tempoFinal = clock() - tempoInicial;

        printf("tempo de Inserção do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - insercao do elemento %d: %d\n", x, qtdOperacoesInsercao);
        media2 += ((double)tempoFinal)/((CLOCKS_PER_SEC/1000));

        /**
        * Marcação de tempo para a operação de Remoção
        */
        x = rand() % n;

        tempoInicial = clock();

        resultado = buscarNoValor(noRaiz, x);
        if(resultado != NULL || resultado->valor != x){
            status = removerNo(resultado);
        }


        tempoFinal = clock() - tempoInicial;

        printf("tempo de remocao do elemento %d: %.20lf Milissegundos\n", x, ((double)tempoFinal)/((CLOCKS_PER_SEC/1000)));
        printf("quantidade de operacoes - remocao do elemento %d: %d\n", x, qtdOperacoesRemocao);
        printf("\n\n\n");
        media += ((double)tempoFinal)/((CLOCKS_PER_SEC/1000));

        qtdOperacoesRemocao = 0;
        qtdOperacoesBusca = 0;


        resultado = NULL;
    }

    printf("media remoção: %lf\n", media/30);
    printf("media insercao: %lf\n", media2/30);


    return sucesso;
}








int criarStructNo(structNo** noCriado, int valor) {
    structNo* temp = (structNo*)calloc(sizeof(structNo), 1);

    if (temp == NULL) {
        printf("Erro ao criar no\n");
        return falha;
    }

    temp->valor = valor;
    temp->pai = NULL;
    temp->esquerda = NULL;
    temp->direita = NULL;

    temp->cor = invalido;

    (*noCriado) = temp;

    return sucesso;
}

structNo* buscarNoValor(structNo* no, int chave) {
    if (no == NULL){
        return NULL;
    }
    if (no->valor == chave){
        return no;
    }else
    if(no->valor < chave && no->direita != NULL){

        return buscarNoValor(no->direita, chave);
    }else
    if (no->valor > chave && no->esquerda != NULL){

        return buscarNoValor(no->esquerda, chave);
    }else{
        return no;
    }

    return NULL;
}

structNo* buscarNoValor2(structNo* no, int chave) {
    if (no == NULL){
        return NULL;
    }
    if (no->valor == chave){
        return no;
    }else
    if(no->valor < chave && no->direita != NULL){
        qtdOperacoesBusca++;
        return buscarNoValor2(no->direita, chave);
    }else
    if (no->valor > chave && no->esquerda != NULL){
        qtdOperacoesBusca++;

        return buscarNoValor2(no->esquerda, chave);
    }else{
        return no;
    }

    return NULL;
}



int max(int valor1, int valor2) {
    if(valor1 > valor2){
        return valor1;
    }else{
        return valor2;
    }
}

int alturaNo(structNo* no) {
    if (no == NULL){
        return 0;
    }

    if (no->esquerda == NULL && no->direita == NULL){
        return 0;
    }

    return (1 + max(alturaNo(no->esquerda), alturaNo(no->direita)));
}

int alturaPreto(structNo* no) {
    int altura = 0;

    if (no == NULL){
        return altura;
    }

    if (no->cor == preto) {
        altura = 1;
    }else{
        altura = 0;
    }

    if (no->esquerda != NULL){
        return altura + alturaPreto(no->esquerda);
    }else
    if (no->direita != NULL){
        return altura + alturaPreto(no->direita);
    }else{
        return altura;
    }
}

structNo* noAnterior(structNo* no) {
    if(no->esquerda != NULL) {
        no = no->esquerda;

        while ( no->direita != NULL) {
            no = no->direita;
        }

        return no;
    }else
    if ( no->pai != NULL) {
        if (no->pai->direita == no){
            no = no->pai;
        }else{
            while (no->pai->esquerda == no) {
                no = no->pai;
            }

            no = no->pai;
        }

        return no;
    }

    return NULL;
}

structNo* noSucessor(structNo* no) {
    if (no->direita != NULL) {
        no = no->direita;

        while (no->esquerda != NULL) {
            no = no->esquerda;
        }

        return no;
    }else
    if ( no->pai != NULL) {
        if (no->pai->esquerda == no) {
            no = no->pai;
        }else {
            while (no->pai->direita == no) {
                no = no->pai;
            }

            no = no->pai;
        }

        return no;
    }

    return NULL;
}

void atualizarContagemNo(structNo* no, int valorAtualizar) {

    if (no->pai != NULL){
        atualizarContagemNo(no->pai, valorAtualizar);
    }
}

void atualizarContagemNoVermelho(structNo* no, int valorAtualizar) {

    if (no->pai != NULL){
        atualizarContagemNoVermelho(no->pai, valorAtualizar);
    }
}


void rotacionarDireita (structNo* raiz, structNo* pivo) {
    structNo* subB = pivo->direita;

    pivo->pai = raiz->pai;
    if(pivo->pai != NULL) {
        if (raiz->pai->esquerda == raiz){
            raiz->pai->esquerda = pivo;
        }else{
            raiz->pai->direita = pivo;
        }
    }

    raiz->pai = pivo;
    pivo->direita = raiz;

    raiz->esquerda = subB;
    if(raiz->esquerda != NULL){
        raiz->esquerda->pai = raiz;
    }
}

void rotacionarEsquerda(structNo* raiz, structNo* pivo) {
    structNo* raizpai = raiz->pai;
    structNo* subB = pivo->esquerda;

    pivo->pai = raizpai;
    if (pivo->pai != NULL) {
        if (raizpai->esquerda == raiz){
            raizpai->esquerda = pivo;
        }else{
            raizpai->direita = pivo;
        }
    }

    raiz->pai = pivo;
    pivo->esquerda = raiz;

    raiz->direita = subB;
    if (raiz->direita != NULL){
        raiz->direita->pai = raiz;
    }
}

void casoEsquerdaEsquerda(structNo* raiz, structNo* pivo) {
    rotacionarDireita (raiz, pivo);
}

void casoDireitaDireita(structNo* raiz, structNo* pivo) {
    rotacionarEsquerda(raiz, pivo);
}

void casoEsquerdaDireita(structNo* raiz, structNo* pivo) {
    rotacionarEsquerda(pivo, pivo->direita);
    rotacionarDireita(raiz, raiz->esquerda);
}

void casoDireitaEsquerda(structNo* raiz, structNo* pivo) {
    rotacionarDireita(pivo, pivo->esquerda);
    rotacionarEsquerda(raiz, raiz->direita);
}

int inserirNo(structNo* no, structNo* novoNo) {
    structNo* avo;
    structNo* tio;
    structNo* noPai = NULL;

    if (no != NULL){
        noPai = buscarNoValor(no, novoNo->valor);
    }
    if (noPai == NULL) {
        qtdOperacoesInsercao++;
        noRaiz = novoNo;
        novoNo->cor = preto;
        return sucesso;
    }

    if (noPai->valor < novoNo->valor){
        qtdOperacoesInsercao++;
        noPai->direita = novoNo;
    } else{
        qtdOperacoesInsercao++;
        noPai->esquerda = novoNo;
    }

    qtdOperacoesInsercao++;
    novoNo->pai = noPai;
    novoNo->cor = vermelho;

    if (noPai->cor == vermelho) {
        avo = noPai->pai;

        if (avo != NULL && avo->esquerda == noPai){
            qtdOperacoesInsercao++;
            tio = avo->direita;
        }else{
            qtdOperacoesInsercao++;
            tio = avo != NULL ? avo->esquerda : NULL;
        }

        if (tio == NULL || tio->cor == preto) {
            //Caso 1
            inserirCaso1 (avo, noPai, novoNo);
        }else {
            //Caso 2
            inserirCaso2 (avo, tio, noPai, novoNo);
        }
    }

    return sucesso;
}

void inserirCaso1 (structNo* avo, structNo* noPai, structNo* chaveNo) {
    if (avo->direita == noPai) {
        if (noPai->direita == chaveNo) {
            avo->cor = vermelho;
            noPai->cor = preto;

            if (avo == noRaiz){
                noRaiz = noPai;
            }

            qtdOperacoesInsercao++;
            casoDireitaDireita (avo, noPai);
        }else {
            avo->cor = vermelho;
            chaveNo->cor = preto;

            if (avo == noRaiz){
                noRaiz = chaveNo;
            }

            qtdOperacoesInsercao++;
            casoDireitaEsquerda(avo, noPai);
        }
    }else {
        if (noPai->esquerda == chaveNo) {
            avo->cor = vermelho;
            noPai->cor = preto;

            if (avo == noRaiz){
                noRaiz = noPai;
            }

            qtdOperacoesInsercao++;
            casoEsquerdaEsquerda(avo, noPai);
        }else {
            avo->cor = vermelho;
            chaveNo->cor = preto;

           if (avo == noRaiz){
                noRaiz = chaveNo;
            }

            qtdOperacoesInsercao++;
            casoEsquerdaDireita(avo, noPai);
        }
    }
}

void inserirCaso2 (structNo* avo, structNo* tio, structNo* noPai, structNo* chaveNo) {
    avo->cor = vermelho;
    tio->cor = preto;
    noPai->cor = preto;

    if (avo->pai == NULL) {
        noRaiz = avo;
        avo->cor = preto;
        return;
    }

    if (avo->pai->cor == preto) {
        return;
    }

    chaveNo = avo;
    noPai = avo->pai;
    avo = noPai->pai;

    if (avo->esquerda == noPai){
        tio = avo->direita;
    }else{
        tio = avo->esquerda;
    }

    if (tio == NULL || tio->cor == preto) {
        //Caso 1
        qtdOperacoesInsercao++;
        inserirCaso1 (avo, noPai, chaveNo);
    }else {
        //Caso 2
        qtdOperacoesInsercao++;
        inserirCaso2 (avo, tio, noPai, chaveNo);
    }
}

int removerNo(structNo* no) {
    structNo* sucessor;
    structNo* proximoNo;
    structNo* irmao;
    structNo* noPai;
    int temp;

    if(no == NULL) {
        return falha;
    }

    if (no->esquerda != NULL && no->direita != NULL) {
        sucessor = noSucessor(no);
        temp = sucessor->valor;
        no->valor = temp;
        qtdOperacoesRemocao++;
        removerNo(sucessor);
    }else
    if (no->esquerda != NULL || no->direita != NULL) {
        if (no->esquerda != NULL){
            proximoNo = no->esquerda;
        }else{
            proximoNo = no->direita;
        }

        if (no->pai != NULL) {
            if (no->pai->esquerda == no) {
                qtdOperacoesRemocao++;
                no->pai->esquerda = proximoNo;
            }else {
                qtdOperacoesRemocao++;
                no->pai->direita = proximoNo;
            }

            proximoNo->pai = no->pai;
        }else {
            qtdOperacoesRemocao++;
            noRaiz = proximoNo;
            proximoNo->pai = NULL;
        }

        if (no->cor == preto){
            proximoNo->cor = preto;
        }
        qtdOperacoesRemocao++;

        no->pai = NULL;
        free(no);
    }else {
        if (no->cor == vermelho) {
            if (no->pai->esquerda == no){
                no->pai->esquerda = NULL;
            }else{
                no->pai->direita = NULL;
            }

            no->pai = NULL;
            free(no);
        }else {
            if (noRaiz == no) {
                noRaiz = NULL;
                free(no);
                return sucesso;
            }

            noPai = no->pai;
            if (noPai->esquerda == no) {
                noPai->esquerda = NULL;
                qtdOperacoesRemocao++;
                irmao = noPai->direita;
            }else {
                noPai->direita = NULL;
                qtdOperacoesRemocao++;
                irmao = noPai->esquerda;
            }

            no->pai = NULL;
            free(no);

            qtdOperacoesRemocao++;
            removerCasos(noPai, irmao);
        }
    }

    return sucesso;
}

void removerCasos(structNo* noPai, structNo* irmao) {
    //Nó pai vermelho
    if (noPai->cor == vermelho) {
        //Caso 1
        if (
            (irmao == NULL) ||
            (
                (irmao->esquerda == NULL ||irmao->esquerda->cor == preto) &&
                (irmao->direita == NULL || irmao->direita->cor == preto)
            )
        ) {
            //No pai vermelho caso 1_2
            removerCaso1_2(noPai, irmao);
        }else {
            //No pai vermelho caso1_1
            removerCaso1_1(noPai, irmao);
        }
    }else
    //No irmao vermelho
    if (irmao != NULL && irmao->cor == vermelho) {
        //Caso 2_1
        if (
                (irmao->esquerda == NULL || irmao->esquerda->cor == preto) &&
                (irmao->direita == NULL || irmao->direita->cor == preto)
        ) {
            //Caso 2_1_2
            removerCaso2_1_2 (noPai, irmao);
        }else {
            //Caso 2_1_1
            removerCaso2_1_1(noPai, irmao);
        }
    }else {
        //No irmao preto ou nulo
        //Caso 2_2
        if (irmao == NULL) {
            return;
        }

        //Irmaos nulos, irmao direito preto, irmao esquerdo preto ou irmaos pretos
        if (
            (irmao->esquerda == NULL || irmao->esquerda->cor == preto) &&
            (irmao->direita == NULL || irmao->direita->cor == preto)
        ) {
            //Caso 2_2_2
            removerCaso2_2_2(noPai, irmao);
        }else {
            //
            //Caso 2_2_1
            removerCaso2_2_1(noPai, irmao);
        }
    }
}

void removerCaso1_1(structNo* noPai, structNo* irmao) {
    structNo* neto;

    if (noPai->esquerda == irmao) {
        if (irmao->esquerda != NULL && irmao->esquerda->cor == vermelho) {
            irmao->cor = vermelho;
            irmao->esquerda->cor = preto;
            noPai->cor = preto;

            if(noPai == noRaiz){
                noRaiz = irmao;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaEsquerda(noPai, irmao);
        }else {
            neto = irmao->direita;
            noPai->cor = preto;

            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaDireita(noPai, irmao);
        }
    }else {
        if (irmao->direita != NULL && irmao->direita->cor == vermelho) {
            noPai->cor = preto;
            irmao->direita->cor = preto;
            irmao->cor = vermelho;

            if(noPai == noRaiz){
                noRaiz = irmao;
            }

            qtdOperacoesRemocao++;
            casoDireitaDireita(noPai, irmao);
        }else {
            neto = irmao->esquerda;
            noPai->cor = preto;

            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoDireitaEsquerda(noPai, irmao);
        }
    }
}

void removerCaso1_2(structNo* noPai, structNo* irmao) {
    if(irmao != NULL){
        irmao->cor = vermelho;
    }

    noPai->cor = preto;
}

void removerCaso2_1_1(structNo* noPai, structNo* irmao) {
    structNo* neto;
    structNo* bisneto;

    if (irmao == noPai->esquerda) {
        neto = irmao->direita;
        if (neto->esquerda != NULL && neto->esquerda->cor == vermelho) {
            bisneto = neto->esquerda;
            bisneto->cor = preto;

            noPai->esquerda = neto;
            neto->pai = noPai;
            irmao->pai = neto;
            irmao->direita = bisneto;
            bisneto->pai = irmao;
            neto->esquerda = irmao;
            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaEsquerda(noPai, neto);
        }else {
            bisneto = neto->direita;
            bisneto->cor = preto;

            neto->direita = bisneto->esquerda;
            bisneto->esquerda->pai = neto;

            noPai->esquerda = bisneto;
            bisneto->pai = noPai;

            bisneto->esquerda = irmao;
            irmao->pai = bisneto;

            if(noPai == noRaiz){
                noRaiz = bisneto;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaEsquerda(noPai, bisneto);
        }
    }else {
        neto = irmao->esquerda;
        if (neto->direita != NULL && neto->direita->cor == vermelho) {
            bisneto = neto->direita;
            bisneto->cor = preto;

            noPai->direita = neto;
            neto->pai = noPai;
            irmao->pai = neto;
            irmao->esquerda = bisneto;
            bisneto->pai = irmao;
            neto->direita = irmao;
            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoDireitaDireita(noPai, neto);
        }else {
            bisneto = neto->esquerda;
            bisneto->cor = preto;

            neto->esquerda = bisneto->direita;
            bisneto->direita->pai = neto;

            noPai->direita = bisneto;
            bisneto->pai = noPai;

            bisneto->direita = irmao;
            irmao->pai = bisneto;
            if(noPai == noRaiz){
                noRaiz = bisneto;
            }

            qtdOperacoesRemocao++;
            casoDireitaDireita(noPai, bisneto);
        }
    }
}

void removerCaso2_1_2(structNo* noPai, structNo* irmao) {
    if(noPai == noRaiz){
        noRaiz = irmao;
    }

    if (noPai->esquerda == irmao) {
        irmao->cor = preto;
        irmao->direita->cor = vermelho;

        qtdOperacoesRemocao++;
        casoEsquerdaEsquerda(noPai, irmao);
    }else {
        irmao->cor = preto;
        irmao->esquerda->cor = vermelho;

        qtdOperacoesRemocao++;
        casoDireitaDireita(noPai, irmao);
    }
}

void removerCaso2_2_1(structNo* noPai, structNo* irmao) {
    structNo* neto;
    if(irmao == noPai->esquerda) {
        if (irmao->esquerda != NULL && irmao->esquerda->cor == vermelho) {
            neto = irmao->esquerda;
            neto->cor = preto;

            if(noPai == noRaiz){
                noRaiz = irmao;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaEsquerda(noPai, irmao);
        }else {
            neto = irmao->direita;
            neto->cor = preto;

            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoEsquerdaDireita(noPai, irmao);
        }
    }else {
        if (irmao->direita != NULL && irmao->direita->cor == vermelho) {
            neto = irmao->direita;
            neto->cor = preto;

           if(noPai == noRaiz){
                noRaiz = irmao;
            }

            qtdOperacoesRemocao++;
            casoDireitaDireita(noPai, irmao);
        }else {
            neto = irmao->esquerda;
            neto->cor = preto;

            if(noPai == noRaiz){
                noRaiz = neto;
            }

            qtdOperacoesRemocao++;
            casoDireitaEsquerda(noPai, irmao);
        }
    }
}

void removerCaso2_2_2(structNo* noPai, structNo* irmao) {
    structNo* temp;
    irmao->cor = vermelho;

    if (noPai != NULL && noPai->pai != NULL) {
        temp = noPai;
        noPai = noPai->pai;
        if(temp == noPai->esquerda){
            irmao = noPai->direita;
        }else{
            irmao = noPai->esquerda;
        }

        removerCasos(noPai, irmao);
    }
}

void imprimirPosOrdem(structNo* no){
    if(no == NULL){
        return;
    }
    imprimirPosOrdem(no->esquerda);
    imprimirPosOrdem(no->direita);
    printf(" %d", no->valor);
}

void imprimirPreOrdem(structNo* no){
    if(no == NULL){
        return;
    }
    printf(" %d", no->valor);
    imprimirPreOrdem(no->esquerda);
    imprimirPreOrdem(no->direita);
}

void imprimirEmOrdem(structNo* no){
    if(no == NULL){
        return;
    }
    imprimirEmOrdem(no->esquerda);
    printf(" %d", no->valor);
    imprimirEmOrdem(no->direita);
}

void imprimirArvore(structNo* no){
    if(no != NULL){
        printf("%i", no->valor);
        printf("[");
        imprimirArvore(no->esquerda);
        imprimirArvore(no->direita);
        printf("]");
    }
}


