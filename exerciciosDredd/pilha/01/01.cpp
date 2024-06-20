#include <iostream>

typedef int Dado; // para facilitar a troca de int para outro tipo
 
// stack implementada em arranjo
class pilhav {
    private:
        int capacidade;
        Dado *dados;
        int tamanho;
        int posTopo;
    public:
        pilhav(int cap = 100);
        ~pilhav();
        void empilha(const Dado &valor);
        Dado desempilha();
        Dado espia(); // acessa elemento do topo, mas não retira
        void depura(); // imprime os dados do vetor da stack sem removê-los (desempilhar)
        void info();  // imprime informações da stack (tamanho e  posição do topo)
};

pilhav::pilhav(int cap){

    tamanho = 0;
    posTopo = -1;
    capacidade = cap;

    dados = new Dado[cap];

}

pilhav::~pilhav(){
    delete[] dados;
}

void pilhav::empilha(const Dado &valor){

    dados[++posTopo] = valor;
    tamanho++;
}

Dado pilhav::desempilha(){
    tamanho--;
    return dados[posTopo--];
}

Dado pilhav::espia(){
    return dados[posTopo];
}

void pilhav::depura(){
    for(int i{0}; i<tamanho; i++){
        std::cout << dados[i] << " ";
    }
    std::cout << "\n";
}

void pilhav::info(){
    std::cout << tamanho << " " << posTopo << "\n";
}

int main(){

    pilhav pilhaArr(20);
    Dado d;

    for(int i{0}; i<5; i++){
        std::cin >> d;
        pilhaArr.empilha(d);
    }
    for(int i{0}; i<3; i++){
        std::cout << pilhaArr.desempilha() << " ";
    }
    std::cout << "\n";

    for(int i{0}; i<4; i++){
        std::cin >> d;
        pilhaArr.empilha(d);
    }
    for(int i{0}; i<3; i++){
        std::cout << pilhaArr.desempilha() << " ";
    }
    std::cout << "\n";

    std::cout << pilhaArr.espia() << "\n";
    pilhaArr.depura();
    pilhaArr.info();

    return 0;
}