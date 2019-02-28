#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstset.h"

int main(void) {
  BstSet<int> set;
  set.add(60);
  set.add(19);
  set.add(93);
  set.add(4);
  set.add(25);
  set.add(84);
  set.add(1);
  set.add(11);
  set.add(21);
  set.add(35);
  set.add(70);
  set.add(86);
  set.inorder();
  std::cout << "\n";
  int ans1 = set.contains(60);
  int ans2 = set.contains(35);
  set.remove(19);
  set.inorder();
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";

  BstSet<int> set2 = set;
  set2.inorder();
  std::cout << "\n";
  return EXIT_SUCCESS;
}
