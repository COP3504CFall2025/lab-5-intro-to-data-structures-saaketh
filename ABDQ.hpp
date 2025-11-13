#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ() {
      this->capacity_ = 4;
      this->size_ = 0;
      this->front_ = 0;
      this->back_ = 0;
      this->data_ = new T[this->capacity_];
    }
    explicit ABDQ(std::size_t capacity) {
      this->capacity_ = capacity;
      this->size_ = 0;
      this->front_ = 0;
      this->back_ = 0;
      this->data_ = new T[this->capacity_];
    }
    ABDQ(const ABDQ& other) {
      this->capacity_ = other.capacity_;
      this->size_ = other.size_;
      this->front_ = other.front_;
      this->back_ = other.back_;
      this->data_ = new T[this->capacity_];
      for (size_t i = 0; i < this->capacity_; i++) {
        this->data_[i] = other.data_[i];
      }
    }
    ABDQ(ABDQ&& other) noexcept {
      this->capacity_ = other.capacity_;
      this->size_ = other.size_;
      this->front_ = other.front_;
      this->back_ = other.back_;
      this->data_ = other.data_;
      other.capacity_ = 0;
      other.size_ = 0;
      other.front_ = 0;
      other.back_ = 0;
      other.data_ = nullptr;
    }
    ABDQ& operator=(const ABDQ& other) {
      if (this == &other) return *this;
      delete[] this->data_;
      this->capacity_ = other.capacity_;
      this->size_ = other.size_;
      this->front_ = other.front_;
      this->back_ = other.back_;
      this->data_ = new T[this->capacity_];
      for (size_t i = 0; i < this->capacity_; i++) {
        this->data_[i] = other.data_[i];
      }
      return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
      if (this == &other) return *this;
      delete[] this->data_;
      this->capacity_ = other.capacity_;
      this->size_ = other.size_;
      this->front_ = other.front_;
      this->back_ = other.back_;
      this->data_ = other.data_;
      other.capacity_ = 0;
      other.size_ = 0;
      other.front_ = 0;
      other.back_ = 0;
      other.data_ = nullptr;
      return *this;
    }
    ~ABDQ() {
      delete[] this->data_;
      this->capacity_ = 0;
      this->size_ = 0;
      this->front_ = 0;
      this->back_ = 0;
      this->data_ = nullptr;
    }

    // Resizes array
    void resize_array(size_t size) {
      T* new_array = new T[size];
      size_t new_index = 0;
      size_t index = this->front_;
      bool back_reached = false;
      while (back_reached == false) {
        if (index >= this->capacity_) {
          index = 0;
        }
        if (index == this->back_) {
          back_reached = true;
        }
        new_array[new_index] = this->data_[index];
        index += 1;
        new_index += 1;
      }
      delete[] this->data_;
      this->data_ = new_array;
      this->capacity_ = size;
    }

    // Expands array logic
    void expand_array(size_t size) {
      if (size >= this->capacity_) {
        this->resize_array(this->capacity_ * this->SCALE_FACTOR);
        this->front_ = 0;
        this->back_ = this->size_ - 1;
      }
    }

    // Shrink array logic
    void shrink_array(size_t size) {
      if (size > 4 && (size < (this->capacity_ / this->SCALE_FACTOR))) {
        this->capacity_ = this->capacity_ / this->SCALE_FACTOR;
        resize_array(this->capacity_);
        this->front_ = 0;
        this->back_ = this->size_ - 1;
      } else if (size == 0) {
        this->capacity_ = 1;
        resize_array(this->capacity_);
        this->front_ = 0;
        this->back_ = this->size_ - 1;
      }
    }

    // Insertion
    void pushFront(const T& item) override {
      this->expand_array(this->size_);
      if (this->size_ > 0) {
        if (this->front_ <= 0) {
          this->front_ = this->capacity_ - 1;
        } else {
          this->front_ = this->front_ - 1;
        }
      }
      this->data_[this->front_] = item;
      this->size_ += 1;
    }
    void pushBack(const T& item) override {
      this->expand_array(this->size_);
      if (this->size_ > 0) {
        if (this->back_ >= this->capacity_) {
          this->back_ = 0;
        } else {
          this->back_ = this->back_ + 1;
        }
      }
      this->data_[this->back_] = item;
      this->size_ += 1;
    }

    // Deletion
    T popFront() override {
      if (this->size_ == 0) {
        throw std::runtime_error("No elements to pop");
      }
      T front_item = this->data_[this->front_];
      this->front_ = this->front_ + 1;
      if (this->front_ >= this->capacity_) {
        this->front_ = 0;
      }
      this->size_ -= 1;
      this->shrink_array(this->size_);
      return front_item;
    }
    T popBack() override {
      if (this->size_ == 0) {
        throw std::runtime_error("No elements to pop");
      }
      T back_item = this->data_[this->back_];
      if (this->back_ == 0) {
        this->back_ = this->capacity_;
      }
      this->back_ = this->back_ - 1;
      this->size_ -= 1;
      // this->shrink_array(this->size_);
      return back_item;
    }

    // Access
    const T& front() const override {
      if (this->size_ > 0) {
        return this->data_[this->front_];
      } else {
        throw std::runtime_error("Empty array");
      }
    }
    const T& back() const override {
      if (this->size_ > 0) {
        std::cout << "back" << this->back_ << std::endl;
        return this->data_[this->back_];
      } else {
        throw std::runtime_error("Empty array");
      }
    }

    // Getters
    std::size_t getSize() const noexcept override {
      return this->size_;
    }

    // For visualization
    void printForward() const {
      size_t index = this->front_;
      bool back_reached = false;
      while (back_reached == false) {
        if (index >= this->capacity_) {
          index = 0;
        }
        if (index == this->back_) {
          back_reached = true;
        }
        // std::cout << index << " ";
        std::cout << this->data_[index] << " ";
        index += 1;
      }
      std::cout << std::endl;
    }
    void printReverse() const {
      size_t index = this->back_;
      bool front_reached = false;
      while (front_reached == false) {
        std::cout << this->data_[index] << " ";
        index -= 1;
        if (index <= 0) {
          index = this->capacity_ - 1;
        }
        if (index == this->front_) {
          front_reached = true;
        }
      }
    }

    void printOriginal() const {
      for (size_t i = 0; i < this->capacity_; i++) {
        std::cout << this->data_[i] << " ";
      }
      std::cout << std::endl;
      std::cout << front_ << " " << back_ << std::endl;
    }

};
