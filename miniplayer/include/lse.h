#ifndef LSE_H
#define LSE_H

typedef struct elem t_elem;
typedef struct lse t_lse;
typedef int (*t_comparador)(const void *carga, const void *chave);
typedef void(*t_lse_destruir_carga)(void* carga);
typedef void(*t_lse_visitar)(void* carga);
void* lse_elem_criar(void* carga);
t_lse *lse_criar(void);
int lse_tamanho(const t_lse *lista);
void *lse_primeiro(const t_lse *lista);
int lse_inserir_inicio(t_lse *lista, void *carga);
int lse_inserir_fim(t_lse *lista, void *carga);
void *lse_remover_inicio(t_lse *lista);
void lse_percorrer(const t_lse *lista, t_lse_visitar cb_visitar);
void *lse_buscar(const t_lse *lista, const void *ch, t_comparador cmp);
void *lse_remover(t_lse *lista, const void *ch, t_comparador cmp);
int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar);
void lse_destruir(t_lse *lista, t_lse_destruir_carga destruir_carga);
#endif
