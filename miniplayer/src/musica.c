#include "musica.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {
    
    t_musica* musica = malloc(sizeof(t_musica));
    if (musica == NULL) {
        return NULL;
    }

    musica->id = id;
    snprintf(musica->titulo, sizeof(musica->titulo), "%s", titulo);
    snprintf(musica->artista, sizeof(musica->artista), "%s", artista);
    musica->duracao = duracao;

    return musica;
}

void musica_destruir(void *carga) { 

    if (carga == NULL) {
        return;
    }
    
    free(carga);

}
