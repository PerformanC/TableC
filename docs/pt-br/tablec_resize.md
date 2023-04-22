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

`tablec_resize` não retorna nenhum valor, devido a ser uma função com tipo `void`.

## O que ele faz internamente?

`tablec_resize` irá primeiro criar uma nova hashtable com a nova capacidade, e depois irá iterar pela hashtable antiga, e copiar as chaves e valores para a nova hashtable, e depois irá liberar a hashtable antiga, e definir a nova hashtable para a hashtable antiga.

## Estabilidade

`tablec_resize` é estável e pode ser usada em um ambiente de produção sem problemas, mas não é recomendado usá-lo, já que dependendo do tamanho da hashtable, pode levar um tempo para redimensioná-la.

## Veja também

*  [`tablec_init`](tablec_init.md) - Inicializando a hashtable.
