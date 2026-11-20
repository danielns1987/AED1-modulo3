# MiniPlayer — Guia de integração dos Makefiles incrementais

**ICC002 — Algoritmos e Estruturas de Dados I**  
**Objetivo:** executar os testes das missões M02, M03, M04 e das próximas missões pelo `Makefile` principal, sem substituir o código já desenvolvido.

## 1. Como o projeto deve estar organizado

```text
miniplayer/
├── Makefile                 # já existente: preservar
├── include/
│   └── lse.h
├── src/
│   └── lse.c
├── build/                   # arquivos gerados pela compilação
└── missoes/
    ├── M02/
    │   ├── Makefile.incremental
    │   └── TESTE_INCREMENTAL_M02.c
    ├── M03/
    │   ├── Makefile.incremental
    │   └── test_m03.c
    └── M04/
        ├── Makefile.incremental
        └── test_m04.c
```

Cada missão acrescenta seu próprio diretório. **Não substitua `src/lse.c`, `include/lse.h` nem o `Makefile` principal** ao instalar um novo kit.

## 2. Antes de alterar: salve o trabalho


Faça uma cópia de segurança da pasta antes de editar o `Makefile`.

## 3. Integração no Makefile principal (uma única vez)

Abra o `Makefile` que já existe na raiz do MiniPlayer e **acrescente ao final**, sem apagar as regras atuais:

```makefile
# -----------------------------------------------------------
# MiniPlayer: testes incrementais das missões
# -----------------------------------------------------------

# Descobre automaticamente as missões instaladas.
ARQUIVOS_MISSOES := $(wildcard missoes/M*/Makefile.incremental)

# Define os nomes dos testes, inclusive o da M02.
TESTES_MISSOES := $(patsubst missoes/M%/Makefile.incremental,test_m%,$(ARQUIVOS_MISSOES))

# Incorpora as regras de cada missão, sem alterar seus arquivos.
-include $(ARQUIVOS_MISSOES)

.PHONY: test_missoes

# Executa todos os testes das missões instaladas.
test_missoes: $(TESTES_MISSOES)
```

**Por que funciona?** `wildcard` localiza os arquivos incrementais presentes; `-include` carrega suas regras; `test_missoes` depende dos testes correspondentes. Quando a M05 for instalada, seu arquivo será detectado automaticamente, desde que mantenha a convenção de nomes.

**Atenção:** o Makefile da M02, conforme o kit distribuído, não acrescenta seu teste à variável `TESTES_MISSOES`; por isso o trecho acima calcula os nomes a partir dos diretórios. Os Makefiles da M03 e M04 também acrescentam seus testes à variável; a repetição de dependências não implica executar o mesmo alvo duas vezes em uma única chamada do Make.

### Caso o Makefile principal já tenha integração incremental

Se já existir uma linha como:

```makefile
-include $(wildcard missoes/M*/Makefile.incremental)
```

**Não adicione um segundo `include`.** Substitua apenas essa linha pelo bloco completo acima, mantendo o restante do arquivo. Se já existir uma regra `test_missoes`, adapte-a em vez de criar outra com o mesmo nome.

## 4. Comandos para os estudantes

Execute sempre **na raiz do projeto**:

```sh
make test_m02        # testes da M02
make test_m03        # testes da M03
make test_m04        # testes da M04
make test_missoes    # testes de todas as missões instaladas
```

Para conferir as regras sem executar os comandos de compilação:

```sh
make -n test_m04
```

Para verificar os arquivos que o Make está incluindo:

```sh
find missoes -name Makefile.incremental -print
```

### Alternativa: sem editar o Makefile principal

Também é possível executar cada arquivo isoladamente:

```sh
make -f missoes/M02/Makefile.incremental test_m02
make -f missoes/M03/Makefile.incremental test_m03
make -f missoes/M04/Makefile.incremental test_m04
```

Essa alternativa é útil quando ainda não foi feita a integração.

## 5. Instalação segura de novas missões

1. Faça um commit ou backup antes de instalar.
2. Inspecione o conteúdo do ZIP: `unzip -l MiniPlayer_M02_Incremental.zip`.
3. Extraia na raiz do projeto sem sobrescrever arquivos existentes:

   ```sh
   unzip -n MiniPlayer_M02_Incremental.zip -d .
   ```
4. copie a pasta `MiniPlayer_M02_Incremental/missoes` para a pasta `missoes`
    ```sh
    cp -r MiniPlayer_M02_Incremental/missoes/* missoes/
    ```
5. Execute `make test_m02` e `make test_missoes`.

**Importante:** `unzip -n` evita sobrescrita, mas pode manter versões antigas caso o diretório da missão já exista. Se houver conflito, compare os arquivos e resolva manualmente; não use `unzip -o` indiscriminadamente.

## 6. Erros comuns e como diagnosticar

| Sintoma | Causa provável | Ação |
|---|---|---|
| `No rule to make target 'test_m04'` | Arquivo incremental não instalado ou não incluído | Confira o caminho e o bloco `-include` |
| `No rule to make target 'src/lse.c'` | Comando executado fora da raiz do projeto | Entre na pasta `miniplayer/` |
| `undefined reference to ...` | Função ainda não implementada ou nome/assinatura divergente | Confira `lse.h`, `lse.c` e o contrato da missão |
| `assertion ... failed` | Teste compilou, mas detectou comportamento incorreto | Depure a implementação; não altere o teste para mascarar o erro |
| `missing separator` | Comando de receita indentado com espaços | Use TAB no início das linhas de comando do Makefile |
| `overriding recipe for target` | Dois Makefiles definem o mesmo alvo | Mantenha nomes únicos (`test_m03`, `test_m04` etc.) |

## 7. Recomendações importantes

- O `Makefile` principal continua responsável pelo programa MiniPlayer; os arquivos incrementais acrescentam **alvos de teste**, não novas implementações.
- Os testes usam o **mesmo `src/lse.c`** que os estudantes desenvolveram nas missões anteriores.
- `make test_missoes` pode parar no primeiro teste que falhar. Para executar os demais individualmente, use `make test_m02`, `make test_m03` e `make test_m04`.
- Os testes de M03 e M04 podem falhar antes de todas as funções previstas terem sido implementadas. Isso faz parte do desenvolvimento incremental.
- O Makefile da M02 usa `CC` e `CFLAGS`; os da M03/M04 definem suas próprias opções de compilação. Isso não impede a inclusão, mas vale padronizar nas próximas missões.
- Os arquivos de missão devem permanecer no repositório para permitir testes de regressão.

## 8. Verificação final

Após integrar o bloco, execute:

```sh
make -n test_missoes   # mostra os comandos planejados
make test_missoes      # compila e executa os testes
```

**Critério de sucesso:** os alvos das missões instaladas são reconhecidos e executam os testes sobre o código atual, sem substituir arquivos de implementação nem documentação.
