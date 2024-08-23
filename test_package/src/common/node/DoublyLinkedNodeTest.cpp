//
// Created by arthur on 17/08/24.
//

#include "catch2/catch_test_macros.hpp"

#include "common/Common.h"

TEST_CASE("DoublyLinkedNodeTest", "[DoublyLinkedNode]"){
    auto node = DoublyLinkedNode(3);

    // Verifica se o valor armazenado no nó está correto
    REQUIRE(node.getValue() == 3);

    // Verifica se _next está inicialmente setado para nullptr
    REQUIRE(node.getNext() == nullptr);

    // Verifica se _previous está inicialmente setado para nullptr
    REQUIRE(node.getPrevious() == nullptr);

    // Cria um segundo nó para testar os ponteiros
    auto nextNode = new DoublyLinkedNode(7);

    // Configura o próximo nó e verifica se _next está correto
    node.setNext(nextNode);
    REQUIRE(node.getNext() == nextNode);

    auto previousNode = new DoublyLinkedNode(4);

    // Configura o nó anterior e verifica se _previous está correto
    node.setPrevious(previousNode);
    REQUIRE(node.getPrevious() == previousNode);

    // Verifica se os ponteiros do segundo nó estão inicialmente setados para nullptr
    REQUIRE(nextNode->getNext() == nullptr);
    REQUIRE(nextNode->getPrevious() == nullptr);
}