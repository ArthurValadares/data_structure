//
// Created by arthur on 19/06/24.
//

#include "../../../include/common/node/SinglyLinkedNode.h"

template <class T>
SinglyLinkedNode<T>* SinglyLinkedNode<T>::getNext() const {
  return this->_next;
}

template <class T>
void SinglyLinkedNode<T>::setNext(SinglyLinkedNode<T>* next) {
  this->_next = next;
}

template <class T>
T SinglyLinkedNode<T>::getValue() const {
  return this->_data;
}
