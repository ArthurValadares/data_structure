# Pilha Array

Confira a implementação de uma [pilha utilizando array](../src/stack/array/pilhaArr.cpp) em C++.

## Detalhes da implementação

A implementação de pilhas em arrays possui como vantagem a **maior velocidade nas operações de empilhamento e desempilhamento**.

Porém, essa abordagem também é acompanhada pela **limitação na capacidade da estrutura**, que permanece fixa até que o array seja **redimensionado** (processo computacionalmente caro). Além disso, na grande parte das vezes o **espaço alocado é maior do que o necessário**.

A pilha ainda mantém apenas a referência ao topo da estrutura, que nesse caso se trata do **índice da posição do array que contém o mesmo**. Ao empilhar um elemento, o **topo avança uma posição**, e, na situação oposta, ao desempilhar um elemento, **o topo regride uma posição**.

Na implementação mencionada, a pilha é criada com uma determinada **capacidade inicial** e, sempre que a capacidade máxima é atingida, a estrutura é redimensionada de acordo com um **fator de redimensionamento** definido no algoritmo. Dessa forma, tanto o método responsável por verificar se a pilha está cheia, como o método responsável por redimensioná-la, são declarados como **métodos privados** da mesma. Além disso, ao invocar o método público **"limparTudo"**, todos os elementos da pilha são removidos e a mesma retorna para sua capacidade inicial.