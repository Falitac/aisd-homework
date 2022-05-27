#include "bst-tree.hpp"
#include <iostream>

void bstTreeTest() {
  Node* root = nullptr;
  int val;
  Node* fourNode;
  while(std::cin >> val) {
    Node* t = insertBST(root, val);
    if(val == 4) {
      fourNode = t;
    }
  }

  print2BST(root); std::printf("\n");
  Node* p = findNextBST(findValueBST(root, 4));
  if(p) {
    std::printf("Found: %d\n", p->val);
  } else {
    std::puts("I didn't find it");
  }

  int num = 36;
  std::printf("Deleting %d\n", num);
  removeBST(root, findValueBST(root, num));
  print2BST(root);

  clearBST(root);
  std::puts("All done");
}

int main(int argc, char** argv) {
  bstTreeTest();
}