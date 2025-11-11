#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {};

    // Core Insertion Operations
    void pushFront(const T& item) override {
      this->list.addHead(item);
    }
    void pushBack(const T& item) override {
      this->list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
      T item = this->list.getHead()->data;
      this->list.removeHead();
      return item;
    }
    T popBack() override {
      T item = this->list.getTail()->data;
      this->list.removeTail();
      return item;
    }

    // Element Accessors
    const T& front() const override {
      return this->list.getHead()->data;
    }
    const T& back() const override {
      return this->list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
      return this->list.getCount();
    }
};






