#include <iostream>
#include <stdexcept>

typedef std::string Dado;

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
        std::string getTipoFila();
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

bool atenderFila(FilaEncadeada &fila){
    if(fila.vazia())
        return false;
    std::cout << fila.desenfileira() << "\n";
    return true;
}

int main(){

    FilaEncadeada filaNormal, filaPrioritario;
    Dado d;
    std::string opcao, nome;
    int atendimentosRestantes{3};
    bool atendeu;

    do{

        try{

            std::cin >> opcao;

            if(opcao == "normal"){

                std::cin >> nome;
                filaNormal.enfileira(nome);
            }else if(opcao == "prioridade"){
                std::cin >> nome;
                filaPrioritario.enfileira(nome);
            }else if(opcao == "atender"){

                atendeu = true;

                if(atendimentosRestantes > 0){
                    atendeu = atenderFila(filaPrioritario);

                    if(!atendeu){
                        atendeu = atenderFila(filaNormal);
                        if(atendeu)
                            atendimentosRestantes = 3;
                    }else{
                        atendimentosRestantes--;
                    }
                }else{
                    atendeu = atenderFila(filaNormal);

                    if(!atendeu){
                        atendeu = atenderFila(filaPrioritario);
                    }else{
                        atendimentosRestantes = 3;
                    }
                }

                if(!atendeu)
                    std::cout << "AGUARDE\n";

            }

        }catch(std::runtime_error &err){
            std::cout << err.what() << "\n";
        }

    }while(opcao != "fim");

    return 0;
}