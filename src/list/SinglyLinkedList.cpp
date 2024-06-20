//
// Created by arthur on 19/06/24.
//

#include "../../include/list/SinglyLinkedList.h"

#include "../../include/common/node/SinglyLinkedNode.h"

template <class T>
void SinglyLinkedList<T>::push(T data) {
  SinglyLinkedNode<T> *node = new SinglyLinkedNode(data);
  node->setNext(this->_begin);
  this->_begin = node;
}

template <class T>
void SinglyLinkedList<T>::pushBack(T data) {
  SinglyLinkedNode<T> *node = new SinglyLinkedNode(data);
  this->_end->setNext(node);
  this->_end = node;
}

template <class T>
void SinglyLinkedList<T>::insertAt(std::size_t index, T data) {
  auto current = this->_begin;
  SinglyLinkedNode<T> *previous = nullptr;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < index) {
    previous = current;
    current = current->getNext();

    i++;
  }

  SinglyLinkedNode<T> *node = new SinglyLinkedNode(data);

  if (previous == nullptr) {
    node->setNext(this->_begin);
    this->_begin = node;
  } else if (current->getNext() == nullptr) {
    current->setNext(node);
    this->_end = node;
  } else {
    previous->setNext(node);
    node->setNext(current);
  }
}

template <class T>
T SinglyLinkedList<T>::removeOnBegin() {
  SinglyLinkedNode<T> *next = this->_begin->getNext();
  auto value = this->_begin->getValue();
  this->_begin = next;
  return value;
}

template <class T>
T SinglyLinkedList<T>::removeAtEnd() {
  T data = this->_end->getValue();

  SinglyLinkedNode<T> *previous = nullptr;
  SinglyLinkedNode<T> *current = this->_begin;
  while (current->getNext() != nullptr) {
    previous = current;
    current = current->getNext();
  }

  if (previous != nullptr) {
    previous->setNext(nullptr);
  }

  this->_end = previous;

  return data;
}

template <class T>
T SinglyLinkedList<T>::removeAt(std::size_t position) {
  SinglyLinkedNode<T> *previous = nullptr;
  SinglyLinkedNode<T> *current = this->_begin;
  std::size_t i = 0;

  while (current->getNext() != nullptr and i < position) {
    previous = current;
    current = current->getNext();

    i++;
  }

  T data = current->getValue();

  if (previous == nullptr) {
    this->_begin = current->getNext();
  } else if (current->getNext() == nullptr) {
    this->_end = previous;
  } else {
    previous->setNext(current->getNext());
  }

  return data;
}

template <class T>
bool SinglyLinkedList<T>::isEmpty() const {
  return this->_begin == nullptr and this->_end == nullptr;
}