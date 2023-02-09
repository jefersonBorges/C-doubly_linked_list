/*Exercício - 0

Manipulação de listas duplamente encadeadas

Em uma lista encadeada de pontos turísitcos, implementar as seguintes operações:

a) inserir_final()*
b) buscar_nodo() *
c) remover_nodo()
d) imprimir_lista()
e) imprimir_lista_invertida() *
f) liberar_lista() *
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TAM 41

struct PontoTuristico{
    char descricao[TAM];
    float latitude;
    float longitude;
    struct PontoTuristico *anterior;
    struct PontoTuristico *proximo;
};
typedef struct PontoTuristico PontoTuristico;

struct DescritorLista{
    PontoTuristico *ponto_inicial;
    PontoTuristico *ponto_final;
    int tamanho_lista;
};
typedef struct DescritorLista DescritorLista;

void criar_lista(DescritorLista *descritor_lista){
    descritor_lista->ponto_inicial = NULL;
    descritor_lista->ponto_final = NULL;
    descritor_lista->tamanho_lista = 0;
}

void ler_pontoTuristico(PontoTuristico *aux){
    printf("\nDescricao: ");
    scanf("%[^\n]", aux->descricao);
    fflush(stdin);

    printf("\nLatitude: ");
    scanf("%f", &aux->latitude);
    fflush(stdin);

    printf("\nLongitude: ");
    scanf("%f", &aux->longitude);
    fflush(stdin);
}

int lista_eh_vazia(DescritorLista *lista){
    return (lista->ponto_inicial == NULL && lista->ponto_final == NULL);
}

void inserirInicio_lista(DescritorLista *lista){
    PontoTuristico *novo = (PontoTuristico*)malloc(sizeof(PontoTuristico));
    ler_pontoTuristico(novo);

    if(lista_eh_vazia(lista)){
        novo->anterior = NULL;
        novo->proximo = NULL;
        lista->ponto_final = novo;
    } else {
        novo->proximo = lista->ponto_inicial;
        novo->anterior = NULL;
        lista->ponto_inicial->anterior = novo;
    }
    lista->ponto_inicial = novo;
    lista->tamanho_lista ++;
}

//a) inserir_final()
void inserirFinal_lista(DescritorLista *lista){
    printf("\nInserindo no final da lista");
    PontoTuristico *novo = (PontoTuristico*)malloc(sizeof(PontoTuristico));
    ler_pontoTuristico(novo);

    if(lista_eh_vazia(lista)){
        printf("\nLista vazia");
        lista->ponto_inicial = novo;
        novo->anterior = NULL;
        novo->proximo = NULL;

    } else {
        printf("\nLista nao vazia");
        novo->anterior = lista->ponto_final;
        novo->proximo = NULL;
        lista->ponto_final->proximo = novo;
        printf("\nSaindo Lista nao vazia");
    }
    lista->ponto_final = novo;
    lista->tamanho_lista ++;
}

void imprimir_ponto(PontoTuristico *paux){
    printf(
        "\nDescricao: %s\tLatitude: %.2f\tLongitude: %.2f",
        paux->descricao, paux->latitude, paux->longitude
    );
}

//b) buscar_nodo()
PontoTuristico* buscar_lista(DescritorLista *lista){
    char *descricao;
    printf("\nQual descricao deseja buscar?");
    scanf("%[^\n]", descricao);
    fflush(stdin);
    printf("\nBuscando: %s na lista", descricao);
    PontoTuristico *paux;
    for(paux = lista->ponto_inicial; paux != NULL; paux = paux->proximo){
        if(strcmp(descricao, paux->descricao) == 0){
            imprimir_ponto(paux);
            return paux;
        }
    }
    printf("\nBusca nao Encontrada");
    return NULL;
}

int posicao_descritorLista(DescritorLista *lista, PontoTuristico *paux){
    /*
        retorna 1 se for inicial
        retorna -1 se for final
        retorna 0 se não for nenhum dos dois
    */
    if(strcmp(paux->descricao, lista->ponto_inicial->descricao) == 0){
        return 1;
    } else if(strcmp(paux->descricao, lista->ponto_final->descricao) == 0){
        return -1;
    } else {
        return 0;
    }
}

//c) remover_nodo()
void remover_lista(DescritorLista *lista){
    printf("\nRemovendo nodo da lista");
    PontoTuristico *paux;
    paux = buscar_lista(lista);
    if(paux != NULL){
        int res = posicao_descritorLista(lista, paux);
        switch (res){
            case 1:
                printf("\nNodo inicial");
                lista->ponto_inicial = paux->proximo;
                paux->proximo->anterior = NULL;
            break;
            case -1:
                printf("\nNodo final");
                lista->ponto_final = paux->anterior;
                paux->anterior->proximo = NULL;
            break;
            default:
            printf("\nNodo do meio");
                paux->proximo->anterior = paux->anterior;
                paux->anterior->proximo = paux->proximo;
            break;
        }
        free(paux);
        lista->tamanho_lista--;
        printf("\nNodo removido");
    } else {
        printf("\nNodo nao encontrado");
    }
}

//d) imprimir_lista()
void imprime_lista(DescritorLista *lista){
    printf("\nImprimindo Normalmente Lista Duplamente encadeada");
    PontoTuristico *paux = lista->ponto_inicial;
    for(paux; paux != NULL; paux = paux->proximo){
        imprimir_ponto(paux);
    }
}

//e)imprimir_lista_invertida()
void imprimeInvertido_lista(DescritorLista *lista){
    printf("\nImprimindo Invertido Lista Duplamente encadeada");
    PontoTuristico *paux = lista->ponto_final;
    for(paux; paux != NULL; paux = paux->anterior){
        imprimir_ponto(paux);
    }
}

//f) liberar_lista()
void liberar_lista(DescritorLista *lista){
    PontoTuristico *paux = lista->ponto_inicial, *aux = NULL;
    while(paux != NULL){
        aux = paux->proximo;
        printf("\nApagando");
        imprimir_ponto(paux);
        free(paux);
        paux = aux;
    }
    criar_lista(lista);
}

int main(){
    DescritorLista *lista;
    lista = (DescritorLista*) malloc(sizeof(DescritorLista));
    PontoTuristico *busca;
    printf("\nLista Duplamente encadeada");
    criar_lista(lista);

    inserirInicio_lista(lista);
    inserirInicio_lista(lista);

    inserirFinal_lista(lista);
    inserirFinal_lista(lista);

    imprime_lista(lista);
    imprimeInvertido_lista(lista);

    busca = buscar_lista(lista);

    remover_lista(lista);
    imprime_lista(lista);

    liberar_lista(lista);
    imprime_lista(lista);

    return 0;
}