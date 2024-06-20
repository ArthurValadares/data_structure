//
// Created by arthur on 19/06/24.
//

#include "../../../include/common/node/DoublyLinkedNode.h"

template <class T>
DoublyLinkedNode<T> *DoublyLinkedNode<T>::getPrevious() const {
  return this->_previous;
}

template <class T>
DoublyLinkedNode<T> *DoublyLinkedNode<T>::getNext() const {
  return this->_next;
}

template <class T>
T DoublyLinkedNode<T>::getValue() const {
  return this->_data;
}

template <class T>
void DoublyLinkedNode<T>::setPrevious(DoublyLinkedNode<T> *previous) {
  this->_previous = previous;
}

template <class T>
void DoublyLinkedNode<T>::setNext(DoublyLinkedNode<T> *next) {
  this->_next = next;
}

template <class T>
std::tuple<DoublyLinkedNode<T> *, DoublyLinkedNode<T> *>
DoublyLinkedNode<T>::getBoth() const {
  return std::make_tuple(this->_previous, this->_next);
}