//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDLIST_H
#define DATA_STRUCTURE_SINGLYLINKEDLIST_H

#include "AbstractSinglyLinkedList.h"
#include "interface/ListInterface.h"

template <class T>
class SinglyLinkedList : AbstractSinglyLinkedList<T>, ListInterface<T> {
 private:
  SinglyLinkedList(SinglyLinkedNodeInterface<T> *begin,
                   SinglyLinkedNodeInterface<T> *end)
      : AbstractSinglyLinkedList<T>(begin, end) {}

 public:
  void push(T data) override;

  void pushBack(T data) override;

  void insertAt(std::size_t index, T data) override;

  T removeOnBegin() override;

  T removeAtEnd() override;

  T removeAt(std::size_t position) override;

  [[nodiscard]] bool isEmpty() const override;
};

#endif  // DATA_STRUCTURE_SINGLYLINKEDLIST_H
