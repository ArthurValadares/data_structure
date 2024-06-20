# Listas

## Tópicos

* [Listas Encadeadas](../src/list/linked)
* [Deques]()
* [Vetores Expansíveis]()
* [Sequence Set]()

## Definição e Visão Geral

### O que é?

**Listas** são estruturas de dados em que os elementos pertencentes são ligados em uma determinada sequência.

[Pilhas](../src/stack/) e [Filas](../src/queue/) são **tipos especiais de listas**. Enquanto nessas duas o **acesso aos elementos intermediários** é considerado **quebra de estrutura**, em uma lista esse acesso é uma **função básica** da estrutura.

Em relação aos **arrays**, listas possuem como **vantagem** o gerenciamento de memória, visto que **não há alocação de memória desnecessária** e o **redimensionamento é extremamente simples**. Porém, possui como **desvantagem** o **custoso acesso aos elementos intermediários**, visto que os nós são percorridos um a um até atingir o nó especificado.

### Aplicações