#include <iostream>
#include <stdexcept>

typedef int Dado;

struct Elemento{
    int chave;
    Dado dado;
};

class Noh{
    friend class Lista;
    friend class Hash;
    private:
        Noh *proximo;
        Elemento elemento;
    public:
        Noh(const Elemento &e) : elemento(e), proximo(nullptr) {}
};

class Lista{
    private:
        Noh *inicio;
        int tamanho;
        void apagaLista();
        bool vazia();
    public:
        Lista();
        ~Lista();
        int getTamanho();
        void insereLista(const Elemento &e);
        Dado removeDado(int chave);
        Dado buscaDado(int chave);
        bool verificaOcorrencia(int chave);
        void imprimirLista();
};

Lista::Lista() : inicio(nullptr), tamanho(0){}

Lista::~Lista(){
    apagaLista();
}

bool Lista::vazia(){
    return tamanho == 0;
}

void Lista::apagaLista(){
    Noh* aux{inicio}, *temp{nullptr};
    while(aux != nullptr){
        temp = aux;
        aux = aux->proximo;
        delete temp;
    }
    tamanho = 0;
    inicio = nullptr;
}

int Lista::getTamanho(){
    return tamanho;
}

void Lista::insereLista(const Elemento &e){ // insercao inicio devido evita necessidade do ponteiro fim
    Noh* novo = new Noh(e);
    
    if(!vazia())
        novo->proximo = inicio;
    inicio = novo;

    tamanho++;
}

Dado Lista::removeDado(int chave){

    Noh* aux{inicio}, *anterior{nullptr};
    Dado temp;

    while(aux != nullptr && aux->elemento.chave != chave){
        anterior = aux;
        aux = aux->proximo;
    }

    if(aux == nullptr)
        throw std::runtime_error("Elemento não encontrado na list.");
    
    if(aux == inicio) // remocao inicio, inclusive list com apenas 1 elemento
        inicio = inicio->proximo;
    else if(aux->proximo == nullptr) // remocao fim (necessariamente existe anterior)
        anterior->proximo = nullptr;
    else // remocao meio
        anterior->proximo = aux->proximo;
    
    temp = aux->elemento.dado;
    delete aux;
    tamanho--;

    return temp;

}
Dado Lista::buscaDado(int chave){

    Noh* aux{inicio};

    while(aux != nullptr && aux->elemento.chave != chave)
        aux = aux->proximo;
    
    if(aux == nullptr)
        throw std::runtime_error("Elemento não encontrado na list.");
    
    return aux->elemento.dado;
    
}
bool Lista::verificaOcorrencia(int chave){
    
    Noh* aux{inicio};

    while(aux != nullptr && aux->elemento.chave != chave)
        aux = aux->proximo;
    
    return aux != nullptr;
}

void Lista::imprimirLista(){
    Noh *aux{inicio};
    std::string sep;
    while(aux != nullptr){
        sep = aux->proximo == nullptr ? "" : " -> ";
        std::cout << aux->elemento.chave << sep;
        aux = aux->proximo;
    }
    std::cout << "\n";
}

class Hash{
    private:
        Lista *tabela;
        int capacidade;
        int funcaoHash(int chave);
    public:
        Hash(int capacidade = 7);
        ~Hash();
        void insere(Elemento e);
        Dado remove(int chave);
        Dado busca(int chave);
        void imprimirTabela();
};

Hash::Hash(int capacidade){
    this->capacidade = capacidade;
    tabela = new Lista[capacidade]; 
}


Hash::~Hash(){
    delete[] tabela;
}

int Hash::funcaoHash(int chave){
    return ((chave % capacidade) + capacidade) % capacidade;
}

void Hash::insere(Elemento e){

    Lista* listaPtr = tabela + funcaoHash(e.chave);

    if(listaPtr->verificaOcorrencia(e.chave))
        throw std::runtime_error("Elemento " + std::to_string(e.chave) + " já existente na tabela hash.");

    listaPtr->insereLista(e);
}
Dado Hash::remove(int chave){

    try{
        tabela[funcaoHash(chave)].removeDado(chave);
    }catch(std::runtime_error &e){
        throw std::runtime_error("Elemento " + std::to_string(chave) + " não encontrado na tabela hash.");
    }

}
Dado Hash::busca(int chave){
    try{
        return tabela[funcaoHash(chave)].buscaDado(chave);
    }catch(std::runtime_error &e){
        throw std::runtime_error("Elemento " + std::to_string(chave) + " não encontrado na tabela hash.");
    }
}

void Hash::imprimirTabela(){

    std::cout << "******************\n";

    for(int i{0}; i<capacidade; i++){
        if(tabela[i].getTamanho() > 0)
            tabela[i].imprimirLista();
        else
            std::cout << "*\n";
    }

    std::cout << "******************\n";

}

int main(){

    const int numChaves = 20, numBusca = 3, numRemocao = 5;
    Hash hash(7);
    Elemento elemento;
    int chaves[numChaves] = {4, 223, -2, 24, 31, 123, 147, 19, 19, 0, 3, 17, 7, 2, 237, 298, 172, 78, 55, -28};
    int chavesBusca[numBusca] = {-2, 123, 999};
    int chavesRemocao[numRemocao] = {4, 19, -2, 0, 0};
    bool fim{false}, printLista(true);

    int i{-1}, j{-1}, k{-1};

    while(!fim){
        try{

            while(++i < numChaves){
                elemento.chave = chaves[i];
                elemento.dado = chaves[i];
                hash.insere(elemento);
            }

            if(printLista){
                hash.imprimirTabela();
                printLista = false;
            }
            while(++j < numBusca){
                std::cout << "Buscar " << chavesBusca[j] << ": \n";
                std::cout << hash.busca(chavesBusca[j]) << "\n";
            }
            while(++k < numRemocao){
                std::cout << "Remover " << chavesRemocao[k] << ": \n";
                hash.remove(chavesRemocao[k]);
                hash.imprimirTabela();
            }

            fim = true;

        }catch(std::runtime_error &e){
            std::cout << e.what() << "\n";
        }
    }

    return 0;
}