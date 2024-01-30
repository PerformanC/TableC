# A função tablec_get

A função `tablec_get` é usada para pegar o valor de uma chave usando a chave como parâmetro de pesquisa e retornando o seu valor.

## Uso

```c
//                                         Table    Chave
struct tablec_bucket *bucket = tablec_get(&tablec, "furry");

printf("[TableC]: O valor da chave \"%s\": %d\n", bucket->key, (int)bucket->value);
```

> [!NOTE]
> Essa função irá retornar `NULL` caso a chave não existir.

## Parâmetros

```c
struct tablec_bucket *tablec_get(
  struct tablec_ht *tablec,
  char *            comprementa
);
```

`tablec_get` tem 2 parâmetros, usados para encontrar o valor dela, olhe eles:

*  `Table`       - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para achar o valor relacionada a ela.

## Valor de retorno

1. Se a chave for encontrada, retorna um `struct tablec_bucket *` com os campos `key` e `value`.
2. Se a chave não for encontrada, retorna `NULL`.

## O que ele faz internamente?

1. Faz o hash da chave
2. Verifica o tamanho do array do índice do hash
    - Se for 0, ele irá retornar um bucket vazio
    - Se for 1 ou mais, continue
3. Itera pelo array do índice do hash, verificando pela chave com `strcmp`
    - Se ele encontrar a chave, ele irá retornar o bucket
    - Se ele não encontrar a chave, ele irá retornar um bucket vazio

## Estabilidade

`tablec_get` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
