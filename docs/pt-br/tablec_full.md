# A função tablec_full

A função `tablec_full` permite verificar quantos buckets não estão cheios, e se a hashtable está cheia ou não. Isso permite fazer redimensionamentos otimizados, redimensionando antes da hashtable estar cheia.

## Uso

```c
struct tablec_ht tablec;
//           Table
tablec_init(&tablec);
```

## Parâmetros

```c
int tablec_full(
  struct tablec_ht *tablec
);
```

`tablec_full usa apenas um parâmetros, usado para verificar se a hashtable está cheia ou não, veja-o:

*  `Table`       - `struct tablec_ht` The hashtable variable, is used to save keys and values.

## Valor de retorno

`tablec_full` retorna o valor `-1` se a hashtable estiver cheia, e o número de buckets que não estão cheios se não estiver cheia.

## O que ele faz internamente?

1. Verifica se a hashtable está cheia
    - Se estiver, irá retornar `-1`
    - Se não estiver, irá calcular `capacity - length` e retornar o valor

## Estabilidade

`tablec_full` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_resize`](tablec_resize.md) - Redimensionando a hashtable.
