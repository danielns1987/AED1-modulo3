# Instalação M07

Na raiz do MiniPlayer, com o ZIP disponível:

```sh
unzip -l MiniPlayer_M07_Incremental.zip
unzip -n MiniPlayer_M07_Incremental.zip -d .
```

Se não houver mudanças, faça backup. Não use unzip -o. Se M07 já existir, confira os arquivos antes de instalar.

O pacote só adiciona `missoes/M07/`. Crie os novos módulos conforme o enunciado; antes disso, o teste não compilará. Com a integração incremental anterior, execute `make test_m07` e `make test_missoes`. Sem integração, use `make -f missoes/M07/Makefile.incremental test_m07`. Para integrar, acrescente uma única vez ao final do Makefile principal (se ainda não estiver presente):

```makefile
-include $(wildcard missoes/M*/Makefile.incremental)
```

Para o alvo agregado, siga o README de Makefiles incrementais já distribuído. Não substitua o Makefile principal.
