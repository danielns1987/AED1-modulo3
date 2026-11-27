#include <stdlib.h>
#include "musica.h"
#include "pilha.h"

typedef struct player{
    t_musica *atual;
    t_pilha *historico;
    t_pilha *avanco;
} t_player;


t_player *player_criar(void){
    t_player *p = malloc(sizeof(t_player));
    if (p == NULL) {
        return NULL;
    }
    p->atual = NULL;
    p->historico = pilha_criar();
    p->avanco = pilha_criar();
    if (p->historico == NULL || p->avanco == NULL) {
        player_destruir(p);
        return NULL;
    }
    return p;
}


int player_reproduzir(t_player *p, t_musica *m){
    if ((p == NULL) || (m == NULL)){
        return 0;
    }

    if (p->atual != NULL) {
        if (p->atual != m) {
            if (p->avanco != NULL)
                pilha_desempilhar(p->avanco);
            if (p->historico != NULL)
                pilha_empilhar(p->historico, p->atual);
        }
    }
    
    p->atual = m;

    return 1;
}


int player_anterior(t_player *p){
    if (p == NULL || p->historico == NULL || p->atual == NULL) {
        return 0;
    }
    
    pilha_empilhar(p->avanco, p->atual);
    p->atual = pilha_desempilhar(p->historico);

    return 1;
}


int player_avancar(t_player *p){
    if (p == NULL || p->avanco == NULL || p->atual == NULL)
        return 0;

    pilha_empilhar(p->historico, p->atual);
    p->atual = pilha_desempilhar(p->avanco);

    return 1;
}


t_musica *player_atual(const t_player *p){
    if (p == NULL || p->atual == NULL){
        return NULL;
    }

    return p->atual;
}

void player_destruir(t_player *p){
    if (p == NULL)
        return;

    pilha_destruir(p->historico, NULL);
    pilha_destruir(p->avanco, NULL);
    free(p);
}
