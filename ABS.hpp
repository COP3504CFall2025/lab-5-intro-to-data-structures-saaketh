#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
      this->capacity_ = 0;
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
    }
    ABS(ABS&& other) noexcept {
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      other.capacity_ = 0;
      other.curr_size_ = 0;
      other.array_ = nullptr;
    }
    ABS& operator=(ABS&& rhs) noexcept {
      if (this == &other) return *this;
      delete[] this->array_;
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      other.capacity_ = 0;
      other.curr_size_ = 0;
      other.array_ = nullptr;
    }
    ~ABS() noexcept override {
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
      }
      this->array_[this->curr_size_] = item;
      this->curr_size_ += 1;
    }

    T peek() const override {
      return this->array_[this->curr_size_ - 1];
    }

    T pop() override {
      this->array_[this->curr_size_ - 1] = nullptr;
      this->curr_size_ -= 1;
    };

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
