#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
      this->capacity_ = 1;
      this->curr_size_ = 0;
      this->array_ = new T[this->capacity_];
    }
    explicit ABQ(const size_t capacity) {
      this->capacity_ = capacity;
      this->curr_size_ = 0;
      this->array_ = new T[this->capacity_];
    }
    ABQ(const ABQ& other) {
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = new T[other.capacity_];
      for (size_t i = 0; i < other.curr_size_; i++) {
        this->array_[i] = other.array_[i];
      }
    }
    ABQ& operator=(const ABQ& other) {
      if (this == &other) return *this;
      delete[] this->array_;
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = new T[other.capacity_];
      for (size_t i = 0; i < other.curr_size_; i++) {
        this->array_[i] = other.array_[i];
      }
      return *this;
    }
    ABQ(ABQ&& other) noexcept {
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      other.capacity_ = 0;
      other.curr_size_ = 0;
      other.array_ = nullptr;
    }
    ABQ& operator=(ABQ&& other) noexcept {
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
    ~ABQ() noexcept {
      delete[] this->array_;
      this->capacity_ = 0;
      this->array_ = nullptr;
      this->curr_size_ = 0;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
      return this->curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
      return this->capacity_;
    }
    [[nodiscard]] T* getData() const noexcept {
      return this->array_;
    }

    // Resizes array
    void resize_array(size_t size) {
      T* new_array = new T[size];
      for (size_t i = 0; i < this->curr_size_; i++) {
        new_array[i] = this->array_[i];
      }
      delete[] this->array_;
      this->array_ = new_array;
      this->capacity_ = size;
    }

    // Expands array logic
    void expand_array(size_t size) {
      if (size >= this->capacity_) {
        this->resize_array(this->capacity_ * this->scale_factor_);
      }
    }

    // Shrink array logic
    void shrink_array(size_t size) {
      if (size > 0 && (size < (this->capacity_ / this->scale_factor_))) {
        this->capacity_ = this->capacity_ / this->scale_factor_;
        resize_array(this->capacity_);
      } else if (size == 0) {
        this->capacity_ = 1;
        resize_array(this->capacity_);
      }
    }

    // Insertion
    void enqueue(const T& data) override {
      this->expand_array(this->curr_size_);
      this->curr_size_ += 1;
      for (size_t i = this->curr_size_ - 1; i >= 1; i--) {
        this->array_[i] = this->array_[i - 1];
      }
      this->array_[0] = data;
    }

    // Access - same logic as peek in stack
    T peek() const override {
      if (this->curr_size_ > 0) {
        return this->array_[this->curr_size_ - 1];
      } else {
        throw std::runtime_error("No elements to peek at");
      }
    }

    // Deletion - same logic as pop in stack
    T dequeue() override {
      if (this->curr_size_ == 0) {
        throw std::runtime_error("No elements to dequeue");
      }
      T item = this->array_[this->curr_size_ - 1];
      this->curr_size_ -= 1;
      this->shrink_array(this->curr_size_);
      return item;
    }

    // For visualization
    void printForward() const {
      for (size_t i = 0; i < this->curr_size_; i++) {
        std::cout << this->array_[i] << " ";
      }
      std::cout << std::endl;
    }
    void printReverse() const {
      for (size_t i = curr_size_; i >= 0; --i) {
        std::cout << this->array_[i] << " ";
      }
      std::cout << std::endl;
    }
};
