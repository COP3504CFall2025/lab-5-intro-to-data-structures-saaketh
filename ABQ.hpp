#pragma once

#include <cstddef>
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
    }
    ABQ(ABQ&& other) noexcept {
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      this->capacity_ = 0;
      this->curr_size_ = 0;
      this->array_ = nullptr;
    }
    ABQ& operator=(ABQ&& other) noexcept {
      if (this == &other) return *this;
      delete[] this->array_;
      this->capacity_ = other.capacity_;
      this->curr_size_ = other.curr_size_;
      this->array_ = other.array_;
      this->capacity_ = 0;
      this->curr_size_ = 0;
      this->array_ = nullptr;
    }
    ~ABQ() noexcept override {
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

    void expand_array() {
      if (this->capacity_ <= this->curr_size_) {
        T* new_array = new T[this->capacity_ * this->scale_factor_];
        for (size_t i = 0; i < this->curr_size_; i++) {
          new_array[i] = this->array_[i];
        }
        delete[] this->array_;
        this->array_ = new_array;
        this->capacity_ *= this->scale_factor_;
      }
    }

    // Insertion
    void enqueue(const T& data) override {
      expand_array();
      for (size_t i = 0; i < this->curr_size_; i++) {
        this->array_[i+1] = this->array_[i];
      }
      this->array_[0] = data;
      this->curr_size_ += 1;
    }

    // Access
    T peek() const override {

    }

    // Deletion
    T dequeue() override;

};
