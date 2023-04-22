# A função tablec_set

`tablec_set` é uma função que salva a chave e o valor na hashtable.

## Uso

`tablec_set` é uma função flexível, que permite salvar qualquer tipo de valor nela, com uma limitação, a chave deve ser um `char *`, mas o valor pode ser qualquer coisa, e será salvo como um `void *`, o que significa que você precisará fazer um cast para o tipo que você quer usar.

O exemplo abaixo irá salvar uma chave chamada `furry` com o valor `true`:

```c
//          Table    Chave      Valor
tablec_set(&tablec, "furry", (void *)true);
```

## Parâmetros

```c
NULL tablec_set(
  struct tablec_ht *tablec,
  char *            chave,
  void *            valor
);
```

`tablec_set` é a função com mais parâmetros, tendo 4 parâmetros, olhe eles:

*  `Table`       - `struct tablec_ht` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para procurar o valor relacionado a ela.
*  `Valor`       - `void *`           O valor para salvar na chave.

## Valor de retorno

`tablec_set` não retorna nenhum valor, devido a ser uma função de tipo `void`.

## O que ele faz internamente?

`tablec_set` irá primeiro fazer o hash da chave e depois verificar a capacidade do array do índice do hash, se for 0, ele irá verificar o tamanho do array, se for 1 (cheio), ele irá alocar um novo espaço, copiar a chave existente para a nova alocação e adicionar a chave a ela, se for 0 (vazio), ele irá adicionar a chave ao array, agora, se for 1 ou mais, ele irá iterar pelo array, verificando por slots vazios, se ele encontrar um, ele irá adicionar a chave a ele, se não, ele irá alocar novos slots (capacidade * 2) e copiar as chaves existentes para os novos slots, e então adicionar a chave ao primeiro slot vazio.

## Estabilidade

`tablec_set` é estável e pode ser usada em um ambiente de produção sem problemas.

## Veja também

*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
