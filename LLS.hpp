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
      if (this->list.getCount() > 0) {
        T last_item = this->list.getHead()->data;
        this->list.removeHead();
        return last_item;
      } else {
        throw std::runtime_error("No elements to pop");
      }
    }

    // Access
    T peek() const override {
      if (this->list.getCount() > 0) {
        return this->list.getHead()->data;
      } else {
        throw std::runtime_error("Stack is empty");
      }
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