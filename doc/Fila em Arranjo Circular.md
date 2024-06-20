# Fila Array (Circular)

Confira a implementação de uma [fila utilizando arrays](../src/queue/array/filaArr.cpp) em C++.

## Detalhes da implementação

Assim como nas pilhas baseadas em arrays, a implementação de filas em arrays possui como vantagem a **maior velocidade nas operações de empilhamento e desempilhamento**.

De forma similar, essa abordagem também é acompanhada pela **limitação na capacidade da estrutura**, que permanece fixa até que o array seja **redimensionado** (processo computacionalmente caro). Além disso, na grande parte das vezes o **espaço alocado é maior do que o necessário**.

Para que as operações ocorram de maneira adequada, a fila armazena os **indíces do array correspondentes ao início e fim** da estrutura. Ao **enfileirar** um elemento, o **fim avança uma posição**, e, ao **desenfileirar** um elemento, o **início avança uma posição**. 

Um ponto importante a ser observado é que implementações de filas em arrays utilizam do conceito de **filas circulares**. Dessa forma, após sucessivas remoções e inserções, é possível que o indíce de fim se encontre em uma posição anterior ao indíce de início. Isso é obtido da seguinte forma: toda vez que algum dos indíces (início ou fim) avance uma posição, basta **calcular o mod do novo valor**.

Sendo assim, vale ressaltar um adendo em relação ao cálculo do tamanho da fila: é preciso realizar uma verificação da ordem em que esses dois índices se encontram. Dessa forma, em algumas implementações, o custo de manutenibilidade do atributo tamanho se torna justificável.
