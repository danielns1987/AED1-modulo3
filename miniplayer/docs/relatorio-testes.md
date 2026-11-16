# Relatório de testes
| ID | Missão | Função/contrato | Entrada/cenário | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|---|
| T01 | M01 | musica_criar | dados válidos | ponteiro não nulo e campos corretos | preencher | pendente |

| T01 | M01 | musica_criar | dados válidos: 1, "Teste", "Artista", 180 | ponteiro não nulo e campos corretos: t_musica | tests/test_musica.c:7: main: Assertion `m != NULL' failed | pendente |

| T02 | M01 | musica_criar | dados válidos: 1, "Teste", "Artista", 180 | ponteiro não nulo e campos corretos: t_musica | test_musica: OK | concluído |


## Casos-limite
- Estrutura vazia:
- Estrutura com um elemento:
- Chave inexistente:
- Falha de alocação (discutir estratégia de simulação):


## Memória
Registrar comandos de compilação, ferramentas utilizadas e problemas corrigidos.

> M01:

make
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude src/main.c src/miniplayer.c -o build/miniplayer

./build/miniplayer
MiniPlayer — projeto progressivo ICC002
M01: implemente musica_criar e musica_destruir.

make build/test_musica
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_musica.c src/musica.c -o build/test_musica

./build/test_musica
test_musica: tests/test_musica.c:7: main: Assertion `m != NULL' failed.

make test
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_lse.c src/lse.c -o build/test_lse
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_pilha.c src/pilha.c src/lse.c -o build/test_pilha
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_fila.c src/fila.c src/lse.c -o build/test_fila
== build/test_musica ==
test_musica: tests/test_musica.c:7: main: Assertion `m != NULL' failed.
Aborted (core dumped)
make: *** [Makefile:20: test] Error 134

make build/test_musica && ./build/test_musica
gcc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude tests/test_musica.c src/musica.c -o build/test_musica
test_musica: OK




