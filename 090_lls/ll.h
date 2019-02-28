#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>

class myexception : public std::exception
{
 public:
  virtual const char * what() const throw() { return "The requested item does not exist\n"; }
};

template<typename T>

class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(const T & item, Node * n1, Node * n2) : data(item), next(n1), prev(n2) {}
  };
  Node * head;
  Node * tail;
  int size;

 public:
  //default constructor
  LinkedList() : head(NULL), tail(NULL), size(0) {}

  //copy constructor
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
    Node * temp = rhs.tail;
    while (temp != NULL) {
      this->addFront(temp->data);
      temp = temp->prev;
    }
  }

  //assignment operator
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      while (head != NULL) {
        Node * temp = head->next;
        delete head;
        head = temp;
      }
      tail = NULL;
      size = 0;
      Node * current = rhs.tail;
      while (current != NULL) {
        this->addFront(current->data);
        current = current->prev;
      }
      size = rhs.size;
    }
    return *this;
  }

  //destructor
  ~LinkedList() {
    while (head != NULL) {
      Node * temp = head->next;
      delete head;
      head = temp;
    }
    tail = NULL;
    size = 0;
  }

  //Addfront
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  //addBack function
  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  //remove the first item
  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    if (head->data == item) {
      Node * temp = head->next;
      delete head;
      head = temp;
      if (head != NULL) {
        head->prev = NULL;
      }
      else {
        tail = NULL;
      }
      size--;
      return true;
    }
    Node * current = head;
    while (current->next != NULL) {
      if (current->next->data == item) {
        Node * temp = current->next->next;
        delete current->next;
        current->next = temp;
        if (current->next != NULL) {
          current->next->prev = current;
        }
        else {
          tail = current;
        }
        size--;
        return true;
      }
      current = current->next;
    }
    return false;
  }

  //[]method
  T & operator[](int index) {
    if (index < 0 || index >= size) {
      throw myexception();
    }
    else {
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= size) {
      throw myexception();
    }
    else {
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
  }

  //find an item
  int find(const T & item) {
    int index = 0;
    Node * current = head;
    while (current != NULL) {
      if (current->data == item) {
        return index;
      }
      index++;
      current = current->next;
    }
    return -1;
  }

  //getSize function
  int getSize() const { return size; }
};

#endif
