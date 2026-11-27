# MiniPlayer — M07: Histórico e navegação

ICC002 — 27/11/2026 — 100 minutos — Duplas

## Problema e objetivos
Implementar a navegação entre músicas com duas instâncias independentes do TAD Pilha da M06. Praticar composição, encapsulamento, referências compartilhadas, invariantes e testes de integração.

## Interface
Crie `include/player.h` (com guarda de inclusão e `#include "musica.h"`) e `src/player.c`. Não substitua módulos anteriores. Declare:

```c
typedef struct player t_player;
t_player *player_criar(void);
int player_reproduzir(t_player *p, t_musica *m);
int player_anterior(t_player *p);
int player_avancar(t_player *p);
t_musica *player_atual(const t_player *p);
void player_destruir(t_player *p);
```

Em `player.c`, mantenha privada a representação: referência `t_musica *atual` e duas referências `t_pilha *historico`, `t_pilha *avanco`. Use apenas a interface pública de `pilha.h`, sem acessar nós ou listas internas.

## Contratos
- Criar: inicia sem música atual e com duas pilhas vazias. Retorna NULL em falha; libera recursos parcialmente alocados.
- Reproduzir: retorna 1 no sucesso, 0 em erro. Se houver música atual diferente da selecionada, empilhe a atual no histórico, selecione a nova e esvazie o avanço. A primeira reprodução não empilha NULL. Selecionar a mesma referência é sucesso sem alteração (inclusive preserva o avanço).
- Anterior: se o histórico estiver vazio, retorna 0 sem alteração. Caso contrário, transfere a atual para o avanço e recupera o topo do histórico; retorna 1.
- Avançar: operação simétrica, usando o avanço como origem e o histórico como destino.
- Atual: retorna a referência atual, ou NULL quando não houver música ou o controlador for NULL.
- Destruir: libera as duas pilhas e o controlador, nunca as músicas. Aceita NULL.
- Todas as operações que retornam int rejeitam controlador NULL; reproduzir também rejeita música NULL.
- Se empilhar falhar, a navegação deve deixar o estado anterior intacto. Pense na ordem das operações: consulte o topo antes de remover e só efetive a transferência após a inserção bem-sucedida.

A biblioteca (ou o chamador, nos testes) é proprietária das músicas. Não exclua músicas enquanto estiverem referenciadas pelo controlador. A exclusão segura e a fila ficam para missões posteriores. Não armazene NULL nas pilhas de navegação.

## Exemplo de execução
Pilhas representadas da base para o topo:

| Ação | Histórico | Atual | Avanço |
|---|---|---|---|
| Criar | — | — | — |
| Reproduzir A | — | A | — |
| Reproduzir B | A | B | — |
| Reproduzir C | A,B | C | — |
| Anterior | A | B | C |
| Anterior | — | A | C,B |
| Avançar | A | B | C |
| Reproduzir D | A,B | D | — |

## Testes e entrega
Execute `make test_m07` e `make test_missoes` na raiz. Os testes fornecidos cobrem navegação, limites, ramificação, repetição da mesma música, instâncias independentes e referências emprestadas. Acrescente um teste próprio. Analise também falhas de alocação (não simuladas automaticamente pelo kit).

Registre em docs/arquitetura.md, contratos.md, diario-de-bordo.md e relatorio-testes.md as decisões e resultados, sem apagar registros anteriores. Entregue zip com código e documentação. Critérios: testes aprovados, composição sem violar encapsulamento, ausência de liberação indevida de músicas, invariantes preservados e análise de complexidade.

## Reflexão
Por que anterior e avançar custam O(1)? Por que selecionar outra música pode custar O(k), sendo k o tamanho do avanço? Como impedir referências pendentes se a biblioteca excluir uma música? A mesma música pode aparecer em posições diferentes do histórico?
