#include <iostream>
#include <stdexcept>
#include <utility>
#include <cstring>

typedef int Dado;

class MaxHeap{

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
        MaxHeap(int capacidade = 10); // construtor cria heap vazia
        MaxHeap(Dado *arr, int tamanhoArr); // construtor cria heap a partir de array já preenchido
        ~MaxHeap();
        Dado espiaRaiz();
        Dado removeRaiz();
        void insere(const Dado &d);
        void imprime(); //fins didáticos (configura quebra de estrutura)
        unsigned int getTamanho();
        unsigned int getCapacidade();
};

MaxHeap::MaxHeap(int capacidade) : capacidade(capacidade){

    heap = new Dado[capacidade];
    tamanho = 0;
}

MaxHeap::MaxHeap(Dado *arr, int tamanhoArr) : capacidade(tamanhoArr){

    tamanho = tamanhoArr;
    heap = new Dado[tamanhoArr];
    std::memcpy(heap, arr, sizeof(Dado) * tamanhoArr);
    arruma();
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

void MaxHeap::arruma(){
    for(int i{int(tamanho/2 - 1)}; i>=0; i--) // metade para cima (apenas nós não-folhas) até a raiz
        corrigeDescendo(i);
}

int MaxHeap::pai(int i){
    return (i - 1)/2;
}

int MaxHeap::filhoEsquerdo(int i){
    return i*2 + 1;
}

int MaxHeap::filhoDireito(int i){
    return i*2 + 2;
}

void MaxHeap::corrigeDescendo(int i){

    int esquerdo{filhoEsquerdo(i)}, direito{filhoDireito(i)};
    int indexMaior = i;

    // verifica se algum dos filhos é maior que o pai e pega o maior em caso positivo
    if(esquerdo < int(tamanho) && heap[esquerdo] > heap[indexMaior])
        indexMaior = esquerdo;
    if(direito < int(tamanho) && heap[direito] > heap[indexMaior])
        indexMaior = direito;
    
    if(indexMaior != i){
        std::swap(heap[i], heap[indexMaior]); // troca pai com maior dos filhos
        corrigeDescendo(indexMaior); // verifica pai com seus novos filhos
    }

}

void MaxHeap::corrigeSubindo(int i){
    
    int indexPai{pai(i)};

    // verifica se o filho é maior que o pai
    if(heap[i] > heap[indexPai]){
        std::swap(heap[i], heap[indexPai]);
        corrigeSubindo(indexPai);
    }
}

bool MaxHeap::vazia(){
    return !bool(tamanho);
}

bool MaxHeap::cheia(){
    return (tamanho == capacidade);
}

Dado MaxHeap::espiaRaiz(){
    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    return heap[0];
}

Dado MaxHeap::removeRaiz(){

    if(vazia()) 
        throw std::runtime_error("Erro: Heap Vazia.\n");
    
    Dado temp = heap[0];

    std::swap(heap[0], heap[--tamanho]);
    corrigeDescendo(0);

    return temp;
    

}

void MaxHeap::insere(const Dado &d){

    if(cheia()) 
        throw std::runtime_error("Erro: Heap Cheia.\n");
    
    heap[tamanho++] = d;
    corrigeSubindo(tamanho - 1);

}

void MaxHeap::imprime(){
    for(int i{0}; i< int(tamanho); i++)
        std::cout << heap[i] << " ";

    std::cout << "\n";
}

unsigned int MaxHeap::getTamanho(){
    return tamanho;
}

unsigned int MaxHeap::getCapacidade(){
    return capacidade;
}


int main(){

    MaxHeap heap;
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