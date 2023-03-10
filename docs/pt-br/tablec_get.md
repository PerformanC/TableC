# A função tablec_get

A função `tablec_get` é usada para pegar o valor de uma chave usando a chave como parâmetro de pesquisa e retornando o seu valor.

## Uso

`tablec_get` é uma função fácil de se usar, e a sua sintaxe é fácil de se entender e ler, aqui vai um exemplo de pegar o valor da chave `furry`:

```c
//                      Table    Chave
int value = tablec_get(&tablec, "furry");

printf("[TableC]: O valor da chave \"furry\": %d\n", value);
```

Lembre-se que isso irá apenas retornar o valor da chave se você tiver definido ela antes, se você não tiver definido ela, irá retornar `NULL`. Caso você queira definir ela, veja a documentação da função [`tablec_set`](tablec_set.md) para ver como definir ela.

## Parâmetros

```c
void *tablec_get(
  struct tablec_ht *tablec,
  char *            comprementa
);
```

`tablec_get` tem 3 parâmetros, usados para encontrar o valor dela, olhe eles:

*  `Table`       - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para achar o valor relacionada a ela.

## Valor de retorno

`tablec_get` irá retornar um `void *`, em que o seu tipo será definido pelo tipo do valor colocado na hashtable. se a chave não existir, retornará `NULL`.

## O que ele faz internamente?

`tablec_get` irá fazer muitas coisas internamente, e elas serão explicadas nessa seção, dê uma olhada nelas:

Primeiramente, ele irá ver qual é a capacidade do bucket, e com isso, ele irá definir a melhor forma de tentar procurar, se a capacidade for `1`, ele irá ver apenas um bucket, mas se tiver `1+` capacidade, ele irá fazer um loop `do {} while();` no array de slots para ver se ele consegue achar.

Se ele conseguir achar a chave, ele irá retornar o valor dela, mas se não conseguir, ele irá retornar `NULL`.

## Estabilidade

`tablec_get` é estável, mas a dependência de outras funções pode fazer com que ela não seja estável, mas a função por si só é estável.


## Veja também

*  [`tablec_set`](tablec_set.md) - Setando valores em chaves.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
