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
    temp->data = data;
    temp->next = this->head;
    temp->prev = nullptr;
    if (this->head != nullptr) {
      this->head->prev = temp;
    } else {
      this->tail = temp;
    }
    this->head = temp;
    this->count++;
  }
	void addTail(const T& data) {
    Node<T>* temp = new Node<T>();
    temp->data = data;
    temp->prev = this->tail;
    temp->next = nullptr;
    if (this->tail != nullptr) {
      this->tail->next = temp;
    } else {
      this->head = temp;
    }
    this->tail = temp;
    this->count++;
  }

	// Removal
	bool removeHead() {
    if (this->getCount() == 1) {
      delete this->head;
      this->head = nullptr;
      this->tail = nullptr;
      this->count--;
      return true;
    }
    if (this->head == nullptr) return false;
    Node<T>* prevHead = this->head;
    this->head = this->head->next;
    if (this->head) this->head->prev = nullptr;
    delete prevHead;
    this->count--;
    return true;
  }
	bool removeTail() {
    if (this->getCount() == 1) {
      delete this->tail;
      this->head = nullptr;
      this->tail = nullptr;
      this->count--;
      return true;
    }
    if (this->tail == nullptr) return false;
    Node<T>* prevTail = this->tail;
    this->tail = this->tail->prev;
    if (this->tail) this->tail->next = nullptr;
    delete prevTail;
    this->count--;
    return true;
  }
	void clear() {
    while(this->removeTail()) {}
  }

	// Operators
	LinkedList<T>& operator=(const LinkedList<T>& other) {
    if (this == &other) return *this;
    this->clear();
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    Node<T>* curr = other.head;
    while (curr != nullptr) {
      this->addTail(curr->data);
      curr = curr->next;
    }
    return *this;
  }
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
    if (this == &other) return *this;
    this->clear();
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
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
  }
	LinkedList(const LinkedList<T>& other) {
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    Node<T>* curr = other.head;
    while (curr != nullptr) {
      this->addTail(curr->data);
      curr = curr->next;
    }
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
    this->clear();
  }

private:
	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
};


