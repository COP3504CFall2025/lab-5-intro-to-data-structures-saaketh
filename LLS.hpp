#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {};

    // Insertion
    void push(const T& item) override {
      this->list.addHead(item);
    }

    // Deletion
    T pop() override {
      T last_item = this->list.getHead()->data;
      this->list.removeHead();
      return last_item;
    }

    // Access
    T peek() const override {
      return this->list.getHead()->data;
    }

    // Getters
    std::size_t getSize() const noexcept override {
      return this->list.getCount();
    }

    // For visualization
    void printForward() {
      this->list.printForward();
    }
    void printReverse() {
      this->list.printReverse();
    }
};