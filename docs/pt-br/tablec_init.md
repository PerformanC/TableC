# A função tablec_init

A função `tablec_init` é usada para inicializar a hashtable, e é a função mais importante, que inicializa a hashtable para que ela possa ser usada, aloca os buckets e a hashtable em si, define a capacidade máxima e os slots vazios, e muitas outras coisas importantes.

## Uso

```c
struct tablec_ht tablec;
//          Table     Capacidade
tablec_init(&tablec,   314159);
```

## Parâmetros

`tablec_init` tem 3 parâmetros, usados para inicializar e alocar alguns campos, olhe eles neles:

*  `Table`         - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Capacidade`    - `size_t`           A capacidade máxima da hashtable.

## Valor de retorno

`tablec_init` não retorna nenhum valor, mas na verdade, muda alguns valores da struct da hashtable, isso é porque não tem nada que possa dar errado com ela, apenas se você não tiver mais RAM para alocar.

## O que ele faz internamente?

1. Inicializa os campos
2. Aloca os buckets com `calloc`
3. Inicializa os buckets

## Estabilidade

`tablec_init` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
*  [`tablec_resize`](tablec_resize.md) - Redimensionando a hashtable.