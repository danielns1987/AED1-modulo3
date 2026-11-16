# Contratos dos TADs
Para **cada função**, preencher:
- Nome e assinatura:
- Pré-condições:
- Pós-condições:
- Valor de retorno em sucesso/falha:
- Quem aloca/libera a memória:
- Invariantes preservadas:
- Testes associados:

> musica_criar
- Nome e assinatura:
    t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao)

- Pré-condições:
    Dados válidos na chamada

- Pós-condições:
    Retorno de ponteiro não nulo e variáveis corretamente atribuídas

- Valor de retorno em sucesso/falha:
    Sucesso: ponteiro não nulo
    Falha: ponteiro nulo

- Quem aloca/libera a memória:
    Chamada da função malloc(sizeof(t_musica)) aloca memória

- Invariantes preservadas:

- Testes associados:
    test_musica


> musica_destruir
- Nome e assinatura:
    void musica_destruir(void *carga)

- Pré-condições:
    Dados válidos na chamada

- Pós-condições:
    Memória da carga liberada

- Valor de retorno em sucesso/falha:
    void

- Quem aloca/libera a memória:
    Função free(carga) libera memória

- Invariantes preservadas:

- Testes associados:
    test_musica
    

## Invariantes da LSE
- `tamanho >= 0`.
- `tamanho == 0` se e somente se `inicio == NULL`.
- Há exatamente `tamanho` nós alcançáveis a partir de `inicio`.
- O último nó aponta para `NULL` e não há ciclos.
