//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDNODE_H
#define DATA_STRUCTURE_SINGLYLINKEDNODE_H

#include "./interface/SinglyLinkedNodeInterface.h"
#include "AbstractNode.h"

/// @brief Nó vinculado individualmente
///
/// Classe genérica usada para representar um
/// nó encadeado individualmente. Herdar
/// de AbstractNode e SinglyLinkedNodeInterface.
/// Observe que no processo de herança,
/// SinglyLinkedNodeInterface é declarado
/// como público, isso é feito para que cada
/// o conteúdo herdado da interface é
/// acessível externamente, enquanto
/// o conteúdo de AbstractNode não está acessível
/// @tparam T o tipo de dados armazenados no nó
template <class T>
class SinglyLinkedNode : AbstractNode<T>, SinglyLinkedNodeInterface<T> {
 private:
  /// Atributo usado para representar o próximo nó
  /// do tópico. A princípio o
  /// valor é nulo.
  T* _next = nullptr;

 public:
  /// Construtor público usado para inicializar todos os atributos da classe
  /// @param data o valor dos dados a serem interrompidos no nó
  /// @param próximo ao próximo nó duplamente vinculado da cadeia
  SinglyLinkedNode(T data, T* next) : AbstractNode<T>(data), _next(next) {}

  /// Construtor público usado para inicializar o atributo contido no nó.
  /// O método deve ser declarado com a palavra-chave explícita porque é
  /// um construtor que pode ser chamado com apenas um argumento
  /// @param data o valor armazenado no nó
  explicit SinglyLinkedNode(T data) : AbstractNode<T>(data), _next(nullptr) {}

  /// Método Get usado para acessar o próximo atributo, que indica o próximo nó
  /// da cadeia. O método é constante, implementa o que está declarado na
  /// interface e retorna um ponteiro para DoublyLinkedNode
  /// @return próximo nó da cadeia
  SinglyLinkedNode<T>* getNext() const override;

  /// Método set usado para definir o valor do próximo atributo, com base no
  /// ponteiro passado como argumento
  /// @param próximo ao ponteiro para o próximo nó da cadeia a ser definido
  void setNext(SinglyLinkedNode<T>* next) override;

  /// Método get usado para acessar o valor contido em um nó, obtendo uma cópia
  /// dele
  /// @return o valor armazenado no nó
  T getValue() const override;
};

#endif  // DATA_STRUCTURE_SINGLYLINKEDNODE_H
