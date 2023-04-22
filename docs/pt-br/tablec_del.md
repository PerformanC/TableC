# A função tablec_del

A função `tablec_del` é uma função importante, pois é um dos sistemas usados pelo TableC para acelerar a função `tablec_set`, usando o array de slots vazios como uma de suas principais características.

## Uso

`tablec_del` é uma das funções mais fáceis de se usar, já que o seu uso necessita de poucos parâmetros, e é fácil de se entender, aqui vai um exemplo de deletando a chave `furry`:

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

`tablec_del` vai primeiro fazer o hash da chave, e depois verificar o tamanho do array que a chave está, caso o tamanho seja 0, ele irá ignorar e `return;`, caso o tamanho seja 1 ou mais, ele irá iterar pelo array, `strcmp`ando as chaves, e se ele encontrar a chave, ele irá deletar a mesma, e se ele não encontrar a chave, ele irá ignorar e `return;`.

## Estabilidade

`tablec_del` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
