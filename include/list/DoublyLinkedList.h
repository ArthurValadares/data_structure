//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDLIST_H
#define DATA_STRUCTURE_DOUBLYLINKEDLIST_H

#include <cstddef>

#include "AbstractDoublyLinkedList.h"
#include "interface/ListInterface.h"

template <class T>
class DoublyLinkedList : AbstractDoublyLinkedList<T>, ListInterface<T> {
 private:
  DoublyLinkedList(DoublyLinkedNodeInterface<T> *begin,
                   DoublyLinkedNodeInterface<T> *end)
      : AbstractDoublyLinkedList<T>(begin, end) {}

 public:
  void push(T data) override;

  void pushBack(T data) override;

  void insertAt(std::size_t index, T data) override;

  T removeOnBegin() override;

  T removeAtEnd() override;

  T removeAt(std::size_t position) override;

  [[nodiscard]] bool isEmpty() const override;
};

#endif  // DATA_STRUCTURE_DOUBLYLINKEDLIST_H
