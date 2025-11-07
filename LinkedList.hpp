#pragma once
#include <iostream>
#include <cstddef>
using namespace std;

template <typename T>
struct Node {
  T data;
  Node* prev;
  Node* next;
};

template <typename T>
class LinkedList {
public:
	// Behaviors
	void printForward() const {
    Node<T>* curr = this->head;
    while (curr != nullptr) {
      std::cout << curr->data << " ";
      curr = curr->next;
    }
    std::cout << std::endl;
  }
	void printReverse() const {
    Node<T>* curr = this->tail;
    while (curr != nullptr) {
      std::cout << curr->data << " ";
      curr = curr->prev;
    }
    std::cout << std::endl;
  }

	// Accessors
	[[nodiscard]] unsigned int getCount() const {
    return this->count;
  }
	Node<T>* getHead() {
    return this->head;
  }
	const Node<T>* getHead() const {
    return this->head;
  }
	Node<T>* getTail() {
    return this->tail;
  }
	const Node<T>* getTail() const {
    return this->tail;
  }

	// Insertion
	void addHead(const T& data) {
    Node<T>* temp = new Node<T>();
    this->head->prev = temp;
    temp->data = data;
    temp->next = this->head;
    temp->prev = nullptr;
    this->head = temp;
    this->count++;
  }
	void addTail(const T& data) {
    Node<T>* temp = new Node<T>();
    this->tail->next = temp;
    temp->data = data;
    temp->next = nullptr;
    temp->prev = this->tail;
    this->tail = temp;
    this->count++;
  }

	// Removal
	void removeHead() {
    Node<T>* temp = this->head->next;
    delete this->head;
    this->head = temp;
    this->count--;
  }
	void removeTail() {
    Node<T>* temp = this->tail->prev;
    delete this->tail;
    this->tail = temp;
    this->count--;
  }
	void Clear() {
    while (this->getCount() != 0) {
      this->removeHead();
    }
  }

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) return *this;
    this->head = other.getHead();
    Node<T>* curr = this->head;
    while (curr != nullptr) {
      addTail(curr->next);
      curr = curr->next;
    }
    this->tail = this->getTail();
    return *this;
  }
	LinkedList<T>& operator=(const LinkedList<T>& other) {
    if (this == &other) return *this;
    this->head = other.head;
    this->tail = other.tail;
    this->count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
    return *this;
  }

	// Construction/Destruction
	LinkedList() {
    this->head = new Node<T>();
    this->tail = new Node<T>();
    this->head->next = this->tail;
    this->tail->prev = this->head;
    this->count = 2;
  }
	LinkedList(const LinkedList<T>& list) {
    this->head = list.getHead();
    Node<T>* curr = this->head;
    while (curr != nullptr) {
      addTail(curr->next);
      curr = curr->next;
    }
    this->tail = this->getTail();
  }
	LinkedList(LinkedList<T>&& other) noexcept {
    this->head = other.head;
    this->tail = other.tail;
    this->count = other.count;
    other.head = nullptr;
    other.tail = nullptr;
    other.count = 0;
  }
	~LinkedList() {
    for (size_t i = 0; i < this->getCount(); i++) {
      removeHead();
    }
    // delete this->head;
    // delete this->tail;
  }

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


