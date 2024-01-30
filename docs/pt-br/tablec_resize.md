# A função tablec_resize

`tablec_resize` não é uma função importante, mas no entanto, é uma função que redimensiona a hashtable, e é usada por `tablec_set` quando a hashtable está cheia, mas apenas se o `modo seguro` estiver ativado.

## Uso

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

`tablec_resize` é estável e pode ser usada em um ambiente de produção sem problemas.

## O que ele faz internamente?

1. Cria uma nova hashtable com a nova capacidade
2. Itera pela antiga hashtable, copiando as chaves e valores para a nova hashtable
3. Libera a antiga hashtable
4. Define a nova hashtable para a antiga hashtable

## Estabilidade

`tablec_resize` é estável e pode ser usada em um ambiente de produção sem problemas, mas não é recomendado usá-lo, já que dependendo do tamanho da hashtable, pode levar um tempo para redimensioná-la.

## Veja também

*  [`tablec_init`](tablec_init.md) - Inicializando a hashtable.
