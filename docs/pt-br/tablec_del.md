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
  struct hashtable *tablec,
  char *            chave
);
```

`tablec_del` possúi 3 parâmetros, usados para deletar tanto a chave como o valor relacionado à chave, olhe eles:

*  `Table`  - `struct hashtable` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`    - `char *`         A chave para ser deletada e o valor relacionada à mesma.

## Valor de retorno

`tablec_del` não retorna nada, nem sucesso ou falha, ele irá apenas deletar a chave e o valor relacionado à mesma, e se ele não encontrar uma chave relacionada, ele irá ignorar, já que isso é algo que você deveria fazer, e isso é uma API de baixo nível.

## O que ele faz internamente?

`tablec_del` é uma função difícil de explicar o seu funcionamento, por isso, o mesmo será explicado de forma resumida:

Primeiramente, ele irá ver qual é a capacidade do bucket, e com isso, ele irá definir se ele deve usar o `do {} while();` loop ou não, já que pode ser necessário para procurar por slots, e depois de encontrar o slot, ele irá adicionar à lista de slots vazios o slot que ele encontrou, e ele irá definir a chave e o valor para `NULL`.

## Estabilidade

`tablec_del` não é uma função estável, por ser complexa e ter muitos if statements, o que dificulta a depuração, mas mesmo assim, é seguro de se usar.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
