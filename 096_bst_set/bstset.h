#ifndef __BSTSET_H__
1;
95;
0c #define __BSTSET_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"

    template<typename K>
    class BstSet : public Set<K>
{
 private:
  //Nodes
  class Node
  {
   public:
    K key;
    Node * left;
    Node * right;
    //constructor for Nodes
    Node() : key(0), left(NULL), right(NULL) {}
    //constructor for add
    Node(const K & k) : key(k), left(NULL), right(NULL) {}
  };
  //root
  Node * root;

 public:
  //default constructor
  BstSet() : root(NULL) {}

  //copy constructor
  BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }

  //cooy helper
  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * root = new Node(current->key);
    root->left = copy(current->left);
    root->right = copy(current->right);
    return root;
  }

  //assignment constructor
  BstSet & operator=(const BstSet & rhs) {
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
  virtual ~BstSet<K>() {
    destroy(root);
    root = NULL;
  }

  //add a Node
  virtual void add(const K & key) {
    Node ** current = &root;
    while (*current != NULL) {
      //key exists: replace its value
      if (key == (*current)->key) {
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
    *current = new Node(key);
  }

  //lookup
  virtual bool contains(const K & key) const {
    Node * current = root;
    while (current != NULL) {
      if (current->key == key) {
        return true;
      }
      else if (key < current->key) {
        current = current->left;
      }
      else {
        current = current->right;
      }
    }
    return false;
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
          temp = (*current)->left;
          delete *current;
          *current = temp;
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
