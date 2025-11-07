#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
  virtual void push(const T&) = 0;
  virtual T pop() = 0;
  virtual T peek() const = 0;
  virtual std::size_t getSize() const noexcept = 0;
};


template <typename T>
class QueueInterface {
  virtual void enqueue() = 0;
  virtual T dequeue() = 0;
  virtual T peek() const = 0;
  virtual std::size_t getSize() const noexcept = 0;
};


template <typename T>
class DequeInterface {
  virtual void pushFront(const T& item);
  virtual void pushBack(const T& item);
  
};

