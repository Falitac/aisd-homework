#include "bst-tree.hpp"
#include <iostream>

Node* insertBST(Node*& root, int val, Node* father) {
  if(!root) {
    root = new Node;
    root->val = val;
    root->left = root->right = nullptr;
    root->up = father;
    return root;
  }
  if(root->val > val) {
    return insertBST(root->left, val, root);
  } else {
    return insertBST(root->right, val, root);
  }
}

// TODO
void removeBST(Node*& root, Node* node) {
  if(!node) return;
  Node* father = node->up;

  if(node->left && node->right) {
    Node* next = findNextBST(node);
    if(next)
      std::printf("next: %d\n", next->val);
    
    if(next->up) {
      next->up->left = next->right;
      next->right = next->up;
    }

    next->left = node->left;
    next->left->up = next;

    if(father) {
      if(father->left == node) {
        father->left = next;
      } else {
        father->right = next;
      }
      next->up = father;
    }
    next->right = node->right;

    if(node == root) {
      root = next;
    }
  } else {
    Node* newChild = node->left ? node->left : node->right;
    if(father) {
      if(father->left == node) {
        father->left = newChild;
      } else {
        father->right = newChild;
      }
    }
    if(node == root) {
      root = nullptr;
    }
  }
  delete node;
}

void printBST(Node* root) {
  static int depth;
  depth++;
  if(root) {
    printBST(root->left);
    std::printf("%d: %d\n", depth, root->val);
    printBST(root->right);
  }
  depth--;
}

void print2BST(Node* root) {
  static int depth;
  depth++;
  if(root) {
    print2BST(root->right);
    for(int i = 0; i < depth - 1; i++)
      std::printf("     ");
    std::printf("%5d\n", root->val);
    print2BST(root->left);
  }
  depth--;
}

void clearBST(Node* root) {
  if(root) {
    clearBST(root->left);
    Node* tmpRight = root->right;
    delete root;
    clearBST(tmpRight);
  }
}

Node* findValueBST(Node* root, int val) {
  if(!root) return nullptr;
  if(root->val == val) {
    return root;
  } else if(val < root->val) {
    return findValueBST(root->left, val);
  } else {
    return findValueBST(root->right, val);
  }
}

Node* minBST(Node* root) {
  while(root->left)
    root = root->left;
  return root;
}

Node* maxBST(Node* root) {
  while(root->right)
    root = root->right;
  return root;
}

Node* findNextBST(Node* node) {
  if(!node) {
    return nullptr;
  }
  if(node->right) {
    return minBST(node->right);
  }
  Node* parent = node->up;
  while(parent && node == parent->right) {
    node = node->up;
    parent = parent->up;
  }
  return parent;
}

Node* findPrevBST(Node* node) {
  if(!node) {
    return nullptr;
  }
  if(node->left) {
    return maxBST(node->left);
  }
  Node* parent = node->up;
  while(parent && node == parent->left) {
    node = node->up;
    parent = parent->up;
  }
  return parent;
}

int getHeightBST(Node* root) {
  int height = 0;
  //helperHeightBST(root);
  return height;
}