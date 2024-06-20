//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H
#define DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H

#include "SinglyLinkedNodeInterface.h"

template <class T>
class DoublyLinkedNodeInterface : SinglyLinkedNodeInterface<T> {
  virtual DoublyLinkedNodeInterface<T>* getPrevious() const = 0;
  virtual void setPrevious(DoublyLinkedNodeInterface<T>* previous) = 0;
};

#endif  // DATA_STRUCTURE_DOUBLYLINKEDNODEINTERFACE_H
