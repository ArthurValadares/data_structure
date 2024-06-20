//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_NODEINTERFACE_H
#define DATA_STRUCTURE_NODEINTERFACE_H

template <class T>
class NodeInterface {
 public:
  virtual T getValue() const = 0;
};

#endif  // DATA_STRUCTURE_NODEINTERFACE_H
