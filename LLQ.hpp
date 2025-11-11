#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {};

    // Insertion
    void enqueue(const T& item) override {
      this->list.addTail(item);
    }

    // Deletion
    T dequeue() override {
      if (this->list.getCount() > 0) {
        T last_item = this->list.getHead()->data;
        this->list.removeHead();
        return last_item;
      } else {
        throw std::runtime_error("List is empty. Cannot dequeue.");
      }
    }

    // Access
    T peek() const override {
      if (this->list.getCount() > 0) {
        return this->list.getHead()->data;
      } else {
        throw std::runtime_error("Head is empty. Cannot be peeked.")
      }
    }

    // Getter
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