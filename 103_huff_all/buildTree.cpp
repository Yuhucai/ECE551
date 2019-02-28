#include "node.h"

Node * buildTree(uint64_t * counts) {
  priority_queue_t myqueue;
  for (int i = 0; i < 257; i++) {
    if (counts[i] != 0) {
      myqueue.push(new Node(i, counts[i]));
    }
  }
  //empty
  if (myqueue.size() == 0) {
    return NULL;
  }
  while (myqueue.size() > 1) {
    Node * l = myqueue.top();
    myqueue.pop();
    Node * r = myqueue.top();
    myqueue.pop();
    Node * tree = new Node(l, r);
    myqueue.push(tree);
  }
  //only one element
  return myqueue.top();
}
