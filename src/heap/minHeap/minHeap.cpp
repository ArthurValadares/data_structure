#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstring>

typedef int Dado;

class MinHeap{

    private:
        Dado* heap;
        const unsigned int capacidade;
        unsigned int tamanho;
        int pai(int i);
        int filhoEsquerdo(int i);
        int filhoDireito(int i);
        void arruma();
        void corrigeSubindo(int i);
        void corrigeDescendo(int i);
        bool vazia();
        bool cheia();
    public:
        MinHeap(int capacidade = 10); // construtor cria heap vazia
        MinHeap(Dado *arr, int tamanhoArr); // construtor cria heap a partir de array já preenchido
        ~MinHeap();
        Dado espiaRaiz();
        Dado removeRaiz();
        void insere(const Dado &d);
        void imprime(); //fins didáticos (configura quebra de estrutura)
        unsigned int getTamanho();
        unsigned int getCapacidade();
};

MinHeap::MinHeap(int capacidade) : capacidade(capacidade){

    heap = new Dado[capacidade];
    tamanho = 0;
}

MinHeap::MinHeap(Dado *arr, int tamanhoArr) : capacidade(tamanhoArr){

    tamanho = tamanhoArr;
    heap = new Dado[tamanhoArr];
    std::memcpy(heap, arr, sizeof(Dado) * tamanhoArr);
    arruma();
}

MinHeap::~MinHeap(){
    delete[] heap;
}

void MinHeap::arruma(){
    for(int i{int(tamanho/2 - 1)}; i>=0; i--) // metade para cima (apenas nós não-folhas) até a raiz
        corrigeDescendo(i);
}

int MinHeap::pai(int i){
    return (i - 1)/2;
}

int MinHeap::filhoEsquerdo(int i){
    return i*2 + 1;
}

int MinHeap::filhoDireito(int i){
    return i*2 + 2;
}

void MinHeap::corrigeDescendo(int i){

    int esquerdo{filhoEsquerdo(i)}, direito{filhoDireito(i)};
    int indexMenor = i;

    // verifica se algum dos filhos é menor que o pai e pega o menor em caso positivo
    if(esquerdo < int(tamanho) && heap[esquerdo] < heap[indexMenor])
        indexMenor = esquerdo;
    if(direito < int(tamanho) && heap[direito] < heap[indexMenor])
        indexMenor = direito;
    
    if(indexMenor != i){
        std::swap(heap[i], heap[indexMenor]); // troca pai com menor dos filhos
        corrigeDescendo(indexMenor); // verifica pai com seus novos filhos
    }

}

void MinHeap::corrigeSubindo(int i){
    
    int indexPai{pai(i)};

    // verifica se o filho é menor que o pai
    if(heap[i] < heap[indexPai]){
        std::swap(heap[i], heap[indexPai]);
        corrigeSubindo(indexPai);
    }
}

bool MinHeap::vazia(){
    return !bool(tamanho);
}

bool MinHeap::cheia(){
    return (tamanho == capacidade);
}

Dado MinHeap::espiaRaiz(){
    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    return heap[0];
}

Dado MinHeap::removeRaiz(){

    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    Dado temp = heap[0];

    std::swap(heap[0], heap[--tamanho]);
    corrigeDescendo(0);

    return temp;
    

}

void MinHeap::insere(const Dado &d){

    if(cheia()) 
        throw std::runtime_error("Erro: Heap Cheia.\n");
    
    heap[tamanho++] = d;
    corrigeSubindo(tamanho - 1);

}

void MinHeap::imprime(){
    for(int i{0}; i< int(tamanho); i++)
        std::cout << heap[i] << " ";

    std::cout << "\n";
}

unsigned int MinHeap::getTamanho(){
    return tamanho;
}

unsigned int MinHeap::getCapacidade(){
    return capacidade;
}


int main(){

    MinHeap heap;
    Dado d;
    char opcao;

    do {
        try {
            std::cin >> opcao;
            switch (opcao) {
                case 'i': // inserir
                    std::cin >> d;
                    heap.insere(d);
                    break;
                case 'r': // remover
                    d = heap.removeRaiz();
                    std::cout << d << "\n";
                    break;
                case 'e': // espiar raiz
                    d = heap.espiaRaiz();
                    std::cout << d << "\n";
                    break;
                case 'p': // imprimir
                    heap.imprime();
                    break;
                case 't':
                    std::cout << "tamanho: " << heap.getTamanho() << "\n";
                    std::cout << "capacidade: " << heap.getCapacidade() << "\n";
                    break;
                case 'x': // sair
                    break;
                default:
                    std::cout << "opcao inválido\n";
            }
        } catch (std::runtime_error& e) {
            std::cout << e.what() << "\n";
        }
    } while (opcao != 'x'); // finalizar execução

    return 0;
}