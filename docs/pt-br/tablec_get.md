# A função tablec_get

A função `tablec_get` é usada para pegar o valor de uma chave usando a chave como parâmetro de pesquisa e retornando o seu valor.

## Uso

`tablec_get` é uma função fácil de se usar, e a sua sintaxe é fácil de se entender e ler, aqui vai um exemplo de pegar o valor da chave `furry`:

```c
//                                        Table    Chave
struct tablec_bucket bucket = tablec_get(&tablec, "furry");

printf("[TableC]: O valor da chave \"%s\": %d\n", bucket.key, (int)bucket.value);
```

Lembre-se que isso irá apenas retornar o valor da chave se você tiver definido ela antes, se você não tiver definido ela, irá retornar `NULL`. Caso você queira definir ela, veja a documentação da função [`tablec_set`](tablec_set.md) para ver como definir ela.

## Parâmetros

```c
struct tablec_bucket tablec_get(
  struct tablec_ht *tablec,
  char *            comprementa
);
```

`tablec_get` tem 3 parâmetros, usados para encontrar o valor dela, olhe eles:

*  `Table`       - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para achar o valor relacionada a ela.

## Valor de retorno

`tablec_get` irá retornar `struct tablec_bucket`, em que o tipo é o mesmo que o valor da chave, e se a chave não existir, irá retornar `NULL`.

## O que ele faz internamente?

`tablec_get` irá primeiro fazer o hash da chave, e depois verificar o tamanho do array que a chave está, caso o tamanho seja 0, ele irá retornar um bucket vazio, caso o tamanho seja 1 ou mais, ele irá iterar pelo array, `strcmp`ando as chaves, e se ele encontrar a chave, ele irá retornar o bucket, e se ele não encontrar a chave, ele irá retornar um bucket vazio.

## Estabilidade

`tablec_get` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
