#include "musica.h"
#include <stddef.h>
/* M01: substituir stubs por alocacao, copia segura de strings e free. */
t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {
    (void)id; (void)titulo; (void)artista; (void)duracao;
    return NULL; /* TODO M01 */
}
void musica_destruir(void *carga) { (void)carga; /* TODO M01 */ }
