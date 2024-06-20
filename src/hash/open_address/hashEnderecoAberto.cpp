#include <iostream>
#include <stdexcept>

typedef int Dado;

struct Elemento{
    int chave;
    Dado dado;
};

const Elemento INVALIDO = {-1, -1};
const Elemento REMOVIDO = {-2, -2};

const int POS_INVALIDA = -1;

bool operator==(const Elemento &elementoA, const Elemento &elementoB){
    return elementoA.chave == elementoB.chave;
}

bool operator!=(const Elemento &elementoA, const Elemento &elementoB){
    return elementoA.chave != elementoB.chave;
}

class HashEA{
    private:
        Elemento *tabela;
        int capacidade, tamanho;
        int funcaoHash(int chave);
        int buscarPos(int chave);
    public:
        HashEA(int capacidade = 19);
        ~HashEA();
        void inserir(const Elemento &e);
        Dado remover(int chave);
        Dado buscar(int chave);
        void imprimir();
};

HashEA::HashEA(int capacidade){
    this->capacidade = capacidade;
    tamanho = 0;
    tabela = new Elemento[capacidade];

    for(int i{0}; i<capacidade; i++)
        tabela[i] = INVALIDO;
}

HashEA::~HashEA(){
    delete[] tabela;
}

int HashEA::funcaoHash(int chave){
    return chave % capacidade;
}

int HashEA::buscarPos(int chave){

    int posFinal = funcaoHash(chave);
    int pos = posFinal;

    do{

        if(tabela[pos].chave == chave)
            return pos;
        if(tabela[pos] == INVALIDO)
            return POS_INVALIDA;

        pos = (pos + 1) % capacidade;

    }while(pos != posFinal);
      
    return POS_INVALIDA;
}

Dado HashEA::buscar(int chave){

    int posFinal = funcaoHash(chave);
    int pos = posFinal;

    do{

        if(tabela[pos].chave == chave)
            return tabela[pos].dado;
        if(tabela[pos] == INVALIDO)
            throw std::runtime_error("Chave " + std::to_string(chave) + " inexistente.");

        pos = (pos + 1) % capacidade;

    }while(pos != posFinal);
      
    throw std::runtime_error("Chave " + std::to_string(chave) + " inexistente.");

}

void HashEA::inserir(const Elemento &e){
    
    if(tamanho == capacidade)
        throw std::runtime_error("Tabela Hash cheia.");
    
    if(e.chave < 0)
        throw std::runtime_error("Valor de chave invalida para insercao.");
    
    if(buscarPos(e.chave) != POS_INVALIDA)
        throw std::runtime_error("Chave " + std::to_string(e.chave) + " já existente.");
    
    int pos = funcaoHash(e.chave);

    while(tabela[pos] != INVALIDO && tabela[pos] != REMOVIDO)
        pos = (pos + 1) % capacidade;
    
    tabela[pos] = e;
    tamanho++;

}
Dado HashEA::remover(int chave){

    if(tamanho == 0)
        throw std::runtime_error("Tabela Hash vazia.");

    int pos = buscarPos(chave); 

    if(pos == POS_INVALIDA)
        throw std::runtime_error("Chave " + std::to_string(chave) + " inexistente.");
    
    tabela[pos] = REMOVIDO;
    tamanho--;

}

void HashEA::imprimir(){
    for(int i{0}; i<capacidade; i++)
        std::cout << tabela[i].chave << (i == capacidade - 1 ? "" : " - "); 
    std::cout << "\n";
}


int main(){

    HashEA hash(9);
    char op;
    Elemento elemento;
    int chave;

    do {
        try {
            std::cin >> op;

            switch (op) {
                case 'i': // inserir
                    std::cin >> elemento.chave;
                    elemento.dado = elemento.chave;
                    hash.inserir(elemento);
                    break;
                case 'r': // remover
                    std::cin >> elemento.chave;
                    hash.remover(elemento.chave);
                    break;
                case 'l': // consultar
                    std::cin >> elemento.chave;
                    elemento.dado = hash.buscar(elemento.chave);
                    std::cout << elemento.dado << "\n";
                    break;
                case 'p':
                    hash.imprimir();
                    break;
                case 'f':
                    break;
                default:
                    std::cout << "operacao invalida.\n";
            }

        }
        catch (std::runtime_error &e) {
            std::cout << e.what() << "\n";
        }
    } while (op != 'f');

    return 0;
}