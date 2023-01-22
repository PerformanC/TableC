# A função tablec_full

The `tablec_full` function is a basic function to allow you to check if the hashtable is full or not, and not break your code when any change happens to the structures.

## Uso

`tablec_full` usa uma função matemática básica para verificar se a hashtable está cheia ou não, e retornará um valor, que é -1 se estiver cheia, e o número de buckets que não estão cheios se não estiver cheia.

```c
struct tablec_ht tablec;
//           Table
tablec_init(&tablec);
```

## Parâmetros

`tablec_full usa apenas um parâmetros, usado para verificar se a hashtable está cheia ou não, veja-o:

*  `Table`       - `struct tablec_ht` The hashtable variable, is used to save keys and values.

## Valor de retorno

`tablec_full` retorna o valor `-1` se a hashtable estiver cheia, e o número de buckets que não estão cheios se não estiver cheia.

## O que ele faz internamente?

`tablec_full` faz uma conta matemática simples, capacity - length, e retorna o valor.

## Estabilidade

`tablec_full` é estável, já que não há possibilidade de falhas.

## Veja também

*  [`tablec_resize`](tablec_resize.md) - Redimensionando a hashtable.
