//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDNODE_H
#define DATA_STRUCTURE_DOUBLYLINKEDNODE_H

#include <tuple>

#include "./interface/DoublyLinkedNodeInterface.h"
#include "AbstractNode.h"

template <class T>
class DoublyLinkedNode : AbstractNode<T>, DoublyLinkedNodeInterface<T> {
 private:
  DoublyLinkedNode<T>* _next = nullptr;
  DoublyLinkedNode<T>* _previous = nullptr;

 public:
  DoublyLinkedNode(T data, T* next, T* previous)
      : AbstractNode<T>(data), _next(next), _previous(previous) {}
  DoublyLinkedNode(T data, T* next)
      : AbstractNode<T>(data), _next(next), _previous(nullptr) {}

  explicit DoublyLinkedNode(T data)
      : _next(nullptr), _previous(nullptr), AbstractNode<T>(data) {}

  DoublyLinkedNode<T>* getNext() const override;

  DoublyLinkedNode<T>* getPrevious() const override;

  T getValue() const override;

  void setPrevious(DoublyLinkedNode<T>* previous) override;

  void setNext(DoublyLinkedNode<T>* next) override;

  std::tuple<DoublyLinkedNode<T>*, DoublyLinkedNode<T>*> getBoth() const;
};

#endif  // DATA_STRUCTURE_DOUBLYLINKEDNODE_H
