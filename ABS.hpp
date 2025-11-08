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

      }
    }
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept override;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override;

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept;

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept;

    // Push item onto the stack
    void push(const T& item) override;

    T peek() const override;

    T pop() override;

private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
