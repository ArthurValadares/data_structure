#include <iostream>
#include <cmath>
#include <cstring>
#include <stdexcept>

typedef int Dado;
const int INDEX_NULO = -1;

class PilhaArr{
    private:
        Dado *dadoArr;
        int indexTopo;
        unsigned int capacidadeAtual;
        const unsigned int capacidadeInicial;
        const float fatorRedimensionamento{0.5};
        bool cheia();
        void redimensionaArr();
    public:
        PilhaArr(unsigned int capacidade = 10);
        ~PilhaArr();
        Dado desempilhar();
        void empilhar(const Dado &d);
        void limparTudo();
        Dado espiarTopo();
        bool vazia();
        unsigned int getTamanho();
        unsigned int getCapacidade();
};

PilhaArr::PilhaArr(unsigned int capacidade) : capacidadeInicial(capacidade){
    dadoArr = new Dado[capacidade];
    capacidadeAtual = capacidade;
    indexTopo = INDEX_NULO;
}

PilhaArr::~PilhaArr(){
    delete[] dadoArr;
}

void PilhaArr::limparTudo(){

    indexTopo = INDEX_NULO;

    if(capacidadeAtual != capacidadeInicial){
        delete[] dadoArr;
        dadoArr = new Dado[capacidadeInicial];
        capacidadeAtual = capacidadeInicial;
    }

}

void PilhaArr::redimensionaArr(){
    int novaCapacidade = std::ceil(capacidadeAtual * (1 + fatorRedimensionamento));
    int tamanhoPilha = indexTopo + 1;

    Dado *aux = new Dado[novaCapacidade];
    std::memcpy(aux, dadoArr, sizeof(Dado) * tamanhoPilha);
    delete[] dadoArr;

    capacidadeAtual = novaCapacidade;
    dadoArr = aux;

}

Dado PilhaArr::desempilhar(){
    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");
    
    return dadoArr[indexTopo--];
}

void PilhaArr::empilhar(const Dado &d){
    if(cheia())
        redimensionaArr();
    dadoArr[++indexTopo] = d;
}

Dado PilhaArr::espiarTopo(){
    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");

    return dadoArr[indexTopo];
}

bool PilhaArr::vazia(){
    return indexTopo == INDEX_NULO;
}

bool PilhaArr::cheia(){
    return (indexTopo + 1) == int(capacidadeAtual);
}

unsigned int PilhaArr::getTamanho(){
    return indexTopo + 1;
}

unsigned int PilhaArr::getCapacidade(){
    return capacidadeAtual;
}

int main(){

    PilhaArr pilha;
    Dado d;
    char opcao;

    do{

        try{

            std::cin >> opcao;

            switch(opcao){
                case 'i': // empilhar elemento
                    std::cin >> d;
                    pilha.empilhar(d);
                    break;
                case 'r': // desempilhar elemento
                    d = pilha.desempilhar();
                    std::cout << d << "\n";
                    break;
                case 'l': // limpar tudo
                    pilha.limparTudo();
                    break;
                case 'e':
                    d = pilha.espiarTopo();
                    std::cout << d << "\n";
                    break;
                case 't':
                    std::cout << "tamanho: " << pilha.getTamanho() << "\n";
                    std::cout << "capacidade: " << pilha.getCapacidade() << "\n";
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