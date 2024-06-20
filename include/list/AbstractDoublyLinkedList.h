//
// Created by arthur on 20/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H
#define DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H

#include "../common/node/interface/DoublyLinkedNodeInterface.h"
#include "interface/ListInterface.h"

template <class T>
class AbstractDoublyLinkedList {
 protected:
  DoublyLinkedNodeInterface<T>* _begin = nullptr;
  DoublyLinkedNodeInterface<T>* _end = nullptr;

  AbstractDoublyLinkedList(DoublyLinkedNodeInterface<T>* begin,
                           DoublyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTDOUBLYLINKEDLIST_H
