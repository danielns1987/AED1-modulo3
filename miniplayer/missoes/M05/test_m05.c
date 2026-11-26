/* Testes incrementais M05 — não acessar campos privados de t_lse/t_elem. */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "lse.h"

static int comparar_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

typedef struct { int id; const char *titulo; int duracao; } musica_t;

static int comparar_musica(const void *a, const void *b) {
    int x = ((const musica_t *)a)->id, y = ((const musica_t *)b)->id;
    return (x > y) - (x < y);
}

static int comparar_musica_titulo(const void *a, const void *b) {
    return strcmp(((const musica_t *)a)->titulo, ((const musica_t *)b)->titulo);
}

static int comparar_musica_duracao(const void *a, const void *b) {
    int x = ((const musica_t *)a)->duracao, y = ((const musica_t *)b)->duracao;
    return (x > y) - (x < y);
}

/* coletores via lse_percorrer (nao acessam campos privados) */
static int ints[64]; static int n_ints;
static void coletar_int(void *carga) {
    assert(n_ints < 64);
    ints[n_ints++] = *(int *)carga;
}

static const musica_t *musicas[64]; static int n_musicas;
static void coletar_musica(void *carga) {
    assert(n_musicas < 64);
    musicas[n_musicas++] = (const musica_t *)carga;
}

static int lista_esta_ordenada(void) {
    for (int i = 1; i < n_ints; i++)
        if (ints[i-1] > ints[i]) return 0;
    return 1;
}

static void teste_vazia_inicio_meio_fim(void) {
    t_lse *l = lse_criar(); assert(l);

    /* vazia */
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);
    n_ints = 0; lse_percorrer(l, coletar_int);
    assert(n_ints == 0);

    int v10 = 10, v5 = 5, v7 = 7, v20 = 20;

    /* vazia -> primeiro elemento */
    assert(lse_inserir_ordenado(l, &v10, comparar_int) == 1);
    assert(lse_tamanho(l) == 1);
    assert(lse_primeiro(l) == &v10);

    /* inicio (5 < 10) */
    assert(lse_inserir_ordenado(l, &v5, comparar_int) == 1);
    assert(lse_tamanho(l) == 2);
    assert(lse_primeiro(l) == &v5);

    /* meio (5 < 7 < 10) */
    assert(lse_inserir_ordenado(l, &v7, comparar_int) == 1);
    assert(lse_tamanho(l) == 3);

    /* fim (20 > todos) */
    assert(lse_inserir_ordenado(l, &v20, comparar_int) == 1);
    assert(lse_tamanho(l) == 4);

    /* ordem final: 5, 7, 10, 20 */
    n_ints = 0; lse_percorrer(l, coletar_int);
    assert(n_ints == 4);
    assert(ints[0] == 5 && ints[1] == 7 && ints[2] == 10 && ints[3] == 20);
    assert(lista_esta_ordenada());

    /* sequencia mista: lista ordenada apos cada insercao (criterio enunciado) */
    lse_destruir(l, NULL);
    l = lse_criar(); assert(l);
    int vals[] = {30, 10, 20, 50, 40};
    for (int i = 0; i < 5; i++) {
        assert(lse_inserir_ordenado(l, &vals[i], comparar_int) == 1);
        assert(lse_tamanho(l) == i + 1);            /* +1 exato */
        n_ints = 0; lse_percorrer(l, coletar_int);
        assert(lista_esta_ordenada());              /* invariante pos-insercao */
        assert(n_ints == lse_tamanho(l));           /* alcancaveis == tamanho */
    }

    /* musicas por id/titulo/duracao (nao alterar lse.c) */
    lse_destruir(l, NULL);
    l = lse_criar(); assert(l);
    musica_t m1={3,"Azul",200}, m2={1,"Bola",150}, m3={2,"Casa",200},
             m4={4,"Dado",150}, m5={5,"Eco",300};
    lse_inserir_ordenado(l, &m1, comparar_musica);
    lse_inserir_ordenado(l, &m2, comparar_musica);
    lse_inserir_ordenado(l, &m3, comparar_musica);
    lse_inserir_ordenado(l, &m4, comparar_musica);
    lse_inserir_ordenado(l, &m5, comparar_musica);
    assert(lse_tamanho(l) == 5);
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 5);
    assert(musicas[0]==&m2 && musicas[1]==&m3 && musicas[2]==&m1
           && musicas[3]==&m4 && musicas[4]==&m5);        /* ordenada por id */
    musica_t chave = {2, "", 0};
    assert(lse_buscar(l, &chave, comparar_musica) == &m3); /* busca no ordenado */

    /* ordenada por titulo (strcmp) sem alterar lse.c */
    lse_destruir(l, NULL); l = lse_criar(); assert(l);
    lse_inserir_ordenado(l, &m4, comparar_musica_titulo);
    lse_inserir_ordenado(l, &m2, comparar_musica_titulo);
    lse_inserir_ordenado(l, &m5, comparar_musica_titulo);
    lse_inserir_ordenado(l, &m1, comparar_musica_titulo);
    lse_inserir_ordenado(l, &m3, comparar_musica_titulo);
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 5);
    assert(musicas[0]==&m1 && musicas[1]==&m2 && musicas[2]==&m3
           && musicas[3]==&m4 && musicas[4]==&m5);        /* Azul,Bola,Casa,Dado,Eco */

    /* ordenada por duracao, empates estaveis (150: m2,m4 | 200: m1,m3) */
    lse_destruir(l, NULL); l = lse_criar(); assert(l);
    lse_inserir_ordenado(l, &m1, comparar_musica_duracao);
    lse_inserir_ordenado(l, &m2, comparar_musica_duracao);
    lse_inserir_ordenado(l, &m3, comparar_musica_duracao);
    lse_inserir_ordenado(l, &m4, comparar_musica_duracao);
    lse_inserir_ordenado(l, &m5, comparar_musica_duracao);
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 5);
    assert(musicas[0]==&m2 && musicas[1]==&m4);            /* 150: m2,m4 (ordem chegada) */
    assert(musicas[2]==&m1 && musicas[3]==&m3);            /* 200: m1,m3 (ordem chegada) */
    assert(musicas[4]==&m5);                                /* 300 */

    lse_destruir(l, NULL);
}

