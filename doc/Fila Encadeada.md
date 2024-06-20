# Fila Encadeada

Confira a implementação de uma [fila encadeada](../src/queue/linked/filaEncadeada.cpp) em C++.

## Detalhes da implementação

Cada elemento da fila é representado por um **"nó"** , que possui dados e também um ponteiro para o próximo elemento.

A fila possui um ponteiro para o **inicio** (primeiro elemento) e para o **fim** (último elemento). Dessa forma, a estrutura tem acesso direto às duas extremidades onde são feitas as operações, sem a necessidade de percorrer, um a um, todos os elementos.

Opcionalmente, pode ser incluído na fila um **atributo tamanho**, que informa o número de nós presentes na estrutura. Válido ressaltar que esse atributo pode ou não ser utilizado para determinar se a fila se encontra vazia. Uma alternativa seria verificar se o ponteiro que aponta para o início da estrutura é nulo ou não.