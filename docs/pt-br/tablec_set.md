# A função tablec_set

`tablec_set` é uma função que salva a chave e o valor na hashtable.

## Uso

```c
//          Table    Chave      Valor
tablec_set(&tablec, "furry", (void *)true);
```

## Parâmetros

```c
NULL tablec_set(
  struct tablec_ht *tablec,
  char *            chave,
  void *            valor
);
```

`tablec_set` é a função com mais parâmetros, tendo 4 parâmetros, olhe eles:

*  `Table`       - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para procurar o valor relacionado a ela.
*  `Valor`       - `void *`           O valor para salvar na chave.

## Valor de retorno

`tablec_set` não retorna nenhum valor, devido a ser uma função de tipo `void`.

## O que ele faz internamente?

1. Faz o hash da chave
2. Verifica o tamanho do array do índice do hash
    - Se for 0, ele irá ignorar e `return;`
    - Se for 1 ou mais, continue
3. Itera pelo array do índice do hash, verificando pela chave com `strcmp`
    - Se ele encontrar um slot vazio, ele irá adicionar a chave nele
    - Se ele não encontrar um slot vazio, ele irá alocar novos slots (capacidade * 2) e copiar as chaves existentes para os novos slots, e então adicionar a chave para o primeiro slot vazio.
4. Salva o valor na chave
5. Incrementa o tamanho da hashtable

## Estabilidade

`tablec_set` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
