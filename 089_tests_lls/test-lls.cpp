#include <assert.h>

#include <cstdlib>

#include "il.h"

void testList(void) {
  //create Intlist l1:21
  IntList l1;
  assert(l1.getSize() == 0 && l1.size == 0 && l1.head == NULL && l1.tail == NULL);
  l1.addBack(1);
  assert(l1.getSize() == 1 && l1.size == 1 && l1.head == l1.tail && l1.head != NULL);
  l1.addFront(2);
  assert(l1.getSize() == 2 && l1.size == 2);
  assert(l1[0] == 2);
  assert(l1[1] == 1);
  assert(l1.head->next->next == NULL);
  assert(l1.head == l1.head->next->prev);
  assert(l1.tail == l1.head->next);
  //create Intlist l2 by assignment operator
  IntList l2;
  l2 = l1;
  assert(l2.getSize() == 2 && l2.size == 2);
  assert(l2[0] == 2);
  assert(l2[1] == 1);
  assert(l2.head->next->next == NULL);
  assert(l2.head == l2.head->next->prev);
  assert(l2.tail == l2.head->next);
  // create Intlist l3 by copy constructor
  IntList l3(l1);
  assert(l3.getSize() == 2 && l3.size == 2);
  assert(l3[0] == 2);
  assert(l3[1] == 1);
  assert(l3.head->next->next == NULL);
  assert(l3.head == l3.head->next->prev);
  assert(l3.tail == l3.head->next);
  // Intlist l1:224321 change to 24321
  l1.addFront(3);
  l1.addFront(4);
  l1.addFront(2);
  l1.addFront(2);
  assert(l1[0] == 2 && l1[1] == 2 && l1[2] == 4);
  assert(l1.size == 6 && l1.getSize() == 6);
  bool x = l1.remove(2);
  assert(l1.size == 5 && l1.getSize() == 5);
  assert(x == true);
  assert(l1[0] == 2 && l1[3] == 2);
  assert(l1.head->data == 2);
  assert(l1.head->next->data == 4);
  bool y = l1.remove(10);
  assert(y == false);
  int f1 = l1.find(2);
  assert(f1 == 0);
  int f2 = l1.find(4);
  assert(f2 == 1);
  int f3 = l1.find(9);
  assert(f3 == -1);
  // Intlist l1:24321 change to 24321510
  l1.addBack(5);
  l1.addBack(10);
  assert(l1.size == 7 && l1.getSize() == 7);
  assert(l1[5] == 5 && l1[6] == 10);
  // remove l2
  l2.remove(2);
  l2.remove(1);
  assert(l2.size == 0 && l2.getSize() == 0 && l2.head == NULL && l2.tail == NULL);
  // Inlist l3:21 change to 1
  l3.remove(2);
  assert(l3.getSize() == 1 && l3.size == 1 && l3.head == l3.tail && l3.head != NULL);
  assert(l3[0] == 1);
  assert(l3.head->next == NULL && l3.head->prev == NULL);
}

int main(void) {
  testList();
  return EXIT_SUCCESS;
}
