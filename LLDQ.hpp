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
      if (this->list.getCount() > 0) {
        T item = this->list.getHead()->data;
        this->list.removeHead();
        return item;
      } else {
        throw std::runtime_error("empty front cant remove");
      }
    }
    T popBack() override {
      if (this->list.getCount() > 0) {
        T item = this->list.getTail()->data;
        this->list.removeTail();
        return item;
      } else {
        throw std::runtime_error("empty back cant remove");
      }
    }

    // Element Accessors
    const T& front() const override {
      if (this->list.getCount() > 0) {
        return this->list.getHead()->data;
      } else {
        throw std::runtime_error("empty head");
      }
    }
    const T& back() const override {
      if (this->list.getCount() > 0) {
        return this->list.getTail()->data;
      } else {
        throw std::runtime_error("empty tail");
      }
    }

    // Getter
    std::size_t getSize() const noexcept override {
      return this->list.getCount();
    }
};






