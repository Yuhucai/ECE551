#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned, BitString> & theMap) {
  //contains a symbol
  if (sym != NO_SYM) {
    assert((left == NULL) && (right == NULL));
    theMap.insert(std::pair<unsigned, BitString>(sym, b));
  }
  //internal node
  else {
    assert((left != NULL) && (right != NULL));
    left->buildMap(b.plusZero(), theMap);
    right->buildMap(b.plusOne(), theMap);
  }
}
