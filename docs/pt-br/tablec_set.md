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
  struct hashtable *tablec,
  char *            chave,
  void *            valor
);
```

`tablec_set` é a função com mais parâmetros, tendo 4 parâmetros, olhe eles:

*  `Table`       - `struct hashtable` A variável da hashtable, usada para salvar chaves e valores nela.
*  `Chave`       - `char *`           A chave para procurar o valor relacionado a ela.
*  `Valor`       - `void *`           O valor para salvar na chave.

## Valor de retorno

`tablec_set` não retorna nada, mas caso a hashtable estar cheia, irá avisar no console, ativando o `modo seguro` fará com que o TableC lide isso para você, e irá expandir a hashtable, como você faria manualmente, mas internamente.

## O que ele faz internamente?

`tablec_set` é a função mais complicada de toda o TableC, ela irá fazer muitas coisas internamente, e será explicado resumidamente nessa seção, dê uma olhada nelas:

Primeiramente, ele irá procurar se a primeira chave da hashtable está preenchida, se não estiver, ele irá preencher e irá rapidamente ser feito, se não, ele irá procurar por slots vazios no array de slots vazios, e se ainda não encontrar nenhum slot disponível, o array de buckets será redimensionado, e o novo slot será preenchido com a chave e valor.

## Estabilidade

`tablec_set` não é estável, é por longe a função mais importante, e a maior, tornando difícil prever e corrigir bugs, mas é estável o suficiente para pequenos projetos.

## Veja também

*  [`tablec_get`](tablec_get.md) - Pegando valores baseado em sua chave.
*  [`tablec_del`](tablec_del.md) - Deletando chaves da hashtable.
