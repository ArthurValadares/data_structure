#include <iostream>
#include <stdexcept>

typedef int Dado;
const int INDEX_NULO{-1};

class FilaArr{
    private:
        int indexInicio, indexFim;
        unsigned int tamanho;
        const unsigned int capacidade;
        Dado *dadoArr;
    public:
        FilaArr(int capacidade = 10);
        ~FilaArr();
        void enfileira(const Dado &d);
        Dado desenfileira();
        Dado espiarInicio();
        void limparTudo();
        unsigned int getTamanho();
        bool vazia();
        bool cheia();

};

FilaArr::FilaArr(int capacidade) : capacidade(capacidade) {
    indexInicio = indexFim = INDEX_NULO;
    dadoArr = new Dado[capacidade];
    tamanho = 0;
}

FilaArr::~FilaArr(){
    delete[] dadoArr;    
}

void FilaArr::enfileira(const Dado &d){

    if(cheia())
        throw std::runtime_error("Erro: queue cheia!");
    
    if(vazia())
        indexInicio = 0;
    indexFim = (indexFim + 1) % capacidade;

    dadoArr[indexFim] = d;

    tamanho++;

}

Dado FilaArr::desenfileira(){
    if(vazia())
        throw std::runtime_error("Erro: queue vazia!");

    Dado temp = dadoArr[indexInicio];
    tamanho--;

    if(vazia())
        indexInicio = indexFim = INDEX_NULO;
    else
        indexInicio = (indexInicio + 1) % capacidade;

    return temp;
    
}

Dado FilaArr::espiarInicio(){
    if(vazia())
        throw std::runtime_error("Erro: queue vazia!");

    return dadoArr[indexInicio];
    
}

void FilaArr::limparTudo(){
    indexInicio = indexFim = INDEX_NULO;
    tamanho = 0;
}

unsigned int FilaArr::getTamanho(){
    return tamanho;
}

bool FilaArr::vazia(){
    return !bool(tamanho);
}

bool FilaArr::cheia(){
    return (tamanho == capacidade);
}

int main(){

    FilaArr fila;
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