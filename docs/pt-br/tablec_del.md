# A função tablec_del

A função `tablec_del` é uma função importante, pois é um dos sistemas usados pelo TableC para acelerar a função `tablec_set`, usando o array de slots vazios como uma de suas principais características.

## Uso

```c
//          Table    Chave
tablec_del(&tablec, "furry");
```

## Parâmetros

```c
NULL tablec_del(
  struct tablec_ht *tablec,
  char *            chave
);
```

`tablec_del` possúi 3 parâmetros, usados para deletar tanto a chave como o valor relacionado à chave, olhe eles:

*  `Table`  - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`    - `char *`         A chave para ser deletada e o valor relacionada à mesma.

## Valor de retorno

`tablec_del` não retorna nenhum valor, devido a ser uma função de tipo `void`.

## O que ele faz internamente?

1. Faz o hash da chave
2. Verifica o tamanho do array do índice do hash
    - Se for 0, ele irá ignorar e `return;`
    - Se for 1 ou mais, continue
3. Itera pelo array do índice do hash, verificando pela chave com `strcmp`
    - Se ele encontrar a chave, ele irá deletar a chave e o valor
    - Se ele não encontrar a chave, ele irá ignorar e `return;`
4. Decrementa o tamanho da hashtable

## Estabilidade

`tablec_del` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