static void teste_duplicados_estaveis(void) {
    musica_t a={10,"primeira",1}, b={10,"segunda",2},
             c={5,"menor",3},    d={10,"terceira",4};
    t_lse *l=lse_criar(); assert(l);

    /* chegada: a(10), b(10), c(5), d(10) — empates em id 10 */
    assert(lse_inserir_ordenado(l, &a, comparar_musica) == 1);
    assert(lse_tamanho(l) == 1);
    assert(lse_inserir_ordenado(l, &b, comparar_musica) == 1);
    assert(lse_tamanho(l) == 2);
    assert(lse_inserir_ordenado(l, &c, comparar_musica) == 1);
    assert(lse_tamanho(l) == 3);
    assert(lse_inserir_ordenado(l, &d, comparar_musica) == 1);
    assert(lse_tamanho(l) == 4);

    /* ordem esperada: menor(5), primeira(10), segunda(10), terceira(10)
       -> entre os id 10, a ordem de chegada a,b,d deve ser preservada. */
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 4);
    assert(musicas[0] == &c);     /* 5 no inicio */
    assert(musicas[1] == &a);     /* 1a chegada entre id 10 */
    assert(musicas[2] == &b);     /* 2a chegada entre id 10 */
    assert(musicas[3] == &d);     /* 3a chegada entre id 10 */

    /* triplo empate no inicio */
    lse_destruir(l, NULL); l = lse_criar(); assert(l);
    musica_t e1={3,"a1",1}, e2={3,"a2",2}, e3={3,"a3",3}, e4={5,"z",4};
    lse_inserir_ordenado(l, &e1, comparar_musica);
    lse_inserir_ordenado(l, &e2, comparar_musica);
    lse_inserir_ordenado(l, &e3, comparar_musica);
    lse_inserir_ordenado(l, &e4, comparar_musica);
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 4);
    assert(musicas[0]==&e1 && musicas[1]==&e2 && musicas[2]==&e3 && musicas[3]==&e4);

    /* empate no fim */
    lse_destruir(l, NULL); l = lse_criar(); assert(l);
    musica_t f1={9,"p1",1}, f2={9,"p2",2};
    lse_inserir_ordenado(l, &f1, comparar_musica);
    lse_inserir_ordenado(l, &f2, comparar_musica);
    n_musicas = 0; lse_percorrer(l, coletar_musica);
    assert(n_musicas == 2);
    assert(musicas[0]==&f1 && musicas[1]==&f2);

    lse_destruir(l, NULL);
}

static void teste_invalido_e_reinsercao(void) {
    int v1 = 1, v2 = 2, v3 = 3, chave2 = 2;
    t_lse *l = lse_criar(); assert(l);

    /* argumentos invalidos: retorna 0 e a lista nao muda */
    assert(lse_inserir_ordenado(NULL, &v1, comparar_int) == 0);
    assert(lse_inserir_ordenado(l, &v1, NULL) == 0);
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);

    /* ordenada: 1, 2, 3 */
    assert(lse_inserir_ordenado(l, &v2, comparar_int) == 1);
    assert(lse_inserir_ordenado(l, &v1, comparar_int) == 1);
    assert(lse_inserir_ordenado(l, &v3, comparar_int) == 1);
    assert(lse_tamanho(l) == 3);

    /* remove o do meio e reinsere na posicao ordenada correta */
    assert(lse_remover(l, &chave2, comparar_int) == &v2);
    assert(lse_tamanho(l) == 2);
    assert(lse_inserir_ordenado(l, &v2, comparar_int) == 1);
    assert(lse_tamanho(l) == 3);

    n_ints = 0; lse_percorrer(l, coletar_int);
    assert(n_ints == 3);
    assert(ints[0] == 1 && ints[1] == 2 && ints[2] == 3);

    /* regressao M03/M04: vazia, remocao de inexistente, args NULL */
    assert(lse_remover(l, &chave2, comparar_int) == &v2);
    assert(lse_remover(l, &chave2, comparar_int) == NULL);       /* ja nao existe */
    assert(lse_tamanho(l) == 2);
    assert(lse_buscar(NULL, &v1, comparar_int) == NULL);
    assert(lse_buscar(l, &v1, NULL) == NULL);
    assert(lse_remover(NULL, &v1, comparar_int) == NULL);
    assert(lse_inserir_fim(NULL, &v1) == 0);

    /* reinserir apos remocao continua ordenada */
    assert(lse_inserir_ordenado(l, &v2, comparar_int) == 1);
    n_ints = 0; lse_percorrer(l, coletar_int);
    assert(ints[0] == 1 && ints[1] == 2 && ints[2] == 3);

    lse_destruir(l, NULL);
}

int main(void) {
    teste_vazia_inicio_meio_fim();
    teste_duplicados_estaveis();
    teste_invalido_e_reinsercao();
    puts("M05: todos os testes passaram.");
    return 0;
} 