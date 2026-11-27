#include <assert.h>
#include <stdio.h>
#include "player.h"
#include "musica.h"

static void navegacao(void) {
    t_musica a={.id=1}, b={.id=2}, c={.id=3}, d={.id=4};
    t_player *p=player_criar(); assert(p);
    assert(player_atual(p)==NULL);
    assert(player_anterior(p)==0 && player_avancar(p)==0);
    assert(player_reproduzir(p,&a)==1);
    assert(player_anterior(p)==0);
    assert(player_reproduzir(p,&b)==1);
    assert(player_reproduzir(p,&c)==1);
    assert(player_anterior(p)==1 && player_atual(p)==&b);
    assert(player_anterior(p)==1 && player_atual(p)==&a);
    assert(player_anterior(p)==0 && player_atual(p)==&a);
    assert(player_avancar(p)==1 && player_atual(p)==&b);
    assert(player_avancar(p)==1 && player_atual(p)==&c);
    assert(player_avancar(p)==0 && player_atual(p)==&c);
    assert(player_anterior(p)==1 && player_atual(p)==&b);
    assert(player_reproduzir(p,&b)==1);
    assert(player_avancar(p)==1 && player_atual(p)==&c);
    assert(player_anterior(p)==1 && player_atual(p)==&b);
    assert(player_reproduzir(p,&d)==1 && player_atual(p)==&d);
    assert(player_avancar(p)==0 && player_atual(p)==&d);
    assert(player_anterior(p)==1 && player_atual(p)==&b);
    assert(player_anterior(p)==1 && player_atual(p)==&a);
    assert(player_anterior(p)==0);
    player_destruir(p);
    assert(a.id==1 && b.id==2 && c.id==3 && d.id==4);
}
static void independentes(void) {
    t_musica a={.id=1}, b={.id=2};
    t_player *p=player_criar(), *q=player_criar(); assert(p && q);
    assert(player_reproduzir(p,&a)==1);
    assert(player_reproduzir(q,&b)==1);
    assert(player_reproduzir(p,&b)==1);
    assert(player_reproduzir(p,&a)==1);
    assert(player_anterior(p)==1 && player_atual(p)==&b);
    assert(player_anterior(p)==1 && player_atual(p)==&a);
    assert(player_anterior(p)==0);
    player_destruir(p);
    assert(player_atual(q)==&b && player_anterior(q)==0);
    player_destruir(q);
}
static void invalidos(void) {
    t_musica a={.id=1};
    assert(player_reproduzir(NULL,&a)==0);
    assert(player_anterior(NULL)==0 && player_avancar(NULL)==0);
    assert(player_atual(NULL)==NULL); player_destruir(NULL);
    t_player *p=player_criar(); assert(p);
    assert(player_reproduzir(p,NULL)==0 && player_atual(p)==NULL);
    assert(player_reproduzir(p,&a)==1);
    assert(player_reproduzir(p,NULL)==0 && player_atual(p)==&a);
    player_destruir(p);
    p=player_criar(); assert(p); player_destruir(p);
}
int main(void) {
    navegacao(); independentes(); invalidos();
    puts("M07: todos os testes passaram."); return 0;
}
