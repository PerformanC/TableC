# A função tablec_resize

`tablec_resize` não é uma função importante, mas no entanto, é uma função que redimensiona a hashtable, e é usada por `tablec_set` quando a hashtable está cheia, mas apenas se o `modo seguro` estiver ativado.

## Uso

`tablec_resize` é simples de usar, mas se você redimensionar a hashtable com um valor menor que a capacidade atual, acabará em um crash, então tenha cuidado com isso.

```c
//             Table   Capacidade 
tablec_resize(&tablec,    128);
```

## Parameters

```c
NULL tablec_resize(
  struct tablec_ht *tablec,
  size_t            novaCapacidade
);
```

`tablec_resize` tem apenas 2 parâmetros, usados para redimensionar a hashtable, olhe eles:

*  `Table`      - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Capacidade` - `size_t`           A nova capacidade da hashtable.

## Valor de retorno

`tablec_resize` vai atualizar a hashtable com a nova, você só precisa ter certeza de que tem RAM suficiente para isso e substituir a atual com a nova, todas as chaves serão rehashadas e a tabela será liberada automaticamente.

## O que ele faz internamente?

`tablec_resize` irá simplesmente `realloc` a hashtable para a nova capacidade, e também irá definir a nova capacidade para a hashtable.

## Estabilidade

`tablec_resize` é considerado instável, e seu uso não é recomendado.

## Veja também

*  [`tablec_init`](tablec_init.md) - Inicializando a hashtable.
