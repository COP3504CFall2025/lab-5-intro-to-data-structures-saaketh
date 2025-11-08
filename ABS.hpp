#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
      this->capacity_ = 1;
      this->curr_size_ = 0;
      this->array_ = new T[capacity_];
    }
    explicit ABS(const size_t capacity) {
      this->capacity_ = capacity;
      this->curr_size_ = 0;
      this->array_ = new T[capacity_];
    }
    ABS(const ABS& other) {
      this->capacity_ = other.capacity_;
      this->curr_size_ = 0;
      this->array_ = new T[capacity_];
      for (int i = 0; i < this->curr_size_; i++) {
        this->push(other);
      }
    }
    ABS& operator=(const ABS& other) {
      if (this == &other) return *this;
      delete[] this->array_;
      this->capacity_ = other.capacity_;
      this->curr_size_ = 0;
      this->array_ = new T[capacity_];
      for (int i = 0; i < this->curr_size_; i++) {
        this->push(other);
      }
      return *this;
    }
    ABS(ABS&& other) noexcept {
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      other.capacity_ = 0;
      other.curr_size_ = 0;
      other.array_ = nullptr;
    }
    ABS& operator=(ABS&& other) noexcept {
      if (this == &other) return *this;
      delete[] this->array_;
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      other.capacity_ = 0;
      other.curr_size_ = 0;
      other.array_ = nullptr;
      return *this;
    }
    ~ABS() noexcept {
      delete[] this->array_;
      this->capacity_ = 0;
      this->array_ = nullptr;
      this->curr_size_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
      return this->curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
      return this->capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
      return this->array_;
    }

    // Push item onto the stack
    void push(const T& item) override {
      if (this->curr_size_ >= capacity_ - 1) { 
        T* new_array = new T[this->capacity_ * this->scale_factor_];
        for (size_t i = 0; i < this->curr_size_; i++) {
          new_array[i] = this->array_[i];
        }
        delete[] this->array_;
        this->array_ = new_array;
        this->capacity_ *= this->scale_factor_;
      }
      this->array_[this->curr_size_] = item;
      this->curr_size_ += 1;
    }

    T peek() const override {
      if (this->curr_size_ > 0) {
        return this->array_[this->curr_size_ - 1];
      } else {
        throw std::runtime_error("No elements to peek at");
      }
    }

    T pop() override { ;
      if (this->curr_size_ > 0) {
        this->curr_size_ -= 1;
        return this->array_[this->curr_size_];
      } else {
        throw std::runtime_error("No elements to pop");
      }
    }

    void printForward() {
      for (size_t i = 0; i < this->curr_size_; i++) {
        std::cout << this->array_[i] << " ";
      }
      std::cout << std::endl;
    }

    void printReverse() {
      for (size_t i = curr_size_; i >= 0; --i) {
        std::cout << this->array_[i] << " ";
      }
      std::cout << std::endl;
    }

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
