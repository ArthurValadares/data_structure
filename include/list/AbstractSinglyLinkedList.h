//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTLINKEDLIST_H
#define DATA_STRUCTURE_ABSTRACTLINKEDLIST_H

#include "../common/node/interface/SinglyLinkedNodeInterface.h"

template <class T>
class AbstractSinglyLinkedList {
 protected:
  SinglyLinkedNodeInterface<T>* _begin = nullptr;
  SinglyLinkedNodeInterface<T>* _end = nullptr;

  AbstractSinglyLinkedList(SinglyLinkedNodeInterface<T>* begin,
                           SinglyLinkedNodeInterface<T>* end)
      : _begin(begin), _end(end) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTLINKEDLIST_H
