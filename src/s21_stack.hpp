#ifndef SRC_STACK_S21_STACK_H_
#define SRC_STACK_S21_STACK_H_
#include <iostream>

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // default constructor
  Stack() : size_(0), stack_(nullptr) {}

  // parameterized constructor
  Stack(std::initializer_list<value_type> const &items) : Stack() {
    auto i = items.begin();
    while (i != items.end()) {
      value_type value = *i;
      i++;
      push(value);
    }
  }

  // copy cnstructor
  Stack(const Stack &s) : Stack() {
    if (this != &s) {
      clean();
      size_ = 0;
      s21::Stack<value_type> help;
      for (node *node = s.stack_; node; node = node->next_)
        help.push(node->elm_);
      node *two = help.stack_;
      while (two != nullptr) {
        push(two->elm_);
        help.pop();
        two = two->next_;
      }
    }
  }

  // move constructor
  Stack(Stack &&s) : Stack() {
    if (this != &s) {
      swap(s);
      s.stack_ = nullptr;
    }
  }

  // destructor
  ~Stack() { clean(); }

  Stack &operator=(Stack &&s) {
    if (this != &s) {
      swap(s);
    }
    return *this;
  }

  //  Element access
  const_reference top() { return stack_->elm_; }

  // Capacity
  bool empty() {
    if (!stack_)
      return true;
    else
      return false;
  }

  size_type size() { return size_; }

  // Modifiers
  void push(const_reference value) {
    size_++;
    node *new_stack = new node;
    new_stack->elm_ = value;
    new_stack->next_ = stack_;
    stack_ = new_stack;
  }

  void pop() {
    size_--;
    node *tmp = stack_;
    if (stack_) {
      stack_ = tmp->next_;
    }
    delete tmp;
  }

  void swap(Stack &other) {
    std::swap(this->size_, other.size_);
    std::swap(this->stack_, other.stack_);
  }

  void emplace_front() {}  // завершающая
  template <typename type_t, typename... Args>
  void emplace_front(type_t arg1, Args &&...args) {
    push(arg1);
    emplace_front(args...);
  }

 private:
  struct node {
    value_type elm_;
    node *next_;
  };
  size_t size_;
  node *stack_;

  void clean() {
    for (size_t i = 0; i < size_; i++) pop();
    size_ = 0;
    stack_ = nullptr;
  }
};
}  // namespace s21
#endif  // SRC_STACK_S21_STACK_H_
