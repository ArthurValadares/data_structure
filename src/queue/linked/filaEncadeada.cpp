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

int main(){

    FilaEncadeada fila;
    Dado d;
    char opcao;

    do{

        try{

            std::cin >> opcao;

            switch(opcao){
                case 'i': // enfileirar elemento
                    std::cin >> d;
                    fila.enfileira(d);
                    break;
                case 'r': // desenfileirar elemento
                    d = fila.desenfileira();
                    std::cout << d << "\n";
                    break;
                case 'l': // limpar tudo
                    fila.limparTudo();
                    break;
                case 'e':
                    d = fila.espiarInicio();
                    std::cout << d << "\n";
                    break;
                case 't':
                    std::cout << "tamanho: " << fila.getTamanho() << "\n";
                    break;
                case 'x':
                    break;
                default:
                    std::cout << "opcao invalida\n";
            }


        }catch(std::runtime_error &err){
            std::cout << err.what() << "\n";
        }

    }while(opcao != 'x');

    return 0;
}