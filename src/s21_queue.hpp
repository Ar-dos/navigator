#ifndef SRC_QUEUE_S21_QUEUE_H_
#define SRC_QUEUE_S21_QUEUE_H_
#include <iostream>

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // default constructor
  Queue() : size_(0), fr_(nullptr), bc_(nullptr) {}

  // parameterized constructor
  Queue(std::initializer_list<value_type> const &items) : Queue() {
    auto i = items.begin();
    while (i != items.end()) {
      value_type value = *i;
      i++;
      push(value);
    }
  }

  // copy constructor
  Queue(const Queue &q) : Queue() {
    if (this != &q) {
      for (node *node = q.fr_; node; node = node->next_) push(node->elm_);
    }
  }

  // move cnstructor
  Queue(Queue &&q) : Queue() {
    if (this != &q) {
      swap(q);
    }
  }

  // destructor
  ~Queue() {
    for (size_t i = 0; i < size_; i++) pop();
    size_ = 0;
    fr_ = nullptr;
    bc_ = nullptr;
  }

  Queue &operator=(Queue &&q) {
    if (this != &q) {
      swap(q);
    }
    return *this;
  }

  //  Element access
  const_reference front() { return fr_->elm_; }

  const_reference back() { return bc_->elm_; }

  // Capacity
  bool empty() {
    if (!fr_)
      return true;
    else
      return false;
  }

  size_type size() { return size_; }

  // Modifiers
  void push(const_reference value) {
    size_++;
    node *new_queue = new node;
    new_queue->elm_ = value;
    if (fr_ == nullptr) {
      new_queue->next_ = nullptr;
      fr_ = new_queue;
      bc_ = new_queue;
    } else {
      new_queue->next_ = nullptr;
      bc_->next_ = new_queue;
      bc_ = new_queue;
    }
  }

  void pop() {
    size_--;
    node *tmp = fr_;
    if (fr_) {
      fr_ = tmp->next_;
    }
    delete tmp;
  }

  void swap(Queue &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->fr_, other.fr_);
    std::swap(this->bc_, other.bc_);
  }

  void emplace_back() {}  // завершающая
  template <typename type_t, typename... Args>
  void emplace_back(type_t arg1, Args &&...args) {
    push(arg1);
    emplace_back(args...);
  }

 private:
  struct node {
    value_type elm_;
    node *next_;
  };
  size_t size_;
  node *fr_;
  node *bc_;
};
}  // namespace s21
#endif  // SRC_QUEUE_S21_QUEUE_H_
