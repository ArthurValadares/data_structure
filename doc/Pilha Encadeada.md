# Pilha Encadeada

Confira a implementação de uma [pilha encadeada](../src/stack/linked/pilhaEncadeada.cpp) em C++.

## Detalhes da implementação

Cada elemento da pilha é representado por um **"nó"** , que possui dados e também um ponteiro para o próximo elemento.

A pilha possui um ponteiro para o **topo** (primeiro elemento) e o fim da estrutura é detectado pelo fato do último nó apontar para nulo.

Opcionalmente, pode ser incluído na pilha um **atributo tamanho**, que informa o número de nós presentes na estrutura. Válido ressaltar que esse atributo pode ou não ser utilizado para determinar se a pilha se encontra vazia. Uma alternativa seria verificar se o ponteiro que aponta para o topo da estrutura é nulo ou não.