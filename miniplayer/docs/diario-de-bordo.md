# Diário de bordo
## Missão M01 — 11/11
- Integrantes e papéis:
    Daniel Nunes Santos: implementação
    José Eduardo Araujo Costa Melo: documentação

- Objetivo:
    Implementar musica_criar e musica_destruir
    Substituir stubs por alocacao, copia segura de strings e free

- O que implementamos:
    Funções musica_criar e musica_destruir em musica.c, cumprindo as tarefas de alocação (função malloc), cópia segura (função snprinf) e liberação de memória (função free).

- Decisão técnica e justificativa:
    A "cópia segura de strings" foi realizada com uso da função snprintf, que garante a limitação do tamanho e a terminação nula.

- Problema encontrado e solução:

- Evidências de testes:
    Saída do terminal:
    daniel@LAPTOP-HALO0GS1:/mnt/c/Users/dream/OneDrive/Área de Trabalho/AED1-modulo3/miniplayer$ make build/test_musica && ./build/test_musica
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_musica.c src/musica.c -o build/test_musica
test_musica: OK

- Próxima ação:
    M02


## Missão M02 — 13/11
- Integrantes e papéis:
- Objetivo:
- O que implementamos:
- Decisão técnica e justificativa:
- Problema encontrado e solução:
- Evidências de testes:
- Próxima ação:
> Duplicar esta seção a cada missão e alternar os papéis na dupla.
