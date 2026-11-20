/* Testes aditivos da M03. Executar a partir da raiz com o Makefile incremental. */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"
#include "musica.h"

static int visitas_total = 0;
static int ordem_ints[10];
static int ordem_ids[10];

static void resetar_rastreamento(void) {
    visitas_total = 0;
    for (int i = 0; i < 10; i++) {
        ordem_ints[i] = 0;
        ordem_ids[i] = 0;
    }
}

static void visitar_int(void *carga) {
    assert(carga != NULL);
    assert(visitas_total < 10);
    ordem_ints[visitas_total++] = *(int *)carga;
}

static void visitar_musica(void *carga) {
    assert(carga != NULL);
    assert(visitas_total < 10);
    ordem_ids[visitas_total++] = ((t_musica *)carga)->id;
}

static void destruir_int(void *carga) {
    free(carga);
}

/* 1. Lista vazia: tamanho 0, primeiro NULL, percurso sem visitas */
static void teste_lista_vazia(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);

    resetar_rastreamento();
    lse_percorrer(l, visitar_int);
    assert(visitas_total == 0);

    lse_destruir(l, NULL);
}

/* 2. Inserção de um elemento: tamanho 1, primeiro correto, percurso com uma visita */
static void teste_insercao_um_elemento(void) {
    int valor = 42;
    t_lse *l = lse_criar();
    assert(l != NULL);

    assert(lse_inserir_inicio(l, &valor) != 0);
    assert(lse_tamanho(l) == 1);
    assert(lse_primeiro(l) == &valor);
    assert(*(int *)lse_primeiro(l) == 42);

    resetar_rastreamento();
    lse_percorrer(l, visitar_int);
    assert(visitas_total == 1);
    assert(ordem_ints[0] == 42);

    lse_destruir(l, NULL);
    assert(valor == 42);
}

/* 3. Inserção de três elementos: percurso em ordem inversa à inserção (LIFO na cabeça) */
static void teste_insercao_tres_elementos_lifo(void) {
    int v1 = 10, v2 = 20, v3 = 30;
    t_lse *l = lse_criar();
    assert(l != NULL);

    assert(lse_inserir_inicio(l, &v1) != 0);
    assert(lse_inserir_inicio(l, &v2) != 0);
    assert(lse_inserir_inicio(l, &v3) != 0);

    assert(lse_tamanho(l) == 3);
    assert(lse_primeiro(l) == &v3);

    resetar_rastreamento();
    lse_percorrer(l, visitar_int);
    assert(visitas_total == 3);
    assert(ordem_ints[0] == 30);
    assert(ordem_ints[1] == 20);
    assert(ordem_ints[2] == 10);

    lse_destruir(l, NULL);
}

/* 4. Independência da carga: testes com t_musica */
static void teste_carga_generica_musica(void) {
    t_musica *m1 = musica_criar(1, "Titulo1", "Artista1", 180);
    t_musica *m2 = musica_criar(2, "Titulo2", "Artista2", 200);
    t_musica *m3 = musica_criar(3, "Titulo3", "Artista3", 220);
    assert(m1 != NULL && m2 != NULL && m3 != NULL);

    t_lse *l = lse_criar();
    assert(l != NULL);

    assert(lse_inserir_inicio(l, m1) != 0);
    assert(lse_inserir_fim(l, m2) != 0);
    assert(lse_inserir_fim(l, m3) != 0);

    assert(lse_tamanho(l) == 3);
    assert(lse_primeiro(l) == m1);

    resetar_rastreamento();
    lse_percorrer(l, visitar_musica);
    assert(visitas_total == 3);
    assert(ordem_ids[0] == 1);
    assert(ordem_ids[1] == 2);
    assert(ordem_ids[2] == 3);

    /* Sem destruir as cargas automaticamente */
    lse_destruir(l, NULL);
    assert(m1->id == 1);
    assert(m2->id == 2);
    assert(m3->id == 3);

    musica_destruir(m1);
    musica_destruir(m2);
    musica_destruir(m3);
}

/* 5. Destruição: callback destrutor com cargas alocadas no heap */
static void teste_destruicao_com_callback(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);

    int *carga1 = malloc(sizeof(int));
    int *carga2 = malloc(sizeof(int));
    int *carga3 = malloc(sizeof(int));
    assert(carga1 != NULL && carga2 != NULL && carga3 != NULL);

    *carga1 = 100;
    *carga2 = 200;
    *carga3 = 300;

    assert(lse_inserir_inicio(l, carga1) != 0);
    assert(lse_inserir_fim(l, carga2) != 0);
    assert(lse_inserir_fim(l, carga3) != 0);

    lse_destruir(l, destruir_int);
}

/* 6. Robustez: lse_inserir_inicio(NULL, ...) falha sem causar acesso inválido */
static void teste_robustez(void) {
    int x = 99;
    assert(lse_inserir_inicio(NULL, NULL) == 0);
    assert(lse_inserir_inicio(NULL, &x) == 0);
}

int main(void) {
    teste_lista_vazia();
    teste_insercao_um_elemento();
    teste_insercao_tres_elementos_lifo();
    teste_carga_generica_musica();
    teste_destruicao_com_callback();
    teste_robustez();

    puts("M03: todos os testes passaram.");
    return 0;
}