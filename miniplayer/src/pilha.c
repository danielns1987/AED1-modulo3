#include "pilha.h"
#include "lse.h"
#include <stdlib.h>

typedef struct pilha {
    t_lse *lista;
    int altura;
} t_pilha;
/* M06: implementar apenas delegando para lse_*. */


t_pilha *pilha_criar(void) {
    t_pilha *p = malloc(sizeof(t_pilha));
    p->lista = lse_criar();
    p->altura = 0;
    return p;
}


int pilha_empilhar(t_pilha *p, void *c) {
    lse_inserir_inicio(p->lista, c);
    p->altura++;
    return 1;
}


void *pilha_desempilhar(t_pilha *p) {
    t_elem *c = lse_remover_inicio(p->lista);
    p->altura--;
    return c;
    }


void *pilha_topo(const t_pilha *p) {
    t_elem *c = lse_primeiro(p->lista);
    return c;
}


void pilha_destruir(t_pilha *p, t_lse_destruir_carga d) {
    lse_destruir(p->lista, d);
    free(p);
}
