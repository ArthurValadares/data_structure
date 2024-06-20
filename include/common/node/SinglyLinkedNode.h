//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDNODE_H
#define DATA_STRUCTURE_SINGLYLINKEDNODE_H

#include "./interface/SinglyLinkedNodeInterface.h"
#include "AbstractNode.h"

template <class T>
class SinglyLinkedNode : AbstractNode<T>, SinglyLinkedNodeInterface<T> {
 private:
  T* _next = nullptr;

 public:
  SinglyLinkedNode(T data, T* next) : AbstractNode<T>(data), _next(next) {}

  explicit SinglyLinkedNode(T data) : AbstractNode<T>(data), _next(nullptr) {}

  SinglyLinkedNode<T>* getNext() const override;
  void setNext(SinglyLinkedNode<T>* next) override;
  T getValue() const override;
};

#endif  // DATA_STRUCTURE_SINGLYLINKEDNODE_H
