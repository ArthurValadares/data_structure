//
// Created by arthur on 19/06/24.
//

#ifndef DATA_STRUCTURE_LINKEDLISTINTERFACE_H
#define DATA_STRUCTURE_LINKEDLISTINTERFACE_H

#include <cstddef>

template <class T>
class ListInterface {
 public:
  virtual void push(T data) = 0;
  virtual void pushBack(T data) = 0;
  virtual void insertAt(std::size_t index, T data) = 0;

  virtual T removeOnBegin() = 0;
  virtual T removeAtEnd() = 0;
  virtual T removeAt(std::size_t position) = 0;

  [[nodiscard]] virtual bool isEmpty() const = 0;
};

#endif  // DATA_STRUCTURE_LINKEDLISTINTERFACE_H
