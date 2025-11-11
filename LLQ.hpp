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
      T last_item = this->list.getHead()->data;
      this->list.removeTail();
      return last_item;
    }

    // Access
    T peek() const override {
      return this->list.getHead()->data;
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