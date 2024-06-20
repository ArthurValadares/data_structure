#include <iostream>
#include <stdexcept>

typedef int Dado;

class Noh{

    //permitir acesso da queue aos atributos privados do Noh
    friend class FilaEncadeada;

    // noh armazena dado e ponteiro para o próximo
    private:
        Noh* proximo;
        Dado dado;
    public:
        Noh(const Dado &d) : dado(d), proximo(nullptr) {}
};

class FilaEncadeada{
    private:
        Noh *inicio, *fim;
        unsigned int tamanho;
    public:
        FilaEncadeada();
        ~FilaEncadeada();
        void enfileira(const Dado &d);
        Dado desenfileira();
        void limparTudo();
        unsigned int getTamanho();
        bool vazia();
        Dado espiarInicio();
        void removeIntersecao(FilaEncadeada &filaB);
};

FilaEncadeada::FilaEncadeada(){
    inicio = fim = nullptr;
    tamanho = 0;
}

FilaEncadeada::~FilaEncadeada(){
    limparTudo();
}

void FilaEncadeada::limparTudo(){
    while(!vazia())
        desenfileira();
}

void FilaEncadeada::enfileira(const Dado &d){

    Noh *novo = new Noh(d);

    if(vazia())
        inicio = novo;
    else
        fim->proximo = novo; // proximo do antigo fim é novo
    
    fim = novo; // fim passa a ser o novo elemento

    tamanho++;

}

Dado FilaEncadeada::desenfileira(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    Noh *aux = inicio;
    Dado temp = inicio->dado;

    inicio = inicio->proximo;
    delete aux;
    tamanho--;

    if(vazia())
        fim = nullptr;

    return temp;

}

unsigned int FilaEncadeada::getTamanho(){
    return tamanho;
}

bool FilaEncadeada::vazia(){
    return !bool(inicio);
}

Dado FilaEncadeada::espiarInicio(){

    if(vazia())
        throw std::runtime_error("Erro: Fila Vazia!");

    return inicio->dado;
}

void FilaEncadeada::removeIntersecao(FilaEncadeada &filaB){

    int tamA{getTamanho()}, tamB{filaB.getTamanho()};
    int j;
    Dado auxA, auxB;
    bool naoEncontrou;

    for(int i{0}; i<tamA; i++){

        j = 0;
        auxA = desenfileira();
        naoEncontrou = true;

        while(j < tamB && naoEncontrou){

            auxB = filaB.desenfileira();

            if(auxB == auxA)
                naoEncontrou = false;

            filaB.enfileira(auxB);
            j++;
        }

        if(naoEncontrou)
            enfileira(auxA);

    }

}

void leituraFila(int tam, FilaEncadeada &fila){

    int num;

    for(int i{0}; i<tam; i++){
        std::cin >> num;
        fila.enfileira(num);
    }

}

int main(){

    FilaEncadeada filaA, filaB;

    int n;

    std::cin >> n;
    leituraFila(n, filaA);

    std::cin >> n;
    leituraFila(n, filaB);

    filaA.removeIntersecao(filaB);
    int novoTam{filaA.getTamanho()};

    for(int i{0}; i<novoTam; i++)
        std::cout << filaA.desenfileira() << " ";

    return 0;
}