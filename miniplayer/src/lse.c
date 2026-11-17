#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
/* Representacao interna: NAO mover para lse.h. */

typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;


typedef struct lse {
    t_elem *inicio;
    int tamanho;
} t_lse;


t_elem* lse_elem_criar(void* carga) {
    t_elem *novo = malloc(sizeof(t_elem));
    novo->carga = carga;
    novo->prox = NULL;
}


t_lse *lse_criar(void) {
    t_lse *l = malloc(sizeof(t_lse));
    if (l == NULL) {
        return NULL;
    }
    l->inicio = NULL;
    l->tamanho = 0;
    
    return l;
} /* TODO M02/M03 */


int lse_tamanho(const t_lse *l) {
    if (l == NULL) {
        return -1;
    }

    return l->tamanho;
} /* TODO M03 */


t_elem *lse_primeiro(const t_lse *l) { 
    if (l == NULL) {
        return NULL;
    }

    if (l->inicio == NULL) {
        return NULL;
    }else{

    }
} /* TODO M03 */


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
    } /* TODO M04 */


int lse_inserir_fim(t_lse *l, void *c) { (void)l; (void)c; return 0; } /* TODO M04 */
void *lse_remover_inicio(t_lse *l) { (void)l; return NULL; } /* TODO M04 */
void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */


void lse_destruir(t_lse *l, t_lse_destruir_carga destruir_carga) {
    if (l == NULL) {
        return;
    }
    
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

 /* TODO M03 */
}
