# Relatório de testes
| ID | Missão | Função/contrato | Entrada/cenário | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|---|
| T01 | M01 | musica_criar | dados válidos | ponteiro não nulo e campos corretos | preencher | pendente |

| T01 | M01 | musica_criar | dados válidos: 1, "Teste", "Artista", 180 | ponteiro não nulo e campos corretos: t_musica | tests/test_musica.c:7: main: Assertion `m != NULL' failed | pendente |

| T02 | M01 | musica_criar | dados válidos: 1, "Teste", "Artista", 180 | ponteiro não nulo e campos corretos: t_musica | test_musica: OK | concluído |

| T03 | M02 | lse_criar | Não recebe entrada | Ponteiro não nulo | Ponteiro nulo: teste_lista_vazia: Assertion `l != NULL && "lse_criar deve retornar uma lista valida"' failed. | pendente |

| T04 | M02 | lse_criar | Não recebe entrada | Ponteiro não nulo | Ponteiro não nulo: M02: teste de contrato passou. | Concluído |

| T05 | M03 | lse_inserir_inicio | Ponteiro para lista e ponteiro para carga | Inteiro com resultado da operação | Erro no teste: Error 1 | pendente |

| T06 | M03 | lse_inserir_inicio | Ponteiro para lista e ponteiro para carga | Inteiro com resultado da operação | Erro no teste: Error 1 | pendente | obs: falta concluir

| T07 | M04 | algumas funções do lse.c | várias | várias | Erro no teste: Error 1 | pendente |



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


> M02:

make -f missoes/M02/MakeFile.incremental test_m02
cc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude missoes/M02/TESTE_INCREMENTAL_M02.c src/lse.c -o build/m02_incremental
./build/m02_incremental
m02_incremental: missoes/M02/TESTE_INCREMENTAL_M02.c:8: teste_lista_vazia: Assertion `l != NULL && "lse_criar deve retornar uma lista valida"' failed.
make: *** [missoes/M02/MakeFile.incremental:9: test_m02] Aborted (core dumped)

 make -f missoes/M02/MakeFile.incremental test_m02
cc -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude missoes/M02/TESTE_INCREMENTAL_M02.c src/lse.c -o build/m02_incremental
./build/m02_incremental
M02: teste de contrato passou.





