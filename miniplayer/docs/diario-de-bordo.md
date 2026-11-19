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
    Daniel Nunes Santos: documentação
    José Eduardo Araujo Costa Melo: implementação

- Objetivo:
    Implementar lse_criar (lista vazia), lse_tamanho, lse_primeiro, lse_destruir (para lista vazia).

- O que implementamos:
    Todas as funções do objetivo, sendo que lse_destruir foi uma implementação apenas parcial e inicial, considerando que estamos ainda listando com listas vazias.

- Decisão técnica e justificativa:

- Problema encontrado e solução:

- Evidências de testes:
    Saída do terminal:
   daniel@LAPTOP-HALO0GS1:/mnt/c/Users/dream/OneDrive/Área de Trabalho/AED1-modulo3/miniplayer$ make -f missoes/M02/MakeFile.incremental test_m02
cc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude missoes/M02/TESTE_INCREMENTAL_M02.c src/lse.c -o build/m02_incremental
./build/m02_incremental
M02: teste de contrato passou.

- Próxima ação:
    M03

## Missão M03 — 16/11



## Missão M04 — 18/11

