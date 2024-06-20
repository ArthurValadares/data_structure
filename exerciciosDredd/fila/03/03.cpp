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

void leituraFila(int tam, FilaEncadeada &fila){

    int n;

    for(int i{0}; i<tam; i++){
        std::cin >> n;
        fila.enfileira(n);
    }    

}

void ordenaMonte(FilaEncadeada &filaA, FilaEncadeada &filaB, FilaEncadeada &filaC){

    int numA, numB, ultimoEnfifeirado;
    FilaEncadeada *filaMenor;

    while(!filaA.vazia() && !filaB.vazia()){ 
        
        filaMenor = (filaA.espiarInicio() <= filaB.espiarInicio()) ? &filaA : &filaB;

        if(!filaC.getTamanho() || filaMenor->espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaMenor->desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaMenor->desenfileira();
    }

    while(!filaA.vazia()){ 
        
        if(!filaC.getTamanho() || filaA.espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaA.desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaA.desenfileira();
    }

    while(!filaB.vazia()){ 
        
        if(!filaC.getTamanho() || filaB.espiarInicio() != ultimoEnfifeirado){
            ultimoEnfifeirado = filaB.desenfileira();
            filaC.enfileira(ultimoEnfifeirado);
        }else
            filaB.desenfileira();
    }

}

int main(){

    FilaEncadeada filaA, filaB, filaC;
    int tam;

    std::cin >> tam;
    leituraFila(tam, filaA);

    std::cin >> tam;
    leituraFila(tam, filaB);

    ordenaMonte(filaA, filaB, filaC);

    while(!filaC.vazia())
        std::cout << filaC.desenfileira() << " "; 


    return 0;
}