#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V>
{
 private:
  //Nodes
  class Node
  {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    //constructor for Nodes
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    //constructor for add
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  //root
  Node * root;

 public:
  //default constructor
  BstMap() : root(NULL) {}

  //copy constructor
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  //cooy helper
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key, current->value);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  //assignment constructor
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      destroy(root);
      root = copy(rhs.root);
    }
    return *this;
  }

  //destroy helper
  void destroy(Node * current) {
    if (current != NULL) {
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  //destructor
  virtual ~BstMap<K, V>() {
    destroy(root);
    root = NULL;
  }

  //add a Node
  virtual void add(const K & key, const V & value) {
    Node ** current = &root;
    while (*current != NULL) {
      //key exists: replace its value
      if (key == (*current)->key) {
        (*current)->value = value;
        return;
      }
      //no such key
      else if (key < (*current)->key) {
        current = &((*current)->left);
      }
      else {
        current = &((*current)->right);
      }
    }
    *current = new Node(key, value);
  }

  //lookup
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return current->value;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    throw std::invalid_argument("the key is not found");
  }

  virtual void remove(const K & key) {
    Node ** current = &root;
    Node * temp = NULL;
    //find key
    while (*current != NULL) {
      //current Node needs to be removed
      if ((*current)->key == key) {
        //one node or zero node
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        else {
          //go left once
          Node ** toReplace = current;
          current = &((*current)->left);
          //follow right
          while ((*current)->right != NULL) {
            current = &((*current)->right);
          }
          (*toReplace)->key = (*current)->key;
          const V value = (*current)->value;
          temp = (*current)->left;
          delete *current;
          *current = temp;
          add((*toReplace)->key, value);
        }
      }
      else if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
  }

  // for personal testcases, print out the tree order
  void inorder() { inorder_printer(root); }

  void inorder_printer(Node * root) {
    if (root != NULL) {
      inorder_printer(root->left);
      std::cout << root->key << " ";
      inorder_printer(root->right);
    }
  }
};

#endif
