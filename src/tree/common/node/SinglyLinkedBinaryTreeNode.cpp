#include "../../../../include/tree/common/node/SinglyLinkedBinaryTreeNode.h"

template <class T>
void SinglyLinkedBinaryTreeNode<T>::setRight(
    SinglyLinkedBinaryTreeNodeInterface<T> *right) {
  this->_right = right;
}

template <class T>
SinglyLinkedBinaryTreeNodeInterface<T> *SinglyLinkedBinaryTreeNode<T>::getLeft()
    const {
  return this->_left;
}

template <class T>
void SinglyLinkedBinaryTreeNode<T>::setLeft(
    SinglyLinkedBinaryTreeNodeInterface<T> *left) {
  this->_left = left;
}

template <class T>
T SinglyLinkedBinaryTreeNode<T>::getValue() const {
  return this->_value;
}

template <class T>
void SinglyLinkedBinaryTreeNode<T>::setValue(T value) {
  this->_value = value;
}

template <class T>
SinglyLinkedBinaryTreeNodeInterface<T> *
SinglyLinkedBinaryTreeNode<T>::getRight() const {
  return this->_right;
}
