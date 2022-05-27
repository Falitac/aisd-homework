#include "bst-tree.hpp"
#include <iostream>

void bstTreeTest(int num) {
  Node* root = nullptr;
  int val;
  while(std::cin >> val) {
    Node* t = insertBST(root, val);
  }

  print2BST(root); std::printf("\n");

  //int num = -20;
  std::printf("Deleting %d\n", num);
  removeBST(root, findValueBST(root, num));
  print2BST(root);

  clearBST(root);
  std::puts("All done");
}

int main(int argc, char** argv) {
  if(argc == 2)
    bstTreeTest(std::atoi(argv[1]));
}