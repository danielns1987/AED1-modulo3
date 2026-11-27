#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>


typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;


typedef struct lse {
    t_elem *inicio;
    int tamanho;
} t_lse;


void *lse_elem_criar(void* carga) {
    t_elem *novo = malloc(sizeof(t_elem));
    if (novo == NULL) {
        return NULL;
    }
    
    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}


t_lse *lse_criar(void) {
    t_lse *lista = malloc(sizeof(t_lse));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
    
    return lista;
}


int lse_tamanho(const t_lse *lista) {
    if (lista == NULL) {
        return -1;
    }

    return lista->tamanho;
}


void *lse_primeiro(const t_lse *lista) { 
    if (lista == NULL) {
        return NULL;
    }

    if (lista->inicio == NULL) {
        return NULL;
    }else{
        t_elem* elem = lista->inicio;
        return elem->carga;
    }
}


int lse_inserir_inicio(t_lse *lista, void *carga) {
    if (lista == NULL) {
        return 0;
    }

    t_elem* novo = lse_elem_criar(carga);
    if (novo == NULL) {
        return 0;
    }

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }
    lista->tamanho++;

    return 1;
}


int lse_inserir_fim(t_lse *lista, void *carga) {
    if (lista == NULL) return 0;

    t_elem* novo = lse_elem_criar(carga);
    if (novo == NULL) return 0;

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        t_elem* cam = lista->inicio;
        while (cam->prox != NULL) cam = cam->prox;
        cam->prox = novo;
    }
    lista->tamanho++;
    return 1;
}
 


void *lse_remover_inicio(t_lse *lista) {
    if (lista == NULL || lista->tamanho == 0) return NULL;

    t_elem* prim = lista->inicio;
    lista->inicio = prim->prox;
    void* carga = prim->carga;
    free(prim);
    lista->tamanho--;
    return carga;
} 


 void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar){
    if (lista == NULL || cb_visitar == NULL) {
        return;
    }

    t_elem* cam = lista->inicio;
    while (cam != NULL) {
        cb_visitar(cam->carga);
        cam = cam->prox;
    }
}    


void *lse_buscar(const t_lse *lista, const void *ch, t_comparador cmp) {
    if (lista == NULL || cmp == NULL) return NULL;

    t_elem* cam = lista->inicio;
    while (cam != NULL) {
        if (cmp(cam->carga, ch) == 0) return cam->carga;
        cam = cam->prox;
    }
    return NULL;
} 


void *lse_remover(t_lse *lista, const void *ch, t_comparador cmp) {
    if (lista == NULL || cmp == NULL) return NULL;

    t_elem* cam = lista->inicio;
    t_elem* ant = NULL;

    while (cam != NULL && cmp(cam->carga, ch) != 0) {
        ant = cam;
        cam = cam->prox;
    }
    if (cam == NULL) return NULL;

    if (ant == NULL) lista->inicio = cam->prox;
    else ant->prox = cam->prox;

    void* carga = cam->carga;
    free(cam);
    lista->tamanho--;
    return carga;
} 

int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar) {
    if ((lista == NULL) || (comparar == NULL)) {
        return 0;
    }

    t_elem *novo = lse_elem_criar(carga);
    if (novo == NULL) {
        return 0;
    }
      
        // Insere no inicio so se vazia ou se a nova carga for estritamente menor.
    // Contrato: comparar(carga_existente, carga_nova). Empate vai depois dos iguais. 
   
       if ((lista->inicio == NULL) || (comparar(lista->inicio->carga, carga) > 0)) {
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->tamanho++;
        return 1;
    } 
   
    t_elem *cam = lista->inicio;
       while ((cam->prox != NULL) && (comparar(cam->prox->carga, carga) <= 0)) { 
        cam = cam->prox;
    }

    novo->prox = cam->prox;
    cam->prox = novo;
    lista->tamanho++;

    return 1;
}
    

void lse_destruir(t_lse *lista, t_lse_destruir_carga destruir_carga) {
    if (lista == NULL) {
        return;
    }

    t_elem* cam = lista->inicio;
    while (cam != NULL) {
        t_elem* prox = cam->prox;
        if (destruir_carga != NULL) {
            destruir_carga(cam->carga);
        }
        free(cam);
        cam = prox;
    }

    free(lista);
}
 
