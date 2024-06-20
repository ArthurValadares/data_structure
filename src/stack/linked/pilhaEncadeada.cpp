#include <iostream>
#include <stdexcept>

typedef int Dado;

class Noh{
    
    //permite o acesso da stack aos atributos privados do noh
    friend class PilhaEncadeada;

    public:
        Noh(const Dado &d) : dado(d), proximo(nullptr) {}
    
    // noh armazena um dado e um ponteiro para o proximo elemento
    private:
        Dado dado;
        Noh* proximo;
};

class PilhaEncadeada{

    public:
        PilhaEncadeada();
        ~PilhaEncadeada();
        Dado desempilhar();
        void empilhar(const Dado &d);
        Dado espiarTopo();
        bool vazia();
        void limparTudo();
        unsigned int getTamanho();

    // stack armazena ponteiro para o topo e o tamanho da mesma
    private:
        Noh* topo;
        unsigned int tamanho;
};

PilhaEncadeada::PilhaEncadeada(){
    tamanho = 0;
    topo = nullptr;
}

PilhaEncadeada::~PilhaEncadeada(){
    limparTudo();
}

void PilhaEncadeada::limparTudo(){
    
    // apaga todos nós alocados dinamicamente
    while(!vazia())
        desempilhar();
}

void PilhaEncadeada::empilhar(const Dado &d){

    // cria novo nó, que passa a ser o topo da stack

    Noh* novo = new Noh(d);
    novo->proximo = topo;
    topo = novo;
    
    tamanho++;
}

Dado PilhaEncadeada::desempilhar(){

    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");

    // remove o elemento do topo da stack, e o novo topo passa a ser o proximo

    Noh *aux = topo;
    Dado temp = topo->dado;

    topo = topo->proximo;
    delete aux;

    tamanho--;

    return temp;

}

Dado PilhaEncadeada::espiarTopo(){
    if(vazia())
        throw std::runtime_error("Erro: stack vazia!");

    return topo->dado;
}

bool PilhaEncadeada::vazia(){
    return !bool(topo);
}

unsigned int PilhaEncadeada::getTamanho(){
    return tamanho;
}

int main(){

    PilhaEncadeada pilha;
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