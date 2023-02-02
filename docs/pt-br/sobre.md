# Sobre o TableC

TableC é uma implementação de hashtables em C, fornecendo uma API fácil, com uma implementação simples e rápida. É uma biblioteca de cabeçalho único, então você pode apenas incluir o arquivo de cabeçalho e usá-lo. Ele também usa o método de endereçamento fechado para lidar com colisões.

## Por que o endereçamento fechado?

O método de endereçamento fechado tem algumas vantagens sobre o método de endereçamento aberto, que acabou fazendo eu decidir usálo em vez do método de endereçamento aberto, o mais popular e mais usado.

Uma delas é que o método de endereçamento fechado usa menos `strcmp`s que não valem a pena, porque o índice de uma chave pode estar perto dessa chave, fazendo com que ele faça `strcmp`s em uma chave que nem está perto da chave que você está procurando.

Outra é que o endereçamento fechado é um método que acabaria sendo um melhor design, porque é mais fácil de implementar, e é mais fácil de entender (para **mim**).

## Sistemas usado pelo TableC

O TableC é inteligente, e ele usa muitos recursos e códigos para melhorar o seu desempenho, alguns deles são:

*  Usa um array de slots vazios para listar slots que estão vazios para que eles possam ser acessados e reutilizados rapidamente.
*  Salva o comprimento e a capacidade do array de slots vazios do hashtable, para que ele possa ser lido, escrito e excluído rapidamente.

Esses recursos parecem sistemas pequenos, mas eu trabalho duro neles para que eles possam funcionar rapidamente e eficientemente.

## Quão estável é o TableC?

O TableC NÃO é estável, já que não foi testado o suficiente, mas alguns testes (feitos por mim, especialmente para o TableC) estão passando, e estou trabalhando nele para torná-lo estável.

As seguintes funções são duramente testadas, usando Fuzzy testinge com casos especiais para ver como ele as trata:

*  `tablec_get`
*  `tablec_set`
*  `tablec_del`

## Por que não há uma função de contains?

O TableC foi feito para alta portabilidade, mas também desempenho e essas funções não são necessárias, já que você pode usar `tablec_get` para verificar se uma chave existe, e se ele retornar `NULL`, então ela não existe, removendo a necessidade de usar 2 funções que procuram através do hashtable para recuperar o valor.

## O TableC não possúi algumas funções

O TableC não possui algumas funções porque eu estou focando nas funções principais, como `tablec_get`, que eu trabalho duramente para melhorar ela, e adicionar mais funções não significa uma biblioteca melhor, se elas não forem bem feitas, e eu estou trabalhando nisso para torná-lo melhor.

## O TableC não é estável, por que eu deveria usálo?

Isso é o ponto, você não deveria usálo por enquanto, até que mais testes sejam feitos, mas quando os testes forem feitos, você poderá usálo, e ele será estável, e você poderá usálo em seus projetos, permitindo usar uma poderosa biblioteca de hashtables, com uma API simples, e uma implementação rápida.

## Como usar o TableC

Na pasta docs, haverá um conjunto de docs sobre como usar cada uma de suas funções, você pode vêlas, e usálas em seus projetos. E também a pasta tests, haverá um conjunto de testes usados para testar o TableC, e você pode usar algum deste código em seus projetos.

## Como pronunciar TableC

Seção engraçado, o TableC não é pronunciado igual você pensa, em português, você pode pronunciar TableC com "Tei bôs", sim, você conta o `C` como um `s`, já que isso representa que o TableC é feito com a linguagem de programação C, e também quer não é uma table apenas, são várias, por isso ele se chama TableC.