//
// Created by arthur on 20/06/24.
//

#include "../../include/list/DoublyLinkedList.h"

#include "../../include/common/node/DoublyLinkedNode.h"

template <class T>
void DoublyLinkedList<T>::push(T data) {
  DoublyLinkedNode<T>* node = new DoublyLinkedNode(data);
  node->setNext(this->_begin);
  this->_begin = node;
}

template <class T>
void DoublyLinkedList<T>::pushBack(T data) {
  DoublyLinkedNode<T>* node = new DoublyLinkedNode(data);
  node->setPrevious(this->_end);
  this->_end = node;
}

template <class T>
void DoublyLinkedList<T>::insertAt(std::size_t index, T data) {
  DoublyLinkedNode<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    current = current->getNext();
  }

  DoublyLinkedNode<T>* node = new DoublyLinkedNode(data);
  DoublyLinkedNode<T>* previous = current->getPrevious();
  node->setPrevious(previous);
  previous->setNext(node);
  current->setPrevious(node);
}

template <class T>
T DoublyLinkedList<T>::removeOnBegin() {
  auto current = this->_begin;
  this->_begin = current->getNext();

  T value = current->getValue();
  delete current;

  return value;
}

template <class T>
T DoublyLinkedList<T>::removeAtEnd() {
  auto current = this->_end;
  this->_end = current->getPrevious();

  T value = current->getValue();
  delete current;

  return value;
}

template <class T>
T DoublyLinkedList<T>::removeAt(std::size_t position) {
  DoublyLinkedNode<T>* current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < position) {
    current = current->getNext();
  }

  auto [previous, next] = current->getBoth();

  T value = current->getValue();
  previous->setNext(next);
  next->setPrevious(previous);

  delete current;

  return value;
}

template <class T>
bool DoublyLinkedList<T>::isEmpty() const {
  return this->_begin == nullptr and this->_end == nullptr;
}
