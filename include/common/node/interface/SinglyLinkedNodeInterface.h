//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H
#define DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H

#include "NodeInterface.h"

template <class T>
class SinglyLinkedNodeInterface : NodeInterface<T> {
  virtual SinglyLinkedNodeInterface<T>* getNext() const = 0;
  virtual void setNext(SinglyLinkedNodeInterface<T>* next) = 0;
};

#endif  // DATA_STRUCTURE_SINGLYLINKEDNODEINTERFACE_H
