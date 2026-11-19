#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
/* Representacao interna: NAO mover para lse.h. */

typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;


typedef struct lse {
    t_elem *inicio;
    int tamanho;
} t_lse;


t_elem *lse_elem_criar(void* carga) {
    t_elem *e = malloc(sizeof(t_elem));
    if (e == NULL) {
        return NULL;
    }
    
    e->carga = carga;
    e->prox = NULL;
    return e;
}


t_lse *lse_criar(void) {
    t_lse *l = malloc(sizeof(t_lse));
    if (l == NULL) {
        return NULL;
    }
    l->inicio = NULL;
    l->tamanho = 0;
    
    return l;
}


int lse_tamanho(const t_lse *l) {
    if (l == NULL) {
        return -1;
    }

    return l->tamanho;
}


void *lse_primeiro(const t_lse *l) { 
    if (l == NULL) {
        return NULL;
    }

    if (l->inicio == NULL) {
        return NULL;
    }else{
        t_elem* e = l->inicio;
        return e->carga;
    }
}


int lse_inserir_inicio(t_lse *l, void *c) {
    t_elem* novo = lse_elem_criar(c);
    
    if (novo == NULL)
        return 0;
    
    if (l->inicio == NULL) {
        l->inicio = novo;
    }else{
        novo->prox = l->inicio;
        l->inicio = novo;
    }
    l->tamanho++;
    
    return 1;
    }


void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar){
    //implementar
}


int lse_inserir_fim(t_lse *l, void *c) {
    assert(l!=NULL);
    t_elem* novo = lse_elem_criar(c);
    
    if (novo == NULL)
        return 0;
    
    if (l->inicio == NULL){
        l->inicio = novo;
    } else{
        t_elem* cam = l->inicio;
        while (cam->prox != NULL){
            cam = cam->prox;
        }
        cam->prox = novo;
    }
    l->tamanho++;

    return 1;

   /* Se lista está vazia, o comportamento é o mesmo de inserir no inicio
    pegar endereço do início, percorrer toda lista até que endereço de próximo = NULL
    conectar o novo com o antigo proximo
    o novo agora vai ter prox = NULL
    obs: usar variável cam para percorrer lista
    mudar tamanho da lista +1*/ 
    
    } /* TODO M04 */

void *lse_remover_inicio(t_lse *l) { 
    assert(l == NULL);
    if (l->tamanho == 0)
        return NULL;

        t_elem* prim = l->inicio;
        l->inicio = prim->prox;

        void* c = prim->carga;
        free(prim);

        l->tamanho--;

        return c;


    /*Se a lista está vazia, não dá para remover no início: é necessário uma decisão*/

     } /* TODO M04 */


void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) {
    assert(l != NULL);
    t_elem* cam = l->inicio;

    while(cam != NULL)
    if (cmp(ch, cam->carga) == 0){
        return cam->carga;
    }else{
        cam = cam->prox;
    }

    /*percorrer a lista até achar valor igual à chave
    usar operação de subtração na comparação*/
    
    //(void)l; (void)ch; (void)cmp; return NULL;
    } /* TODO M04 */



void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) {
    assert(l != NULL);
    t_elem* cam = l->inicio;
    t_elem* ant = NULL;
    bool achou = false;

    while ((cam != NULL) && (!achou)){
        if (cmp(ch, cam->carga) == 0) {
            achou = true;
        }else{
            ant = cam;
            cam = cam->prox;
        }
    }
    
    if (!achou){
        return NULL;
    }else{
        if (l->inicio == cam){
            l->inicio = cam->prox;
        }else{
            ant->prox = cam->prox;
        }
        void* c = cam->prox;
        free(cam);
        return c;
    }


    //(void)l; (void)ch; (void)cmp; return NULL;
    

        /*lógica parecida com a busca*/

    
} /* TODO M04 */




int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */



void lse_destruir(t_lse *l, t_lse_destruir_carga destruir_carga) {
    if (l == NULL) {
        return;
    }
    
    if(destruir_carga != NULL) {
        if (l->inicio == NULL) {
            free(l);
            return;
        }

        t_elem* cam = l->inicio;
        while(cam != NULL) {
            t_elem* prox = cam->prox;
            destruir_carga(cam->carga);
            free(cam);
            cam = prox;
        }
        free(l);
    }
}


typedef int (*t_comparador)(void* chave, void* carga);
