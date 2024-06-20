//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_ABSTRACTNODE_H
#define DATA_STRUCTURE_ABSTRACTNODE_H

template <class T>
class AbstractNode {
 protected:
  T _data;
  explicit AbstractNode(T data) : _data(data) {}
};

#endif  // DATA_STRUCTURE_ABSTRACTNODE_H
